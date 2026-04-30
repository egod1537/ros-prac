import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    pkg_share = get_package_share_directory('sim')
    pkg_slam = get_package_share_directory('slam_toolbox')

    sim_launch = os.path.join(pkg_share, 'launch', 'sim.launch.py')
    slam_launch = os.path.join(pkg_slam, 'launch', 'online_async_launch.py')
    rviz_config = os.path.join(pkg_share, 'config', 'slam.rviz')

    use_rviz = LaunchConfiguration('rviz')

    sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(sim_launch),
        launch_arguments={'rviz': 'false'}.items()
    )

    slam = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(slam_launch),
        launch_arguments={'use_sim_time': 'true'}.items()
    )

    rviz = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', rviz_config],
        parameters=[{'use_sim_time': True}],
        # condition=IfCondition(use_rviz),
        output='screen',
    )

    return LaunchDescription([
        DeclareLaunchArgument('rviz', default_value='true'),
        sim,
        slam,
        rviz
    ])
