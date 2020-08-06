#include <assert.h>

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

#include "tree-node.hpp"

using namespace std;

int main(int argc, char** argv) {
    mt19937_64 rng{(unsigned long)time(0)};
    uniform_real_distribution<float> uni{0, 512};
    size_t PointNum = 1024;

    vector<bin_tree_node<float>> nodes;
    for (size_t i = 0; i < PointNum; ++i) {
        nodes.push_back({{uni(rng), uni(rng), uni(rng)}, nullptr, nullptr, -1});
    }

    auto root = create_kd_tree<float>(nodes.begin(), nodes.end());
    cout << "count_tree-->" << count_bin_tree(root) << ";count_arr-->"
         << nodes.size() << endl;
    return 0;
}
