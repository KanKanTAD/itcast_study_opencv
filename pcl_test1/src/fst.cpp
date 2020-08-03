#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/common/common.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/point_cloud_color_handlers.h>

#include <chrono>
#include <iostream>
#include <pcl/impl/point_types.hpp>
#include <string>
#include <thread>

using namespace std;

int main(int argc, char** argv) {
    std::string input_file{"/home/tad/Public/pcl/gitee_pcl/test/pcl_logo.pcd"};
    if (argc >= 2) {
        input_file = argv[1];
    }

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud{new pcl::PointCloud<pcl::PointXYZRGBA>};
    pcl::io::loadPCDFile(input_file, *cloud);

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGBA> single_color{cloud, 255, 255, 0};

    pcl::visualization::PCLVisualizer viewer{"3d_viewer"};
    viewer.addCoordinateSystem();

    viewer.addPointCloud(cloud, single_color, "cloud1");
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud1");

    while (!viewer.wasStopped()) {
        viewer.spinOnce();
    }
    return 0;
}
