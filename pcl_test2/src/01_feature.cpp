#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <Eigen/Eigen>
#include <iostream>
#include <numeric>
#include <pcl/impl/point_types.hpp>
#include <string>

#include <functional>

#include "tadus_pcl_io.hpp"

using namespace pcl;
std::string pcd_dir{"/home/tad/Picture/pcl-pcd/"};
int main(int argc, char** argv) {
    auto file_path = pcd_dir + "bunny.pcd";

    auto ptcd_1 = tadus::pcl_io::getPtcd<pcl::PointXYZ>(file_path);
    pcl::visualization::PCLVisualizer viewer{"visuer"};
    viewer.addPointCloud(ptcd_1, "pt_cd_1");
    viewer.addCoordinateSystem(1.0);

	for (const auto& p: ptcd_1->points) {

		std::cout<<p<<std::endl;
	}
	//std::accumulate(ptcd_1->begin(),ptcd_1->end(),PointXYZ {},[](const PointXYZ& a,const PointXYZ& b) {});

    while (viewer.wasStopped() == false) {
        viewer.spinOnce();
    }

    return 0;
}
