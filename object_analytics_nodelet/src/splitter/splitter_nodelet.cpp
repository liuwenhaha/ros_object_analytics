/*
 * Copyright (c) 2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <pluginlib/class_list_macros.h>

#include "object_analytics_nodelet/const.h"
#include "object_analytics_nodelet/splitter/splitter_nodelet.h"

namespace object_analytics_nodelet
{
namespace splitter
{
void SplitterNodelet::onInit()
{
  ros::NodeHandle nh = getNodeHandle();
  sub_pc2_ = nh.subscribe(Const::kTopicRegisteredPC2, 1, &SplitterNodelet::cbSplit, this);
  pub_2d_ = nh.advertise<sensor_msgs::Image>(Const::kTopicRgb, 1);
  pub_3d_ = nh.advertise<sensor_msgs::PointCloud2>(Const::kTopicPC2, 1);
}

void SplitterNodelet::cbSplit(const sensor_msgs::PointCloud2::ConstPtr& points)
{
  sensor_msgs::ImagePtr image(new sensor_msgs::Image);
  Splitter::split(points, image);
  pub_2d_.publish(image);
  pub_3d_.publish(points);
}
}  // namespace splitter
}  // namespace object_analytics_nodelet
PLUGINLIB_EXPORT_CLASS(object_analytics_nodelet::splitter::SplitterNodelet, nodelet::Nodelet)
