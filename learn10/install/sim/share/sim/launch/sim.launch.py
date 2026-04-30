import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
import xacro


def generate_launch_description():
    pkg_share = get_package_share_directory('sim')
    pkg_ros_gz_sim = get_package_share_directory('ros_gz_sim')

    world_path = os.path.join(pkg_share, 'worlds', 'room.sdf')
    urdf_path = os.path.join(pkg_share, 'urdf', 'robot.urdf.xacro')
    bridge_config = os.path.join(pkg_share, 'config', 'bridge.yaml')
    rviz_config = os.path.join(pkg_share, 'config', 'sim.rviz')

    # Xacro 처리
    robot_desc = xacro.process_file(urdf_path).toxml()  # type: ignore

    # ===== Launch 인자 =====
    use_rviz = LaunchConfiguration('rviz')

    # ===== Gazebo 시뮬레이터 (헤드리스) =====
    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py')
        ),
        launch_arguments={
            'gz_args': f'-r -s {world_path}',
            # -r: 시작과 동시에 시뮬 재생 (paused 아님)
            # -s: server only (GUI 없음)
        }.items()
    )

    # ===== 로봇 spawn =====
    spawn = Node(
        package='ros_gz_sim',
        executable='create',
        arguments=[
            '-name', 'bot',
            '-string', robot_desc,
            '-x', '0', '-y', '0', '-z', '0.05',
        ],
        output='screen',
    )

    # ===== robot_state_publisher (URDF 기반 tf) =====
    rsp = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{
            'robot_description': robot_desc,
            'use_sim_time': True,
        }],
        output='screen',
    )

    # ===== ROS↔Gz 브릿지 =====
    bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        parameters=[{
            'config_file': bridge_config,
            'use_sim_time': True,
        }],
        output='screen',
    )

    # ===== rviz2 (옵션) =====
    rviz = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', rviz_config],
        parameters=[{'use_sim_time': True}],
        condition=IfCondition(use_rviz),
        output='screen',
    )

    return LaunchDescription([
        DeclareLaunchArgument('rviz', default_value='false',
                              description='Launch rviz2'),
        gz_sim,
        rsp,
        spawn,
        bridge,
        rviz,
    ])
