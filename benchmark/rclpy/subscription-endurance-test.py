#!/usr/bin/env python3
# Copyright (c) 2018 Intel Corporation. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import rclpy
from sensor_msgs.msg import *

def callback(msg):
  pass

def main():
  rclpy.init()

  node = rclpy.create_node('endurance_subscription_rclpy')
  publisher = node.create_subscription(JointState, 'endurance_topic', callback)
  while rclpy.ok():
    rclpy.spin_once(node)

if __name__ == '__main__':
  main()

