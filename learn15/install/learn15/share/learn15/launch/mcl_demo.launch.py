from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(package='learn15', executable='sim2d', name='sim2d',
             output='screen',
             parameters=[{'world_size': 20.0, 'num_landmarks': 10,
                          'odom_rate_hz': 30.0, 'landmark_rate_hz': 10.0}]),
        Node(package='learn15', executable='mcl', name='mcl',
             output='screen',
             parameters=[{'num_particles': 500,
                          'sigma_v': 0.1, 'sigma_w': 0.05,
                          'sigma_r': 0.1, 'sigma_phi': 0.05}]),
        Node(package='rviz2', executable='rviz2', name='rviz2', output='screen'),
    ])
