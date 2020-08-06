#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/common/common.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/point_cloud_color_handlers.h>

#include <chrono>
#include <iostream>
#include <pcl/impl/point_types.hpp>
#include <string>
#include <thread>

#include "utils.hpp"
using namespace std;

int main(int argc, char** argv) {
    std::string input_file{"/home/tad/Public/pcl/gitee_pcl/test/pcl_logo.pcd"};
    if (argc >= 2) {
        input_file = argv[1];
    }

    auto cloud_ptr = utils::ptcldFromFile<pcl::PointXYZRGBA>(input_file);

    auto single_color = utils::single_color<pcl::PointXYZRGBA>(*cloud_ptr, {255, 0, 0});
    pcl::visualization::PCLVisualizer viewer{"3d_viewer"};
    viewer.setBackgroundColor(0.67, 0.67, 0.67);
    viewer.addCoordinateSystem();

    viewer.addPointCloud(cloud_ptr, *single_color, "cloud1");
    viewer.setPointCloudRenderingProperties(
        pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud1");

    while (!viewer.wasStopped()) {
        viewer.spinOnce();
    }
    return 0;
}
