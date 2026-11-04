cmake_minimum_required(VERSION 3.8)
project(unicycle_sim)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosgraph_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

# ---- Executable target ----
# add_executable(<target_name> <source files>) compiles these .cpp files
# into a binary named <target_name>.
add_executable(unicycle_simulator src/unicycle_simulator_node.cpp)

# ament_target_dependencies links the ROS 2 packages found above into this
# target, so #include "rclcpp/rclcpp.hpp" etc. actually resolve at link time.
ament_target_dependencies(unicycle_simulator
  rclcpp
  nav_msgs
  geometry_msgs
  rosgraph_msgs
  tf2
  tf2_geometry_msgs
)

# install(TARGETS ...) tells colcon to copy the built binary into
# install/unicycle_sim/lib/unicycle_sim/, which is where `ros2 run` and
# launch files look for it.
install(TARGETS
  unicycle_simulator
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
