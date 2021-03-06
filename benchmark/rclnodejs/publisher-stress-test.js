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

'use strict';

/* eslint-disable camelcase */
const rclnodejs = require('../../index.js');

const message = {
  layout: {
    dim: [
      {label: 'height',  size: 10, stride: 600},
      {label: 'width',   size: 20, stride: 60},
      {label: 'channel', size: 3,  stride: 4},
    ],
    data_offset: 0,
  },
  data: Uint8Array.from({length: 1024 * 1024 * 10}, (v, k) => k)
};

rclnodejs.init().then(() => {
  console.log(
    'The publisher will publish a UInt8MultiArray topic(contains a size of 10MB array) every 100ms.');
  console.log(`Begin at ${new Date().toString()} and end in about 1 hour.`);

  let node = rclnodejs.createNode('stress_publisher_rclnodejs');
  const publisher = node.createPublisher('std_msgs/msg/UInt8MultiArray', 'stress_topic');
  let sentTimes = 0;
  let totalTimes = 36000;

  let timer = setInterval(() => {
    if (sentTimes++ > totalTimes) {
      clearInterval(timer);
      rclnodejs.shutdown();
      console.log(`End at ${new Date().toString()}`);
    } else {
      publisher.publish(message);
    }}, 100);
  rclnodejs.spin(node);
}).catch((err) => {
  console.log(err);
});
