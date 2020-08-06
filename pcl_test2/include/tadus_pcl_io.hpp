#pragma once

#include <pcl/PCLPointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>

#include <string>

namespace tadus {
namespace pcl_io {

template <typename T>
typename pcl::PointCloud<T>::Ptr getPtcd(const std::string& file_path) {
    typename pcl::PointCloud<T>::Ptr ptr{new pcl::PointCloud<T>{}};
    pcl::io::loadPCDFile(file_path, *ptr);
    return ptr;
}
pcl::PCLPointCloud2Ptr getPtcd2(const std::string& file_path) {
    pcl::PCLPointCloud2Ptr res;
    pcl::io::loadPCDFile(file_path, *res);
    return res;
}
}  // namespace pcl_io
}  // namespace tadus
