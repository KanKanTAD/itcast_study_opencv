#include <ctime>
#include <random>
#include <vector>

#include "tree-node.hpp"

int main(int argc, char** argv) {
    std::cout << "hello world\n";

    mt19937 mt{(unsigned)(time(0))};
    uniform_real_distribution<float> rnd{0, 1024};

    size_t NODE_COUNT = 1024;
    vector<octree_node<float>> nodes;
    while (NODE_COUNT--) {
        nodes.push_back({rnd(mt), rnd(mt), rnd(mt)});
    }
    random_shuffle(nodes.begin(), nodes.end());
    auto& root = nodes.front();
    auto it    = nodes.begin();
    while (++it != nodes.end()) {
        root.insert(*it);
    }

    cout << "count tree-->" << root.count(&root) << " ;nodes.size()-->"
         << nodes.size() << endl;

    return 0;
}
