#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "rosgraph_msgs/msg/clock.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include <cmath>

class UnicycleSimulator : public rclcpp::Node
{
public:
  UnicycleSimulator()
  : rclcpp::Node("unicycle_simulator")
  {
    declare_parameter<double>("initial_x", 0.0);
    declare_parameter<double>("initial_y", 0.0);
    declare_parameter<double>("initial_theta", 0.0);
    declare_parameter<double>("odom_frequency", 50.0);   // Hz
    declare_parameter<double>("clock_frequency", 100.0); // Hz

    get_parameter("initial_x", x_);
    get_parameter("initial_y", y_);
    get_parameter("initial_theta", theta_);

    double odom_freq, clock_freq;
    get_parameter("odom_frequency", odom_freq);
    get_parameter("clock_frequency", clock_freq);

    v_ = 0.0;
    omega_ = 0.0;

    cmd_vel_sub_ = create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel", 10,
      [this](const geometry_msgs::msg::Twist::SharedPtr msg) {
        v_ = msg->linear.x;
        omega_ = msg->angular.z;
      });

    odom_pub_ = create_publisher<nav_msgs::msg::Odometry>("/odom", 10);
    clock_pub_ = create_publisher<rosgraph_msgs::msg::Clock>("/clock", 10);

    auto odom_period = std::chrono::duration<double>(1.0 / odom_freq);
    odom_timer_ = create_wall_timer(
      odom_period, [this]() { odomTimerCallback(); });

    auto clock_period = std::chrono::duration<double>(1.0 / clock_freq);
    clock_timer_ = create_wall_timer(
      clock_period, [this]() { clockTimerCallback(); });

    last_update_ = now();

    RCLCPP_INFO(get_logger(), "unicycle_simulator started");
  }

private:
  void odomTimerCallback();
  void clockTimerCallback();

  double x_, y_, theta_;     // robot pose
  double v_, omega_;         // last received velocity command
  rclcpp::Time last_update_;

  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
  rclcpp::Publisher<rosgraph_msgs::msg::Clock>::SharedPtr clock_pub_;
  rclcpp::TimerBase::SharedPtr odom_timer_;
  rclcpp::TimerBase::SharedPtr clock_timer_;
};

void UnicycleSimulator::odomTimerCallback()
{
  rclcpp::Time current_time = now();
  double dt = (current_time - last_update_).seconds();

  double xdot = v_ * std::cos(theta_);
  double ydot = v_ * std::sin(theta_);
  double thetadot = omega_;

  x_     += xdot     * dt;
  y_     += ydot     * dt;
  theta_ += thetadot * dt;

  last_update_ = current_time;

  nav_msgs::msg::Odometry msg;
  msg.header.stamp = current_time;
  msg.header.frame_id = "odom";
  msg.child_frame_id = "base_link";
  msg.pose.pose.position.x = x_;
  msg.pose.pose.position.y = y_;
  msg.pose.pose.position.z = 0.0;

  tf2::Quaternion q;
  q.setRPY(0, 0, theta_);
  msg.pose.pose.orientation = tf2::toMsg(q);

  msg.twist.twist.linear.x = v_;
  msg.twist.twist.angular.z = omega_;

  odom_pub_->publish(msg);
}

void UnicycleSimulator::clockTimerCallback()
{
  rosgraph_msgs::msg::Clock msg;
  msg.clock = now();
  clock_pub_->publish(msg);
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<UnicycleSimulator>());
  rclcpp::shutdown();
  return 0;
}
