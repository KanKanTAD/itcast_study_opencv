#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/pcl_macros.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <pcl/impl/point_types.hpp>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "utils.hpp"
using namespace std;

int main(int argc, char** argv) {
    pcl::visualization::PCLVisualizer viewer;
    viewer.setBackgroundColor(0.86, 0.76, 0.33);

    auto cloud1 = utils::makePntCld_randCube<pcl::PointXYZ>(1024, {0.0f, 1.0f});
    auto nn_pts = utils::___nn(*cloud1, 500);

    std::vector<pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>::Ptr> vs;
    int i = 0;
    for (auto& cld : *nn_pts) {
        auto clr = utils::single_color(*cld);
        vs.push_back(clr);
        viewer.addPointCloud(cld, *clr, "cloud" + to_string(i++));
    }

    while (!viewer.wasStopped()) {
        viewer.spinOnce();
        pcl_sleep(0.1);
    }
    return 0;
}
