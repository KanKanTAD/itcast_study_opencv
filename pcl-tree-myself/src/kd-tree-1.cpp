#include <assert.h>

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

//#define _debug
#ifdef _debug
#define info \
    { cout << __FILE__ << ":" << __LINE__ << endl; }
#else
#define info
#endif

template <typename ScalarT>
union point_ {
    point_(ScalarT x, ScalarT y, ScalarT z) : x{x}, y{y}, z{z} {
    }
    ScalarT data[4] = {0, 0, 0, 0};
    struct {
        ScalarT x;
        ScalarT y;
        ScalarT z;
    };
};

template <typename ScalarT>
ostream& operator<<(ostream& out, point_<ScalarT>& p) {
    out << "x--" << p.x << ";y--" << p.y << ";z--" << p.z << ";";
    return out;
}

template <typename ScalarT>
struct tree_node {
    point_<ScalarT> data;
    tree_node<ScalarT>*left{nullptr}, *right{nullptr};
    int tag = -1;
};

template <typename ScalarT>
ostream& operator<<(ostream& out, tree_node<ScalarT>& node) {
    out << "data-->" << node.data;
    if (nullptr != node.left) {
        cout << "[left-->" << (*node.left) << ";]" << endl;
    }
    if (nullptr != node.right) {
        cout << "[right-->" << (*node.right) << ";]" << endl;
    }
    return out;
}

template <typename Iter>
inline float mean(Iter _b, Iter _e, size_t _tag = 0, size_t* sz = nullptr) {
    if (_b == _e) {
        return 0.f;
    }
    float res = 0.0f;
    float len = 0.0f;
    for (auto it = _b; it != _e; it = next(it), len += 1.0f) {
        res += it->data.data[_tag];
    }
    if (nullptr != sz) {
        *sz = int(len);
    }
    return res / len;
}

template <typename Iter>
inline float var(Iter _b, Iter _e, size_t _tag = 0, size_t* sz = nullptr) {
    if (_b == _e) {
        return 0.f;
    }
    float _m = mean(_b, _e, _tag, sz);

    float _v   = 0.0f;
    float _len = 0.0f;
    for (auto it = _b; it != _e; it = next(it), _len += 1.0f) {
        _v += pow(_v - it->data.data[_tag], 2.0f);
    }

    return _v / _len;
}

template <typename ScalarT, typename Iter>
tree_node<ScalarT>* create_tree(Iter _b, Iter _e) {
    info if (_b >= _e) {
        info return nullptr;
    }
    float vars[3];
    size_t _len;
    for (int i = 0; i < 3; ++i) {
        vars[i] = var(_b, _e, i, &_len);
    }
    auto _end   = end(vars);
    auto max_it = max_element(begin(vars), _end);
    assert(max_it != _end);
    int _tag = int(max_it - begin(vars));

    sort(_b, _e, [=](tree_node<ScalarT>& a, tree_node<ScalarT>& b) {
        return a.data.data[_tag] < b.data.data[_tag];
    });
    info;
    int _md = _len / 2;
    info;
    tree_node<ScalarT>* res = &(*(_b + _md));
    res->tag                = _tag;
    res->left               = create_tree<ScalarT>(_b, (_b + _md));
    res->right              = create_tree<ScalarT>((_b + _md + 1), _e);
    return res;
}

template <typename ScalarT>
size_t count_tree(tree_node<ScalarT>* root) {
    if (nullptr == root) {
        return 0;
    }
    return 1 + count_tree(root->left) + count_tree(root->right);
}
int main(int argc, char** argv) {
    mt19937_64 rng{(unsigned long)time(0)};
    uniform_real_distribution<float> uni{0, 512};
    size_t PointNum = 1024;

    vector<tree_node<float>> nodes;
    for (size_t i = 0; i < PointNum; ++i) {
        nodes.push_back({{uni(rng), uni(rng), uni(rng)}, nullptr, nullptr, -1});
    }

    auto root = create_tree<float>(nodes.begin(), nodes.end());
    cout << "count_tree-->" << count_tree(root) << ";count_arr-->"
         << nodes.size() << endl;
    return 0;
}
