# 코드 기반 커리큘럼 복원

이 문서는 현재 레포의 디렉터리, 소스 코드, 메시지 정의, launch 파일, 설정 파일을 기준으로 "어떤 커리큘럼을 받아왔는지"를 역추적한 것이다. 공식 강의계획서가 아니라 코드 증거 기반의 추정이며, 빌드 산출물(`build/`, `install/`, `log/`)과 외부 의존성(`node_modules/`)은 학습 내용에서 제외했다.

## 전체 흐름 요약

이 레포는 ROS 2 C++ 기초부터 시작해서 로봇 모델링, Gazebo/RViz 시뮬레이션, SLAM Toolbox 실습, 그리고 직접 구현한 EKF-SLAM/MCL/FastSLAM까지 이어지는 로봇 소프트웨어 및 확률 로보틱스 커리큘럼으로 보인다.

큰 줄기는 다음과 같다.

1. ROS 2 C++ 기본 노드 작성: pub/sub, service, action.
2. 커스텀 인터페이스 작성: `.msg`, `.srv`, `.action`, `rosidl_generate_interfaces`.
3. launch, 파라미터, YAML 설정, topic remap, node name override.
4. TF2와 robot frame tree: static transform, dynamic transform, lookup.
5. URDF/Xacro 로봇 모델링과 RViz 표시.
6. Gazebo Sim, ros_gz_bridge, 라이다/오도메트리/차동구동 시뮬레이션.
7. SLAM Toolbox를 이용한 2D mapping 실습.
8. Eigen 기반 확률 필터 직접 구현: 1D EKF-SLAM, 2D EKF-SLAM.
9. Monte Carlo Localization 직접 구현: particle filter, likelihood, resampling, kidnap recovery 관찰.
10. OpenMP 병렬화와 성능 측정.
11. FastSLAM 직접 구현: particle별 landmark EKF map, RMSE/benchmark.
12. 직접 구현한 MCL을 ROS 2 노드로 포팅하고 RViz에서 시각화.

## 단계별 상세 커리큘럼

### learn1: ROS 2 C++ pub/sub 입문

근거 파일:

- `learn1/src/pubsub/src/publisher.cpp`
- `learn1/src/pubsub/src/subscriber.cpp`
- `learn1/src/pubsub/CMakeLists.txt`

학습 내용:

- `rclcpp::Node`를 상속한 C++ 노드 작성.
- `std_msgs::msg::String` 사용.
- `create_publisher<Msg>("topic", 10)`로 publisher 생성.
- `create_subscription<Msg>("topic", 10, callback)`로 subscriber 생성.
- `create_wall_timer()`를 이용해 500ms마다 메시지 발행.
- `rclcpp::init`, `rclcpp::spin`, `rclcpp::shutdown`의 기본 실행 구조.
- QoS depth 10, topic 이름, callback binding의 기본 형태.
- `ament_cmake`, `find_package(rclcpp REQUIRED)`, `find_package(std_msgs REQUIRED)`, `add_executable`, `ament_target_dependencies`, `install(TARGETS ...)`의 기본 CMake 패턴.

구현 산출물:

- `"hello0"`, `"hello1"` 형태의 문자열을 `/topic`에 발행하는 publisher.
- 같은 topic을 구독해서 `RCLCPP_INFO`로 출력하는 subscriber.

### learn2: ROS 2 service/client 기본

근거 파일:

- `learn2/src/service/src/server.cpp`
- `learn2/src/service/src/client.cpp`
- `learn2/src/service/CMakeLists.txt`

학습 내용:

- `example_interfaces::srv::AddTwoInts` 서비스 사용.
- `create_service<Srv>("add_two_ints", handler)`로 service server 작성.
- `create_client<Srv>("add_two_ints")`로 client 작성.
- `wait_for_service()`로 서버 준비 대기.
- `async_send_request()`와 `spin_until_future_complete()`로 비동기 요청 처리.
- request/response 포인터 타입과 callback 인자 구조 학습.

구현 산출물:

- `a + b`를 계산해 `sum`으로 반환하는 `add_two_ints` 서버.
- 고정 입력 `10 + 25`를 요청하고 결과를 출력하는 클라이언트.

### learn3: 커스텀 msg/srv와 패키지 분리

근거 파일:

- `learn3/src/msgs/msg/Status.msg`
- `learn3/src/msgs/srv/Compute.srv`
- `learn3/src/msgs/CMakeLists.txt`
- `learn3/src/nodes/src/talker.cpp`
- `learn3/src/nodes/src/listener.cpp`
- `learn3/src/nodes/src/calc_server.cpp`

학습 내용:

- 인터페이스 전용 패키지(`msgs`)와 노드 패키지(`nodes`) 분리.
- `rosidl_generate_interfaces()`로 커스텀 message/service 생성.
- 커스텀 메시지 `Status` 정의:
  - `string name`
  - `int32 level`
  - `string message`
- 커스텀 서비스 `Compute` 정의:
  - request: `int32 a`, `int32 b`, `string operation`
  - response: `float64 result`
- 생성된 헤더 `msgs/msg/status.hpp`, `msgs/srv/compute.hpp` 사용.
- `add`, `sub`, `mul`, `div` operation 분기 처리.

구현 산출물:

- `status` topic에 센서 상태를 주기적으로 발행하는 `talker`.
- `status` topic을 구독해 상태 로그를 출력하는 `listener`.
- `compute` service로 사칙연산을 수행하는 `calc_server`.

### learn4: ROS 2 action

근거 파일:

- `learn4/src/msgs/action/Countdown.action`
- `learn4/src/nodes/src/server.cpp`
- `learn4/src/nodes/src/client.cpp`

학습 내용:

- 커스텀 action 정의:
  - goal: `int32 target_seconds`
  - result: `string message`
  - feedback: `int32 remaining`
- `rclcpp_action::create_server`와 action server callback 3종:
  - goal callback
  - cancel callback
  - accepted callback
- action 실행을 별도 thread로 분리.
- `GoalHandle`을 통해 feedback 발행, cancel 처리, succeed/canceled 결과 반환.
- `rclcpp_action::create_client`로 action client 작성.
- goal response, feedback, result callback 사용.

구현 산출물:

- 초 단위 countdown action server.
- 5초 countdown goal을 보내고 feedback/result를 출력하는 client.
- cancel 요청을 받을 수 있는 action server 구조.

### learn5: launch, 파라미터, topic remap

근거 파일:

- `learn5/msgs/msg/Temperature.msg`
- `learn5/nodes/src/talker.cpp`
- `learn5/nodes/src/listener.cpp`
- `learn5/nodes/launch/basic.launch.py`
- `learn5/nodes/launch/full.launch.py`

학습 내용:

- 커스텀 `Temperature` 메시지 정의:
  - `float64 value`
  - `string unit`
- `declare_parameter()`와 `get_parameter()` 사용.
- publisher 파라미터:
  - `period_ms`
  - `unit`
- subscriber 파라미터:
  - `warn_above`
- launch 파일에서 여러 노드 동시 실행.
- `DeclareLaunchArgument`와 `LaunchConfiguration`.
- 노드 이름 override:
  - `temp_talker`
  - `temp_listener`
- topic remapping:
  - 코드 내부 topic과 launch remap을 통해 `/sensor/temp`로 연결.

구현 산출물:

- 랜덤 온도값을 발행하는 `talker`.
- threshold 이상이면 `RCLCPP_WARN`, 아니면 `RCLCPP_INFO`를 출력하는 `listener`.
- 기본 launch와 full launch 두 종류.

### learn6: ROS 2 파라미터 서버와 YAML 설정

근거 파일:

- `learn6/src/nodes/src/heater.cpp`
- `learn6/src/nodes/config/heater.yaml`
- `learn6/src/nodes/launch/heater.launch.py`

학습 내용:

- `target_temp`, `mode`, `power` 파라미터 선언.
- `rcl_interfaces::msg::ParameterDescriptor` 사용.
- `IntegerRange`로 `power` 범위를 0부터 100까지 제한.
- `add_on_set_parameters_callback()`으로 런타임 파라미터 변경 검증.
- `mode` 값을 `auto|heat|cool` 중 하나로 제한.
- YAML 파일에서 노드 파라미터 주입:
  - `target_temp: 25.0`
  - `power: 80`
  - `mode: "heat"`
- launch에서 `get_package_share_directory()`로 config 파일 경로 resolve.

구현 산출물:

- 3초마다 현재 heater state를 출력하는 파라미터 기반 노드.
- 잘못된 mode 변경을 reject하는 검증 callback.

### learn7: TF2 기본

근거 파일:

- `learn7/src/nodes/src/static_broadcaster.cpp`
- `learn7/src/nodes/src/mover.cpp`
- `learn7/src/nodes/src/tracker.cpp`
- `learn7/src/nodes/launch/tf_demo.launch.py`

학습 내용:

- 정적 TF 발행:
  - `base_link -> lidar_link`
  - translation `(0.1, 0.0, 0.3)`
  - identity quaternion
- 동적 TF 발행:
  - `odom -> base_link`
  - 반지름 2.0, 각속도 0.5 기반 원운동
  - yaw를 quaternion으로 직접 구성
- TF listener 구성:
  - `tf2_ros::Buffer`
  - `tf2_ros::TransformListener`
  - `lookupTransform("odom", "lidar_link", tf2::TimePointZero)`
- TF lookup 실패 시 `TransformException` 처리.
- launch 파일에서 static broadcaster, mover, tracker 동시 실행.

구현 산출물:

- `odom -> base_link -> lidar_link` frame tree.
- 움직이는 robot base와 lidar 위치를 TF로 추적하는 tracker.

### learn8: URDF/Xacro와 RViz 로봇 모델 표시

근거 파일:

- `learn8/src/robot_desc/urdf/robot.urdf`
- `learn8/src/robot_desc/urdf/robot.xacro`
- `learn8/src/robot_desc/launch/display.launch.py`
- `learn8/src/robot_desc/launch/display_xacro.launch.py`
- `learn8/src/robot_desc/rviz/config.rviz`

학습 내용:

- URDF link/joint 기본 구조.
- `base_link`, `lidar_link`, `wheel_left`, `wheel_right` 구성.
- fixed joint와 continuous joint 차이.
- link visual geometry:
  - box body
  - cylinder lidar
  - cylinder wheels
- Xacro macro 사용:
  - wheel macro로 좌/우 바퀴 중복 제거.
  - material 정의 재사용.
- `robot_state_publisher`로 `robot_description` publish.
- `joint_state_publisher_gui`로 continuous joint 시각화.
- RViz에서 로봇 모델 확인.

구현 산출물:

- 단순 2륜 로봇 URDF.
- 같은 모델을 Xacro로 리팩터링한 버전.
- URDF 직접 로드 launch와 Xacro 처리 launch.

### learn9: Gazebo Sim + ROS bridge

근거 파일:

- `learn9/src/sim/urdf/robot.urdf.xacro`
- `learn9/src/sim/worlds/room.sdf`
- `learn9/src/sim/config/bridge.yaml`
- `learn9/src/sim/launch/sim.launch.py`

학습 내용:

- Gazebo Sim용 Xacro 확장:
  - collision/inertial 추가.
  - box/cylinder inertia macro 작성.
  - `base_footprint`, `base_link`, `lidar_link`, wheels, caster 구성.
- Gazebo sensor:
  - `gpu_lidar`
  - 360 samples
  - range 0.12부터 10.0
  - topic `scan`
- Gazebo DiffDrive plugin:
  - left/right wheel joint 연결.
  - `cmd_vel`, `odom`, `tf` topic 설정.
  - `frame_id=odom`, `child_frame_id=base_footprint`.
- Gazebo JointStatePublisher plugin.
- SDF world 구성:
  - 5x5 방
  - 네 방향 벽
  - 중앙 pillar 장애물
  - sensors/physics/user commands/scene broadcaster plugin.
- `ros_gz_bridge` 설정:
  - `/clock`
  - `/scan`
  - `/cmd_vel`
  - `/odom`
  - `/tf`
  - `/joint_states`
- launch에서 Gazebo server only mode 실행:
  - `gz_args: -r -s <world>`
- `ros_gz_sim create`로 robot spawn.
- RViz optional launch argument.

구현 산출물:

- 라이다와 차동구동이 포함된 Gazebo 로봇 시뮬레이션.
- ROS 2 topic으로 scan/odom/tf/cmd_vel을 연결하는 bridge.

### learn10: SLAM Toolbox mapping

근거 파일:

- `learn10/src/sim/launch/sim.launch.py`
- `learn10/src/sim/launch/slam.launch.py`
- `learn10/src/sim/config/slam.yaml`
- `learn10/maps/room.yaml`
- `learn10/maps/room.pgm`

학습 내용:

- `learn9`의 Gazebo simulation을 기반으로 SLAM Toolbox 연결.
- `slam_toolbox`의 `online_async_launch.py` include.
- `use_sim_time=true`.
- 주요 frame 설정:
  - `odom_frame: odom`
  - `map_frame: map`
  - `base_frame: base_footprint`
  - `scan_topic: /scan`
- mapping mode 설정.
- map resolution 0.05m/cell.
- scan matching 설정:
  - `use_scan_matching`
  - `minimum_travel_distance`
  - `minimum_travel_heading`
  - scan buffer size/distance
- loop closure 설정:
  - `do_loop_closing`
  - loop search distance
  - coarse/fine response threshold.
- correlation matcher와 angle/distance penalty 튜닝.
- RViz config와 mapping 결과 map 저장.

구현 산출물:

- Gazebo 방 환경에서 `/scan`과 `/odom`을 이용한 SLAM Toolbox mapping launch.
- 저장된 occupancy grid map: `room.yaml`, `room.pgm`.

### task1: ROS 2 통신 종합 과제

근거 파일:

- `task1/src/msgs/msg/Temperature.msg`
- `task1/src/msgs/srv/GetAverage.srv`
- `task1/src/nodes/src/sensor.cpp`
- `task1/src/nodes/src/monitor.cpp`

학습 내용:

- 커스텀 msg와 service를 함께 사용하는 종합 과제.
- `Temperature` 메시지:
  - `string name`
  - `float64 temperature`
  - `int32 time`
- `GetAverage` 서비스:
  - request 없음
  - response `float64 temperature`
- sensor node:
  - 1초마다 20도부터 40도 사이 랜덤 온도 발행.
  - timestamp counter 증가.
- monitor node:
  - temperature topic 구독.
  - 누적 합과 count 관리.
  - `get_average` service로 평균 온도 반환.

과제 성격:

- `learn1`, `learn3`, `learn5`에서 배운 pub/sub, custom msg, custom service를 하나의 작은 시스템으로 합친 점검 과제.

### sim2d: 2D landmark simulator 모듈화

근거 파일:

- `sim2d/README.md`
- `sim2d/include/sim2d/sim.hpp`
- `sim2d/src/sim.cpp`
- `sim2d/examples/basic_loop.cpp`
- `sim2d/tests/smoke.cpp`

학습 내용:

- EKF/GUI/ROS/Eigen에 의존하지 않는 순수 2D simulation core 분리.
- simulator가 소유하는 world truth:
  - robot pose
  - landmark map
  - range/bearing sensor model
  - noisy odometry sampling
  - deterministic seed
- estimator는 외부에 두고 `StepResult`를 소비하는 구조.
- simulation state와 view/output helper 분리.

의미:

- `learn12` 이후의 2D SLAM 아이디어를 재사용 가능한 작은 라이브러리로 추출한 연습으로 보인다.

### learn11: 1D EKF-SLAM

근거 파일:

- `learn11/src/ekf.hpp`
- `learn11/src/ekf.cpp`
- `learn11/src/sim.hpp`
- `learn11/src/sim.cpp`
- `learn11/src/main.cpp`

학습 내용:

- 1차원 EKF-SLAM 상태 구성:
  - `x[0]`: robot position
  - `x[1...]`: landmark positions
  - `P`: 전체 covariance matrix
- prediction:
  - robot position에 control `u` 추가.
  - robot variance에 `sigma_u^2` 추가.
- measurement model:
  - landmark measurement `z = landmark - robot`.
  - Jacobian `H`: robot에 -1, 해당 landmark에 +1.
- Kalman update:
  - innovation covariance `S`
  - Kalman gain `K`
  - state update `x += K * innovation`
  - Joseph form covariance update.
- covariance 대칭화와 최소 분산 clamp.
- 새 landmark 추가 시 state vector와 covariance matrix 확장.
- ImGui/ImPlot 기반 시각화:
  - noise slider
  - landmark 위치 편집
  - step control
  - true robot, EKF robot, true landmarks 표시.

구현 산출물:

- `EKF SLAM 1D` GUI 앱.
- 움직임/측정 noise가 EKF 추정과 covariance에 주는 영향을 실험하는 환경.

### learn12: 2D EKF-SLAM

근거 파일:

- `learn12/src/ekf2d.hpp`
- `learn12/src/ekf2d.cpp`
- `learn12/src/sim/sim2d.hpp`
- `learn12/src/sim/sim2d.cpp`
- `learn12/src/sim/sim_view.cpp`
- `learn12/sim_config.ini`

학습 내용:

- 2D robot pose state:
  - `x`, `y`, `theta`
- landmark state:
  - landmark마다 `(lx, ly)` 2차원 좌표.
- prediction:
  - `dist`, `dtheta` 기반 pose update.
  - motion Jacobian `G`.
  - `sigma_v`, `sigma_w`를 pose covariance에 반영.
- measurement model:
  - range `r`
  - bearing `phi`
  - `atan2`, angle wrap 처리.
- update:
  - 2xN measurement Jacobian `H`.
  - measurement covariance `R = diag(sigma_r^2, sigma_phi^2)`.
  - innovation bearing wrap.
  - Joseph form covariance update.
- landmark initialization:
  - robot pose와 range/bearing에서 world landmark 좌표 생성.
  - robot pose Jacobian `J_xr`.
  - measurement Jacobian `J_z`.
  - 새 landmark covariance block 계산.
- sensor model:
  - max range
  - field of view half angle
  - range/bearing noise
- true landmark와 EKF landmark index mapping.
- ImGui/ImPlot GUI:
  - motion noise, sensor noise, landmark count/range 조정.
  - auto/manual teleop.
  - ROS teleop 스타일 키 입력.
  - 마우스로 landmark 추가/삭제.
  - true trajectory와 estimated trajectory 표시.
  - covariance ellipse.
  - covariance matrix heatmap.
  - P matrix values table.

구현 산출물:

- `EKF SLAM 2D` GUI 앱.
- 2D landmark 기반 EKF-SLAM의 prediction/update/landmark augmentation을 직접 관찰하는 실험 환경.

### task2 및 learn13: Monte Carlo Localization

근거 파일:

- `task2/include/mcl.hpp`
- `task2/src/mcl.cpp`
- `task2/src/sim/sim_view.cpp`
- `learn13/src/mcl.hpp`
- `learn13/src/mcl.cpp`
- `learn13/src/sim/sim2d.cpp`
- `learn13/src/sim/sim_view.cpp`
- `learn13/sim_config.ini`

학습 내용:

- Particle filter 기반 localization 구현.
- particle state:
  - `x`
  - `y`
  - `theta`
  - `weight`
  - `log_weight`
- known landmark map을 기준으로 localization 수행.
- initialization:
  - Gaussian particle initialization.
  - `learn13`에서는 uniform initialization도 제공.
- prediction:
  - motion command `dist`, `dtheta`.
  - motion noise `sigma_v`, `sigma_w`.
  - mid-heading 방식으로 이동량 반영.
- observation likelihood:
  - 각 particle에서 landmark의 expected range/bearing 계산.
  - range residual, bearing residual.
  - Gaussian log likelihood 누적.
  - log-sum-exp 스타일 정규화로 underflow 완화.
- resampling:
  - cumulative distribution.
  - systematic resampling.
  - resampling 후 weight reset.
- degeneracy 판단:
  - `N_eff = 1 / sum(w_i^2)`.
  - `N_eff < M/2`이면 resampling.
- mean pose:
  - x/y는 weight 평균.
  - theta는 sin/cos weighted average.
- GUI:
  - particle 표시.
  - true landmarks와 known map 표시.
  - FOV 표시.
  - effective N plot.
  - pose error plot.
  - MCL update on/off.
  - uniform/gaussian particle reset.
  - kidnap 실험.
  - keyboard teleop.

과제 성격:

- `task2`는 MCL 구현 과제 또는 중간 산출물로 보인다.
- `learn13`은 같은 개념을 더 정돈된 구조와 GUI control로 확장한 수업 단계로 보인다.

### learn13-5: OpenMP MCL 병렬화와 성능 측정

근거 파일:

- `learn13-5/include/mcl_omp.hpp`
- `learn13-5/src/mcl_omp.cpp`
- `learn13-5/src/timing.cpp`
- `learn13-5/src/omp_check.cpp`
- `learn13-5/src/sim/sim_view.cpp`

학습 내용:

- 직렬 MCL과 OpenMP MCL 비교.
- `MCL_OMP` 구현:
  - thread별 random generator vector.
  - `#pragma omp parallel` prediction.
  - `#pragma omp parallel for` weight 계산.
  - prefix sum 기반 CDF 계산.
  - parallel resample buffer 채우기.
- OpenMP thread 수 조절:
  - `omp_get_max_threads`
  - `omp_set_num_threads`
  - GUI slider로 thread 수 조정.
- 직렬/병렬 mode 전환:
  - `MCL`
  - `MCL_OMP`
- mode 전환 시 filter state 복사.
- timing 측정:
  - predict time
  - measure time
  - observe/update time
  - total time
  - mean, median, p95, min, max.
- GUI 성능 표:
  - latest
  - mean
  - p95
  - predict
  - update
- step timing plot.

구현 산출물:

- 같은 MCL 로직을 직렬/병렬로 실행하며 성능 차이를 측정하는 GUI 앱.
- OpenMP 동작 확인용 `omp_check`.

### learn14: FastSLAM과 benchmark

근거 파일:

- `learn14/include/fastslam.hpp`
- `learn14/src/fastslam.cpp`
- `learn14/include/particle.hpp`
- `learn14/src/particle.cpp`
- `learn14/include/landmarkEKF.hpp`
- `learn14/include/benchmark.hpp`
- `learn14/src/benchmark.cpp`
- `learn14/src/sim_view.cpp`
- `learn14/src/benchmark_view.cpp`
- `learn14/sim_config.ini`
- `learn14/benchmark_config.ini`

학습 내용:

- FastSLAM 구조:
  - particle가 robot pose뿐 아니라 landmark map도 보유.
  - 각 landmark는 `LandmarkEKF`로 관리.
  - particle별 landmark vector.
- landmark EKF:
  - landmark mean `mu`.
  - landmark covariance `sigma`.
  - seen flag.
- landmark initialization:
  - particle pose와 range/bearing에서 landmark world coordinate 계산.
  - measurement noise를 landmark covariance로 변환.
- landmark update:
  - expected range/bearing.
  - 2x2 Jacobian.
  - innovation covariance `S`.
  - Kalman gain.
  - Joseph form covariance update.
  - measurement likelihood를 log weight에 반영.
- FastSLAM particle update:
  - motion prediction.
  - observation마다 landmark init/update.
  - weight normalization.
  - `N_eff` 기준 resampling.
- FastSLAM statistics:
  - last resampled 여부.
  - pre/post resample effective N.
  - log weight min/max/span.
  - mean pose.
  - weighted mean landmarks.
- GUI:
  - true trajectory, particles, true landmarks.
  - mean landmarks.
  - best particle map.
  - covariance ellipses.
  - FOV display.
  - selected particle 표시.
  - pose RMSE, landmark RMSE, effective N timeseries.
  - config 저장/로드.
- benchmark:
  - particle count sweep: `10,100,500,5000,20000`.
  - multiple random seeds.
  - steps, dt, metric interval 설정.
  - motion patterns: `circle`, `straight`, `spin`, `figure8`, `square`.
  - pose RMSE, mean landmark RMSE, best particle landmark RMSE.
  - effective N, log weight span, resample rate.
  - timeseries CSV 저장.

구현 산출물:

- `learn14 FastSLAM` GUI 앱.
- `learn14_benchmark` 또는 benchmark viewer 성격의 실행 파일.
- `benchmark_timeseries.csv` 산출물.

### learn15: 직접 구현한 MCL의 ROS 2 통합

근거 파일:

- `learn15/src/mcl_msgs/msg/Landmark.msg`
- `learn15/src/mcl_msgs/msg/LandmarkArray.msg`
- `learn15/src/learn15/src/ros/sim2d_node.cpp`
- `learn15/src/learn15/src/ros/mcl_node.cpp`
- `learn15/src/learn15/src/mcl.cpp`
- `learn15/src/learn15/launch/mcl_demo.launch.py`
- `learn15/src/learn15/rviz/mcl_demo.rviz`

학습 내용:

- 알고리즘 core와 ROS node 분리:
  - `mcl_core` library.
  - `mcl` executable.
  - `sim2d` executable.
- 커스텀 ROS 메시지:
  - `Landmark`: `id`, `range`, `bearing`.
  - `LandmarkArray`: `std_msgs/Header`, `Landmark[]`.
- `sim2d` ROS node:
  - world landmark 생성.
  - true pose와 noisy odom pose 분리.
  - `/odom` 발행.
  - `odom -> base_link` TF 발행.
  - `/landmarks`에 base frame 기준 range/bearing 관측 발행.
  - `/landmark_markers`에 RViz MarkerArray 발행.
  - `/ground_truth` pose 발행.
  - odom rate와 landmark rate를 별도 timer로 운영.
- `mcl` ROS node:
  - `/odom` 구독.
  - 이전 odom pose와 현재 odom pose 차이로 `dd`, `dtheta` 계산.
  - MCL prediction 수행.
  - `/landmarks` 구독.
  - LandmarkArray를 internal `Observation`으로 변환.
  - MCL observe/update 수행.
  - `/mcl/pose` 발행.
  - `/mcl/particles` PoseArray 발행.
  - `map -> odom` TF 발행.
  - TF buffer/listener로 `odom -> base_link` lookup.
- RViz config:
  - fixed frame `map`.
  - Grid.
  - Ground Truth.
  - Landmarks MarkerArray.
  - MCL Particles PoseArray.
  - MCL Pose.
- launch:
  - `sim2d`, `mcl`, `rviz2` 동시 실행.
  - particle 수, noise, landmark count/rate 등 파라미터 주입.

구현 산출물:

- GUI 앱에 머물던 MCL을 ROS 2 node graph로 옮긴 최종 통합 실습.
- RViz에서 true pose, landmarks, particles, estimated pose를 보는 데모.

## 배운 기술 스택

ROS 2:

- `rclcpp`
- `std_msgs`, `geometry_msgs`, `nav_msgs`, `sensor_msgs`, `tf2_msgs`
- `rclcpp_action`
- `tf2`, `tf2_ros`, `tf2_geometry_msgs`
- `visualization_msgs`
- `rosidl_default_generators`
- `ament_cmake`
- launch Python API
- `robot_state_publisher`
- `joint_state_publisher_gui`
- `rviz2`
- `ros_gz_sim`
- `ros_gz_bridge`
- `slam_toolbox`

C++/수치/시각화:

- C++17.
- Eigen matrix/vector 연산.
- ImGui/ImPlot GUI.
- GLFW/OpenGL.
- OpenMP 병렬화.
- random number generation.
- covariance matrix, Jacobian, Kalman gain, log likelihood, log-sum-exp, systematic resampling.

로봇/SLAM 개념:

- ROS node lifecycle.
- topic/service/action 통신 모델.
- custom interface generation.
- launch orchestration.
- runtime parameters and YAML config.
- frame tree and transform lookup.
- URDF/Xacro robot modeling.
- Gazebo sensor/differential drive simulation.
- ROS-Gazebo topic bridge.
- occupancy grid mapping.
- EKF-SLAM.
- Monte Carlo Localization.
- FastSLAM.
- particle degeneracy and resampling.
- landmark data association이 이미 id로 주어진 상황에서의 SLAM/localization.
- RViz visualization and TF integration.

## 과제/마일스톤으로 보이는 지점

### task1

ROS 2 기본 통신 종합 과제다. 커스텀 온도 메시지를 발행하는 sensor와 평균 온도를 반환하는 monitor service를 구현했다. pub/sub, custom msg, custom srv, state accumulation을 한 번에 확인한다.

### task2

MCL 구현 과제로 보인다. `learn13`과 유사하게 known landmark map, particle prediction, observation likelihood, resampling, GUI visualization을 다룬다. 다만 `learn13` 쪽이 더 정돈된 확장판처럼 보이며, `task2`는 과제 제출용 또는 중간 구현본에 가까워 보인다.

## 커리큘럼 난이도 상승 구조

1. `learn1`-`learn2`: ROS 2 C++ 통신의 최소 단위.
2. `learn3`-`learn4`: 직접 만든 인터페이스와 action까지 확장.
3. `learn5`-`learn6`: 실제 실행 관리에 필요한 launch, parameter, YAML.
4. `learn7`-`learn8`: 로봇 좌표계와 로봇 모델.
5. `learn9`-`learn10`: 실제 로봇 시스템처럼 sensor, odom, tf, map을 연결하는 simulation stack.
6. `learn11`-`learn12`: SLAM 알고리즘을 직접 수학적으로 구현.
7. `task2`/`learn13`: particle filter localization으로 확률적 추정 방식 확장.
8. `learn13-5`: 같은 알고리즘을 성능 관점에서 병렬화하고 측정.
9. `learn14`: localization에서 SLAM으로 확장한 FastSLAM.
10. `learn15`: 직접 구현한 알고리즘을 ROS 2 node graph와 RViz로 통합.

## 최종적으로 쌓은 역량

이 코드 기준으로 보면, 단순 ROS 예제 수준을 넘어 다음 역량까지 훈련한 커리큘럼이다.

- ROS 2 C++ 패키지를 직접 만들고 빌드/설치할 수 있다.
- topic/service/action 통신을 각각 구현할 수 있다.
- custom msg/srv/action을 정의하고 노드에서 사용할 수 있다.
- launch 파일로 여러 노드, 파라미터, remap을 구성할 수 있다.
- TF tree를 발행하고 lookup할 수 있다.
- URDF/Xacro로 로봇 모델을 만들고 RViz에 표시할 수 있다.
- Gazebo Sim에서 라이다/차동구동 로봇을 구성하고 ROS topic으로 bridge할 수 있다.
- SLAM Toolbox로 mapping pipeline을 띄우고 map을 저장할 수 있다.
- EKF-SLAM의 prediction/update/landmark augmentation을 직접 구현할 수 있다.
- MCL의 particle prediction, likelihood weighting, effective sample size, systematic resampling을 직접 구현할 수 있다.
- OpenMP로 particle filter를 병렬화하고 성능을 측정할 수 있다.
- FastSLAM에서 particle별 landmark EKF map을 유지하고 benchmark할 수 있다.
- 직접 구현한 localization 알고리즘을 ROS 2 node로 감싸서 `/odom`, `/landmarks`, `/mcl/pose`, `/mcl/particles`, `map -> odom` TF와 연결할 수 있다.

## 한 줄 결론

이 레포는 "ROS 2 C++ 기초 + 로봇 모델/시뮬레이션 + SLAM Toolbox 실습 + EKF/MCL/FastSLAM 직접 구현 + ROS 통합"까지 이어지는 모바일 로봇 SLAM 실습 커리큘럼의 산출물로 보는 것이 가장 자연스럽다.
