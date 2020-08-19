#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// void test_mulrange_for() {
// std::vector<int> f;
// f.resize(3, 0);
// iota(f.begin(), f.end(), 0);
// std::vector<int> g;
// g.resize(4, 0);
// iota(g.begin(), g.end(), 0);

// for (auto i : f; auto j : g) {
// cout << i << ";" << j << endl;
//}
//}

void test_range_for() {
    std::vector<int> indeies;
    indeies.resize(100, 0);
    iota(indeies.begin(), indeies.end(), 0);
    for (size_t i = 0; auto idx : indeies) {
        cout << "indeies[" << i++ << "]=" << idx << endl;
    }
}

int main(int argc, char** argv) {
    test_range_for();

    return 0;
}
