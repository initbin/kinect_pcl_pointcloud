#ifndef IMAGE_TO_POINTCLOUD_H_
#define IMAGE_TO_POINTCLOUD_H_

#include <opencv2/opencv.hpp>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <iostream>

const double fx = 525.0;
const double fy = 525.0;
const double cx = 319.5;
const double cy = 239.5;
const double factor = 1000.0;

int pcl_init();

#endif