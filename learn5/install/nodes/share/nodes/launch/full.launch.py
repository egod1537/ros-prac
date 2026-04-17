from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    period_arg = DeclareLaunchArgument(
        'period_ms', default_value='500',
    )

    warn_arg = DeclareLaunchArgument(
        'warn_above', default_value='23.0',
        description='temperature warning threshold')

    talker = Node(
        package='nodes',
        executable='talker',
        name='temp_talker',               # 노드 이름 오버라이드
        parameters=[{
            'period_ms': LaunchConfiguration('period_ms'),
            'unit': 'celsius',
        }],
        remappings=[
            ('temperature', '/sensor/temp'),  # topic 리매핑
        ],
    )

    listener = Node(
        package='nodes',
        executable='listener',
        name='temp_listener',
        parameters=[{
            'warn_above': LaunchConfiguration('warn_above'),
        }],
        remappings=[
            ('temperature', '/sensor/temp'),  # 같은 topic으로 리매핑
        ],
    )

    return LaunchDescription([
        period_arg,
        warn_arg,
        talker,
        listener,
    ])
