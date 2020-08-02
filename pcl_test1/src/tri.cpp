#include <chrono>
#include <iostream>

#include <pcl/impl/point_types.hpp>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/point_cloud_color_handlers.h>
#include <string>
#include <thread>

using namespace std;

int main(int argc, char **argv) {
  cout << "hi" << endl;

  std::string pcd_file_path{"/home/tad/Public/pcl/gitee_pcl/test/bunny.pcd"};
  std::string pcd_file_path2{
      "/home/tad/Public/pcl/gitee_pcl/test/milk_color.pcd"};
  if (argc >= 2) {
    pcd_file_path = argv[1];
  }
  if (argc >= 3) {
    pcd_file_path2 = argv[2];
  }

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1{
      new pcl::PointCloud<pcl::PointXYZ>};
  pcl::io::loadPCDFile(pcd_file_path, *cloud1);

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2{
      new pcl::PointCloud<pcl::PointXYZ>};
  pcl::io::loadPCDFile(pcd_file_path2, *cloud2);

  pcl::visualization::PCLVisualizer::Ptr viewer{
      new pcl::visualization::PCLVisualizer{"3D_Viewer"}};

  viewer->setBackgroundColor(0.3, 0.3, 0.3, 0);

  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> singleColor{
      255, 255, 0};
  viewer->addPointCloud(cloud1, singleColor, "cloud1");

  while (!viewer->wasStopped()) {
    viewer->spinOnce();
    //std::this_thread::sleep_for(std::chrono::milliseconds(300));
  }
  return 0;
}
