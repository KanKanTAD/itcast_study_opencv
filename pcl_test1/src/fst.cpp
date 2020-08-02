#include <iostream>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization//cloud_viewer.h>

using namespace std;

int main(int argc, char **argv) {
  cout << "hi" << endl;

  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud{
      new pcl::PointCloud<pcl::PointXYZRGBA>};
	pcl::io::loadPCDFile("/home/tad/Public/pcl/gitee_pcl/test/pcl_logo.pcd",*cloud);

	pcl::visualization::CloudViewer viewer {"cloud viewer"};

	viewer.showCloud(cloud);

	while (!viewer.wasStopped()) {
		;
	}
  return 0;
}
