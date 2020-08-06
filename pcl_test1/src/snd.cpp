#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "utils.hpp"

using namespace std;

int main(int argc, char** argv) {
    cout << "load a pcd and show it!" << endl;
    std::string pcd_file_path;
    if (argc >= 2) {
        pcd_file_path = argv[1];
    } else {
        pcd_file_path = "/home/tad/Public/pcl/gitee_pcl/test/pcl_logo.pcd";
    }

    auto cld_ptr = utils::ptcldFromFile<pcl::PointXYZRGBA>(pcd_file_path);
    pcl::visualization::CloudViewer viewer{"cloud viewer"};

    viewer.showCloud(cld_ptr);

    void (*vizCallabel)(pcl::visualization::PCLVisualizer&) =
        [](pcl::visualization::PCLVisualizer& visualizer) {
            static int _cnt = 0;
            std::cout << "cnt:" << _cnt++ << endl;
            cout << "once thread id:" << std::this_thread::get_id() << endl;
        };
    viewer.runOnVisualizationThreadOnce(vizCallabel);

    void (*call_back)(pcl::visualization::PCLVisualizer&) =
        [](pcl::visualization::PCLVisualizer& visualizer) {
            static unsigned long _cnt = 0;
            visualizer.removeShape("text_str", 0);
            visualizer.addText(
                "per viewer loop:" + to_string(_cnt++), 100, 300, 22, 1.0, 1.0, 1.0, "text_str", 0);
            static int x = 0;
            if (!x) {
                cout << "thread id:" << std::this_thread::get_id() << endl;
                x++;
            }
        };

    viewer.runOnVisualizationThread(call_back);

    while (!viewer.wasStopped()) {
        std::this_thread::sleep_for(std::chrono::milliseconds{300});
        static int _once = 0;
        if (!_once) {
            ++_once;
            cout << "while thread id:" << this_thread::get_id() << endl;
        }
    }
    return 0;
}
