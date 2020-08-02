#include <Eigen/Eigen>
#include <chrono>
#include <iostream>

#include <pcl/impl/point_types.hpp>
#include <pcl/common/transforms.h>
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
  viewer->addPointCloud(cloud1, "cloud1");
  viewer->setPointCloudRenderingProperties(
      pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "cloud1");

  Eigen::Matrix4f transform_1 = Eigen::Matrix4f::Identity();
  Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();

	transform_2.translation() << 1.0,0,0;
	cout<<transform_2.matrix()<<endl;


  while (!viewer->wasStopped()) {
    viewer->spinOnce();
  }
  return 0;
}
