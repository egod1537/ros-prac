from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(package='nodes', executable='static_broadcaster'),
        Node(package='nodes', executable='mover'),
        Node(package='nodes', executable='tracker'),
    ])
