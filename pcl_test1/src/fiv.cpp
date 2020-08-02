#include <chrono>
#include <ctime>
#include <iostream>
#include <pcl/impl/point_types.hpp>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <random>
#include <thread>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace std;

int main(int argc, char **argv) {
  cout << "hi" << endl;

  const size_t _sz = 1024;
  pcl::PointCloud<pcl::PointXYZRGB> cloud1;

  cloud1.width = _sz;
  cloud1.height = 1;
  cloud1.is_dense = false;

  std::mt19937 _mt_19937{unsigned(time(0))};
  std::uniform_real_distribution<float> rng_pos{0, _sz};
  std::uniform_int_distribution<uint8_t> rng_clr{0, 255};
  for (int i = 0; i < _sz; ++i) {
    cloud1.points.emplace_back(rng_pos(_mt_19937), rng_pos(_mt_19937),
                               rng_pos(_mt_19937), rng_clr(_mt_19937),
                               rng_clr(_mt_19937), rng_clr(_mt_19937));
  }

  pcl::visualization::PCLVisualizer viewer;
  viewer.setBackgroundColor(0.86, 0.76, 0.33);

  pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud1_ptr{&cloud1};
  viewer.addPointCloud(cloud1_ptr, "cloud1", 0);
  pcl::PointXYZ center{_sz / 2.f, _sz / 2.f, _sz / 2.f};
  pcl::PointXYZ ori{};

  viewer.addSphere(center, _sz / 5.f, "circle1", 0);

  while (!viewer.wasStopped()) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(300));
    viewer.spinOnce();
  }
  return 0;
}
