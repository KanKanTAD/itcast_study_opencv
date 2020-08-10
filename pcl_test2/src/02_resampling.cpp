#include <pcl/pcl_macros.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <iostream>
#include <pcl/impl/point_types.hpp>

#include "utils.hpp"

using namespace pcl;

int main(int argc, char** argv) {
    auto pts       = utils::makePntCld_randCube<PointXYZ>(100, {0.0f, 1.0f});
    auto pts_color = utils::single_color(*pts, {255, 0, 0});

    visualization::PCLVisualizer vis;

    vis.addPointCloud(pts, *pts_color, "pts_1");
    vis.addCoordinateSystem(1.0);

    while (vis.wasStopped() == false) {
        vis.spinOnce();
        pcl_sleep(0.03);
    }
    return 0;
}
