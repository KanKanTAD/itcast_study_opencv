#include <pcl/common/transforms.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/pcl_macros.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/point_cloud_color_handlers.h>

#include <Eigen/Eigen>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <pcl/impl/point_types.hpp>
#include <string>
#include <thread>

#include "utils.hpp"

using namespace std;

int main(int argc, char** argv) {
    pcl::visualization::PCLVisualizer viewer{"viewer"};

    std::string rops_file_path{"/home/tad/Picture/pcl-pcd/rops_cloud.pcd"};

    auto rops_cloud = utils::ptcldFromFile<pcl::PointXYZ>(rops_file_path);

    auto _minmax0 = utils::axis_minmax(*rops_cloud, 0);
    cout << _minmax0.first << ";" << _minmax0.second << endl;
    viewer.addPointCloud(rops_cloud);

    auto trans_cloud =
        utils::pass_filte(*rops_cloud, 0, {_minmax0.first + 0.2f, _minmax0.second - 0.2f});
    for (auto& p : trans_cloud->points) {
        p.x += 0.8f;
    }

    auto trans_color = utils::single_color(*trans_cloud, {128, 128, 0});
    viewer.addPointCloud(trans_cloud, *trans_color, "trans_cloud");

    auto mean_pos = utils::pos_mean(*trans_cloud);
    auto mean_pnt = utils::makePntCld_like(*trans_cloud);
    mean_pnt->points.push_back(mean_pos);

    auto m_p_c = utils::single_color(*mean_pnt, {255, 0, 0});
    viewer.addPointCloud(mean_pnt, *m_p_c, "trans_cloud_mean_pnt");

    while (viewer.wasStopped() == false) {
        viewer.spinOnce();
        pcl_sleep(0.03);
    }

    return 0;
}
