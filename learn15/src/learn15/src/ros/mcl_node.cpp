#include <cmath>
#include <memory>
#include <optional>

#include <geometry_msgs/msg/pose_array.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/duration.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/qos.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp/utilities.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Quaternion.hpp>
#include <tf2/LinearMath/Transform.hpp>
#include <tf2/LinearMath/Vector3.hpp>
#include <tf2/exceptions.hpp>
#include <tf2/utils.h>
#include <tf2/utils.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/buffer.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_broadcaster.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/transform_listener.hpp>

#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_array.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "learn15/geom.hpp"
#include "learn15/mcl.hpp"
#include "learn15/slam_types.hpp"
#include "mcl_msgs/msg/landmark_array.hpp"
#include "nav_msgs/msg/odometry.hpp"

namespace nm = nav_msgs::msg;
namespace gm = geometry_msgs::msg;
namespace mm = mcl_msgs::msg;

class MCLNode : public rclcpp::Node {
public:
  MCLNode() : Node("mcl") {
    declare_parameter<int>("num_particles", 500);

    declare_parameter<double>("sigma_v", 0.1);
    declare_parameter<double>("sigma_w", 0.05);
    declare_parameter<double>("sigma_r", 0.1);
    declare_parameter<double>("sigma_phi", 0.05);

    declare_parameter<double>("init_x", 0.0);
    declare_parameter<double>("init_y", 0.0);
    declare_parameter<double>("init_theta", 0.0);
    declare_parameter<double>("init_std", 0.5);

    mcl_ = std::make_unique<MCL>(get_parameter("sigma_v").as_double(),
                                 get_parameter("sigma_w").as_double(),
                                 get_parameter("sigma_r").as_double(),
                                 get_parameter("sigma_phi").as_double());
    mcl_->init_gaussian(get_parameter("num_particles").as_int(),
                        get_parameter("init_x").as_double(),
                        get_parameter("init_y").as_double(),
                        get_parameter("init_theta").as_double(),
                        get_parameter("init_std").as_double());

    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    tf_buffer_ = std::make_unique<tf2_ros::Buffer>(get_clock());
    tf_listener_ = std::make_unique<tf2_ros::TransformListener>(*tf_buffer_);

    odom_sub_ = create_subscription<nm::Odometry>(
        "/odom", rclcpp::SensorDataQoS(),
        std::bind(&MCLNode::on_odom, this, std::placeholders::_1));

    landmark_sub_ = create_subscription<mm::LandmarkArray>(
        "/landmarks", rclcpp::SensorDataQoS(),
        std::bind(&MCLNode::on_landmarks, this, std::placeholders::_1));

    pose_pub_ = create_publisher<gm::PoseStamped>("/mcl/pose", 10);
    particles_pub_ = create_publisher<gm::PoseArray>("/mcl/particles", 10);
  }

private:
  void on_odom(nm::Odometry::SharedPtr msg);
  void on_landmarks(mm::LandmarkArray::SharedPtr msg);
  void publish_pose(const Pose2D &, const rclcpp::Time &);
  void publish_particles(const rclcpp::Time &);
  void broadcast_map_to_odom(const Pose2D &, const rclcpp::Time &);

  std::unique_ptr<MCL> mcl_;
  std::optional<Pose2D> prev_odom_;

  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::unique_ptr<tf2_ros::TransformListener> tf_listener_;

  rclcpp::Subscription<nm::Odometry>::SharedPtr odom_sub_;
  rclcpp::Subscription<mm::LandmarkArray>::SharedPtr landmark_sub_;
  rclcpp::Publisher<gm::PoseStamped>::SharedPtr pose_pub_;
  rclcpp::Publisher<gm::PoseArray>::SharedPtr particles_pub_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MCLNode>());
  rclcpp::shutdown();
  return 0;
}

void MCLNode::on_odom(nm::Odometry::SharedPtr msg) {
  const double x = msg->pose.pose.position.x;
  const double y = msg->pose.pose.position.y;
  const double th = tf2::getYaw(msg->pose.pose.orientation);

  if (!prev_odom_) {
    prev_odom_ = Pose2D{x, y, th};
    return;
  }

  const auto &p = *prev_odom_;
  const double dd = std::hypot(x - p.x, y - p.y);
  const double dth = wrap(th - p.theta);

  if (dd < 1e-4 && std::abs(dth) < 1e-4) {
    prev_odom_ = Pose2D{x, y, th};
    return;
  }

  mcl_->predict(dd, dth);
  prev_odom_ = Pose2D{x, y, th};
}

void MCLNode::on_landmarks(mm::LandmarkArray::SharedPtr msg) {
  std::vector<Observation> obs;
  obs.reserve(msg->landmarks.size());
  for (const auto &lm : msg->landmarks)
    obs.push_back({lm.id, lm.range, lm.bearing});

  if (obs.empty())
    return;

  mcl_->observe(obs);
  const Pose2D pose = mcl_->mean_pose();

  publish_pose(pose, msg->header.stamp);
  publish_particles(msg->header.stamp);
  broadcast_map_to_odom(pose, msg->header.stamp);
}

void MCLNode::publish_pose(const Pose2D &pose, const rclcpp::Time &stamp) {
  gm::PoseStamped msg;
  msg.header.stamp = stamp;
  msg.header.frame_id = get_parameter("map_frame").as_string();
  msg.pose.position.x = pose.x;
  msg.pose.position.y = pose.y;

  tf2::Quaternion q;
  q.setRPY(0, 0, pose.theta);
  msg.pose.orientation = tf2::toMsg(q);
  pose_pub_->publish(msg);
}

void MCLNode::broadcast_map_to_odom(const Pose2D &pose,
                                    const rclcpp::Time &stamp) {
  const auto map_f = get_parameter("map_frame").as_string();
  const auto odom_f = get_parameter("odom_frame").as_string();
  const auto base_f = get_parameter("base_frame").as_string();

  tf2::Quaternion q_mb;
  q_mb.setRPY(0, 0, pose.theta);
  tf2::Transform T_map_base(q_mb, tf2::Vector3(pose.x, pose.y, 0));

  gm::TransformStamped tf_ob_msg;
  try {
    tf_ob_msg = tf_buffer_->lookupTransform(
        odom_f, base_f, stamp, rclcpp::Duration::from_seconds(0.1));
  } catch (const tf2::TransformException &ex) {
    RCLCPP_WARN(this->get_logger(), "TF lookup: %s", ex.what());
    return;
  }

  tf2::Transform T_odom_base;
  tf2::fromMsg(tf_ob_msg.transform, T_odom_base);

  tf2::Transform T_map_odom = T_map_base * T_odom_base.inverse();

  gm::TransformStamped out;
  out.header.stamp = stamp;
  out.header.frame_id = map_f;
  out.child_frame_id = odom_f;
  out.transform = tf2::toMsg(T_map_odom);
  tf_broadcaster_->sendTransform(out);
}

void MCLNode::publish_particles(const rclcpp::Time &stamp) {
  gm::PoseArray msg;
  msg.header.stamp = stamp;
  msg.header.frame_id = get_parameter("map_frame").as_string();

  const int M = mcl_->get_particle_count();
  msg.poses.reserve(M);
  for (int i = 0; i < M; ++i) {
    const auto &p = mcl_->get_particle(i);
    gm::Pose pose;
    pose.position.x = p.x;
    pose.position.y = p.y;
    tf2::Quaternion q;
    q.setRPY(0, 0, p.theta);
    pose.orientation = tf2::toMsg(q);
    msg.poses.push_back(pose);
  }
  particles_pub_->publish(msg);
}
