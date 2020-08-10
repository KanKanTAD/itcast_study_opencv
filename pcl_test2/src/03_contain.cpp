#include <Eigen/src/Core/Matrix.h>
#include <pcl/features/moment_of_inertia_estimation.h>
#include <pcl/pcl_macros.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <iostream>
#include <pcl/impl/point_types.hpp>

#include "utils.hpp"

int main(int argc, char** argv) {
    std::string file_path = "";
    if (argc >= 2) {
        file_path = argv[1];
    }
    auto cloud = utils::makePntCld<pcl::PointXYZ>();
    if (file_path == "") {
        cloud = utils::makePntCld_randCube<pcl::PointXYZ>(1000, {0.0f, 1.0f});
    } else {
        cloud = utils::loadPCDFile<pcl::PointXYZ>(file_path);
    }

    pcl::MomentOfInertiaEstimation<pcl::PointXYZ> feature_extractor;
    feature_extractor.setInputCloud(cloud);
    feature_extractor.compute();

    pcl::PointXYZ min_point_AABB, max_point_AABB;
    feature_extractor.getAABB(min_point_AABB, max_point_AABB);

	Eigen::Vector3f mass_center;
	feature_extractor.getMassCenter(mass_center);

	float maj,mid,mio;
	feature_extractor.getEigenValues(maj,mid,mio);

	Vector3f maj_vec,mid_vec,mio_vec;
	feature_extractor.getEigenVectors(maj_vec,mid_vec,mio_vec);

    pcl::visualization::PCLVisualizer vis;
    vis.addCoordinateSystem(1.0);

    vis.addCube(min_point_AABB.x,
                max_point_AABB.x,
                min_point_AABB.y,
                max_point_AABB.y,
                min_point_AABB.z,
                max_point_AABB.z,
                255,
                0,
                0,
                "AABB_cube");

    vis.addPointCloud(cloud, "src_cloud");
    while (!vis.wasStopped()) {
        vis.spinOnce();
        pcl_sleep(0.03);
    }
    return 0;
}
