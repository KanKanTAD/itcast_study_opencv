#include <algorithm>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <regex>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <typename T>
using mtx_t = std::vector<std::vector<T>>;

template <typename T>
using mtx_ptr = std::shared_ptr<mtx_t<T>>;

template <typename T>
using vec_ptr = std::shared_ptr<vector<T>>;

void trip(string& s) {
    int i = 2;
    while (i--) {
        while (s.empty() == false) {
            if (s.back() == ' ') {
                s.pop_back();
            } else {
                break;
            }
        }
        s.reserve();
    }
}
std::shared_ptr<vector<string>> split(const string& s, const string& p) {
    std::regex r{p};
    shared_ptr<vector<string>> res{
        new vector<string>{sregex_token_iterator(s.begin(), s.end(), r, -1),
                           sregex_token_iterator()}};
    return res;
}

template <typename T>
mtx_ptr<T> getMtxFromFile(const string& filepath, const string& delim) {
    cout << __FUNCTION__ << ":" << __LINE__ << endl;
    std::ifstream ifs{filepath};
    if (ifs.is_open() == false) {
        throw std::runtime_error{"can't open file"};
    }
    std::unique_ptr<ifstream, std::function<void(ifstream*)>> _0x1{
        &ifs, [](ifstream* a) { a->close(); }};

    mtx_ptr<float> res{new mtx_t<float>{}};
    while (!ifs.eof()) {
        std::string line;
        std::getline(ifs, line);
        trip(line);
        if (line.empty()) {
            continue;
        }
        // cout << "getline--->" << line << endl;
        auto vs = split(line, delim);
        vector<float> fs;
        std::transform(vs->begin(),
                       vs->end(),
                       back_inserter(fs),
                       [](const string& s) -> float { return stof(s); });
        res->push_back(fs);
    }
    return res;
}

template <typename T>
void showit(const mtx_t<T>& m) {
    for (auto& row : m) {
        for (auto& col : row) {
            cout << setw(12) << right << fixed << col << " ";
        }
        cout << endl;
    }
}

template <typename T, typename Iter>
vec_ptr<T> eular_distance(Iter _b, Iter _e, mtx_t<T>& mtx) {
    vec_ptr<T> res{new vector<T>{}};
    for (auto& ovec : mtx) {
        res->push_back(inner_product(_b, _e, ovec.begin(), (T)0));
    }

    return res;
}
template <typename T>
vec_ptr<T> eular_distance(vector<T>& vec, mtx_t<T>& mtx) {
    return eular_distance(vec.begin(), vec.end(), mtx);
}

template <typename T>
struct knn_classify {
    int k = 1;
    mtx_ptr<T> trans_data_label;

    template <typename Iter>
    int classit(Iter vc_beg, Iter vc_end) {
        auto vs = eular_distance<float>(vc_beg, vc_end, *trans_data_label);
        vector<int> idies;
        idies.resize(trans_data_label->size(), 0);
        std::iota(idies.begin(), idies.end(), 0);
        sort(idies.begin(), idies.end(), [&](int& a, int& b) {
            return vs->at(a) < vs->at(b);
        });
        vector<int> label;
        transform(idies.begin(),
                  idies.begin() + k,
                  back_inserter(label),
                  [&](int& idx) -> int {
                      return int(trans_data_label->at(idx).back());
                  });

        multiset<int> t{label.begin(), label.end()};
        set<int> st{t.begin(), t.end()};
        return *max_element(
            st.begin(), st.end(), [&](const int& a, const int& b) {
                return t.count(a) < t.count(b);
            });
    }
};

int main(int argc, char** argv) {
    std::string filepath = "/home/tad/www/yuehui_test.csv";
    if (argc >= 2) {
        filepath = argv[1];
    }
    cout << "filepath is:" << filepath << endl;

    auto data = getMtxFromFile<float>(filepath, "[,\\s]+");

    knn_classify<float> knn{12, data};
    auto test = data->at(3);
    auto c    = knn.classit(test.begin(), test.end());
    cout << c << endl;

    return 0;
}
