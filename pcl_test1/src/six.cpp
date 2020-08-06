#include <pcl/visualization/pcl_visualizer.h>

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    pcl::visualization::PCLVisualizer viewer{"viewer"};

    while (!viewer.wasStopped()) {
        viewer.spinOnce();
    }
    return 0;
}
