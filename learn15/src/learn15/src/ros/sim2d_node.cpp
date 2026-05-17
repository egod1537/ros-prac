#include <chrono>
#include <cmath>
#include <csignal>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <memory>
#include <nav_msgs/msg/odometry.hpp>
#include <random>
#include <rclcpp/publisher.hpp>
#include <rclcpp/qos.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Quaternion.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_broadcaster.hpp>
#include <vector>

#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "learn15/geom.hpp"
#include "learn15/slam_types.hpp"
#include "mcl_msgs/msg/landmark.hpp"
#include "mcl_msgs/msg/landmark_array.hpp"
#include "nav_msgs/msg/odometry.hpp"

namespace gm = geometry_msgs::msg;
namespace nm = nav_msgs::msg;
namespace mm = mcl_msgs::msg;

class Sim2DNode : public rclcpp::Node {
public:
  Sim2DNode() : Node("sim2d"), gen_(42) {
    declare_parameter<double>("world_size", 20.0);
    declare_parameter<int>("num_landmarks", 10);
    declare_parameter<double>("odom_rate_hz", 30.0);
    declare_parameter<double>("landmark_rate_hz", 10.0);
    declare_parameter<double>("noise_v", 0.05);
    declare_parameter<double>("noise_w", 0.02);
    declare_parameter<double>("noise_r", 0.05);
    declare_parameter<double>("noise_phi", 0.02);
    declare_parameter<double>("sensor_range", 5.0);

    place_landmarks();
    true_pose_ = odom_pose_ = {0, 0, 0};

    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    odom_pub_ =
        create_publisher<nm::Odometry>("/odom", rclcpp::SensorDataQoS());
    landmark_pub_ = create_publisher<mm::LandmarkArray>(
        "/landmarks", rclcpp::SensorDataQoS());
    gt_pub_ = create_publisher<gm::PoseStamped>("/ground_truth", 10);

    odom_timer_ =
        create_wall_timer(std::chrono::duration<double>(
                              1.0 / get_parameter("odom_rate_hz").as_double()),
                          std::bind(&Sim2DNode::tick_odom, this));
    landmark_timer_ = create_wall_timer(
        std::chrono::duration<double>(
            1.0 / get_parameter("landmark_rate_hz").as_double()),
        std::bind(&Sim2DNode::tick_landmarks, this));
  }

private:
  void tick_odom() {
    const double v = 0.5, w = 0.3;
    const double dt = 1.0 / get_parameter("odom_rate_hz").as_double();

    true_pose_.theta = wrap(true_pose_.theta + w * dt);
    true_pose_.x += v * dt * std::cos(true_pose_.theta);
    true_pose_.y += v * dt * std::sin(true_pose_.theta);

    std::normal_distribution<double> nv(0,
                                        get_parameter("noise_v").as_double());
    std::normal_distribution<double> nw(0,
                                        get_parameter("noise_w").as_double());

    const double vn = v + nv(gen_), wn = w + nw(gen_);
    odom_pose_.theta = wrap(odom_pose_.theta + wn * dt);
    odom_pose_.x += vn * dt * std::cos(odom_pose_.theta);
    odom_pose_.y += vn * dt * std::sin(odom_pose_.theta);

    const auto stamp = now();

    nm::Odometry om;
    om.header.stamp = stamp;
    om.header.frame_id = "odom";
    om.child_frame_id = "base_link";
    om.pose.pose.position.x = odom_pose_.x;
    om.pose.pose.position.y = odom_pose_.y;
    tf2::Quaternion qo;
    qo.setRPY(0, 0, odom_pose_.theta);
    om.pose.pose.orientation = tf2::toMsg(qo);
    odom_pub_->publish(om);

    gm::TransformStamped tfm;
    tfm.header.stamp = stamp;
    tfm.header.frame_id = "odom";
    tfm.child_frame_id = "base_link";
    tfm.transform.translation.x = odom_pose_.x;
    tfm.transform.translation.y = odom_pose_.y;
    tfm.transform.rotation = tf2::toMsg(qo);
    tf_broadcaster_->sendTransform(tfm);

    gm::PoseStamped gt;
    gt.header.stamp = stamp;
    gt.header.frame_id = "map";
    gt.pose.position.x = true_pose_.x;
    gt.pose.position.y = true_pose_.y;
    tf2::Quaternion qt;
    qt.setRPY(0, 0, true_pose_.theta);
    gt.pose.orientation = tf2::toMsg(qt);
    gt_pub_->publish(gt);
  }

  void tick_landmarks() {
    mm::LandmarkArray msg;
    msg.header.stamp = now();
    msg.header.frame_id = "base_link";

    std::normal_distribution<double> nr(0,
                                        get_parameter("noise_r").as_double());
    std::normal_distribution<double> nphi(
        0, get_parameter("noise_phi").as_double());
    const double max_r = get_parameter("sensor_range").as_double();

    for (size_t i = 0; i < world_landmarks_.size(); ++i) {
      const auto &[lx, ly] = world_landmarks_[i];
      const double dx = lx - true_pose_.x, dy = ly - true_pose_.y;
      const double r = std::hypot(dx, dy);
      if (r > max_r)
        continue;
      const double phi = wrap(std::atan2(dy, dx) - true_pose_.theta);

      mm::Landmark lm;
      lm.id = i;
      lm.range = r + nr(gen_);
      lm.bearing = wrap(phi + nphi(gen_));
      msg.landmarks.push_back(lm);
    }
    landmark_pub_->publish(msg);
  }

  void place_landmarks() {
    const double S = get_parameter("world_size").as_double();
    const int N = get_parameter("num_landmarks").as_int();
    std::uniform_real_distribution<double> u(-S / 2, S / 2);

    for (int i = 0; i < N; ++i)
      world_landmarks_.push_back({u(gen_), u(gen_)});
  }

  std::mt19937 gen_;
  Pose2D true_pose_, odom_pose_;
  std::vector<std::pair<double, double>> world_landmarks_;

  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::Publisher<nm::Odometry>::SharedPtr odom_pub_;
  rclcpp::Publisher<mm::LandmarkArray>::SharedPtr landmark_pub_;
  rclcpp::Publisher<gm::PoseStamped>::SharedPtr gt_pub_;
  rclcpp::TimerBase::SharedPtr odom_timer_, landmark_timer_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Sim2DNode>());
  rclcpp::shutdown();
  return 0;
}
