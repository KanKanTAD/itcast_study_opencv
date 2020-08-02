#include <chrono>
#include <iostream>
#include <pcl/impl/point_types.hpp>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <thread>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace std;

int main(int argc, char **argv) {
  cout << "hi" << endl;

  pcl::PointCloud<pcl::PointXYZ> cloud1;

  pcl::visualization::PCLVisualizer viewer;
  while (!viewer.wasStopped()) {
    //std::this_thread::sleep_for(std::chrono::milliseconds(300));
		viewer.spinOnce();
  }
  return 0;
}
