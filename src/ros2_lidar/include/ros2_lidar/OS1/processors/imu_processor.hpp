// Copyright 2020, Steve Macenski
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ROS2_lidar__OS1__PROCESSORS__IMU_PROCESSOR_HPP_
#define ROS2_lidar__OS1__PROCESSORS__IMU_PROCESSOR_HPP_

#include <vector>
#include <memory>
#include <string>

#include "ros2_lidar/conversions.hpp"

#include "rclcpp/qos.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"
#include "sensor_msgs/msg/imu.hpp"

#include "ros2_lidar/interfaces/data_processor_interface.hpp"

namespace OS1
{

/**
 * @class OS1::IMUProcessor
 * @brief A data processor interface implementation of a processor
 * for creating IMU in the driver in ROS2.
 */
class IMUProcessor : public ros2_lidar::DataProcessorInterface
{
public:
  /**
   * @brief A constructor for OS1::IMUProcessor
   * @param node Node for creating interfaces
   * @param mdata metadata about the sensor
   * @param frame frame_id to use for messages
   */
  IMUProcessor(
    const rclcpp_lifecycle::LifecycleNode::SharedPtr node,
    const ros2_lidar::Metadata & mdata,
    const std::string & frame,
    const rclcpp::QoS & qos)
  : DataProcessorInterface(), _node(node), _frame(frame)
  {
    _pub = node->create_publisher<sensor_msgs::msg::Imu>("imu", qos);
  }

  /**
   * @brief A destructor clearing memory allocated
   */
  ~IMUProcessor()
  {
    _pub.reset();
  }

  /**
   * @brief Process method to create imu
   * @param data the packet data
   */
  bool process(uint8_t * data, uint64_t override_ts) override
  {
    if (_pub->get_subscription_count() > 0 && _pub->is_activated()) {
      _pub->publish(ros2_lidar::toMsg(data, _frame, override_ts));
    }
    return true;
  }

  /**
   * @brief Activating processor from lifecycle state transitions
   */
  void onActivate() override
  {
    _pub->on_activate();
  }

  /**
   * @brief Deactivating processor from lifecycle state transitions
   */
  void onDeactivate() override
  {
    _pub->on_deactivate();
  }

private:
  rclcpp_lifecycle::LifecyclePublisher<sensor_msgs::msg::Imu>::SharedPtr _pub;
  rclcpp_lifecycle::LifecycleNode::SharedPtr _node;
  std::string _frame;
};

}  // namespace OS1

#endif  // ROS2_lidar__OS1__PROCESSORS__IMU_PROCESSOR_HPP_
