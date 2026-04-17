from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
                package='nodes',
                executable='talker',
        ),
        Node(
                package='nodes',
                executable='listener',
        ),
    ])
