// Copyright (c) 2018 Intel Corporation. All rights reserved.
//
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

#include <chrono>
#include <memory>
#include <utility>

#include "nav_msgs/srv/get_map.hpp"
#include "rclcpp/rclcpp.hpp"
#include "./utilities.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);

  printf(
      "The client will send a GetMap request(response contains a size of 10MB "
      "array) every 100ms until receiving response 36000 times.\n");
  printf("Begin at %s\n", GetCurrentTime());

  auto node = rclcpp::Node::make_shared("stress_client_rclcpp");
  auto client = node->create_client<nav_msgs::srv::GetMap>("get_map");
  auto request = std::make_shared<nav_msgs::srv::GetMap::Request>();
  auto totalTimes = 36000;
  auto receivedTimes = 0;

  while (rclcpp::ok()) {
    if (receivedTimes > totalTimes) {
      rclcpp::shutdown();
      printf("End at %s\n", GetCurrentTime());
    } else {
      client->async_send_request(
          request,
          [&receivedTimes](std::shared_future<
                   std::pair<nav_msgs::srv::GetMap::Request::SharedPtr,
                             nav_msgs::srv::GetMap::Response::SharedPtr>>
                       result) {
                         receivedTimes++;
                         (void)result; });
      rclcpp::spin_some(node);
    }
  }

  return 0;
}
