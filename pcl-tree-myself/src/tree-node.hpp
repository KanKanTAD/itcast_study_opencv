#pragma once

#include <assert.h>

#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;
#ifdef _debug
#define info \
    { cout << __FILE__ << ":" << __LINE__ << endl; }
#else
#define info
#endif

template <typename ScalarT>
union point3_ {
    point3_(ScalarT x, ScalarT y, ScalarT z) : x{x}, y{y}, z{z} {
    }
    ScalarT data[4] = {0, 0, 0, 0};
    struct {
        ScalarT x;
        ScalarT y;
        ScalarT z;
    };
};

template <typename ScalarT>
ostream& operator<<(ostream& out, point3_<ScalarT>& p) {
    out << "x--" << p.x << ";y--" << p.y << ";z--" << p.z << ";";
    return out;
}

template <typename ScalarT>
struct bin_tree_node {
    point3_<ScalarT> data;
    bin_tree_node<ScalarT>*left{nullptr}, *right{nullptr};
    int tag = -1;
};

template <typename ScalarT>
ostream& operator<<(ostream& out, bin_tree_node<ScalarT>& node) {
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
bin_tree_node<ScalarT>* create_kd_tree(Iter _b, Iter _e) {
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

    sort(_b, _e, [=](bin_tree_node<ScalarT>& a, bin_tree_node<ScalarT>& b) {
        return a.data.data[_tag] < b.data.data[_tag];
    });
    info;
    int _md = _len / 2;
    info;
    bin_tree_node<ScalarT>* res = &(*(_b + _md));
    res->tag                    = _tag;
    res->left                   = create_kd_tree<ScalarT>(_b, (_b + _md));
    res->right                  = create_kd_tree<ScalarT>((_b + _md + 1), _e);
    return res;
}

template <typename ScalarT>
size_t count_bin_tree(bin_tree_node<ScalarT>* root) {
    if (nullptr == root) {
        return 0;
    }
    return 1 + count_bin_tree(root->left) + count_bin_tree(root->right);
}
template <typename ScalarT>
struct octree_node {
    octree_node(ScalarT x, ScalarT y, ScalarT z) : data{x, y, z} {
    }
    explicit octree_node(point3_<ScalarT>& data) : data{data} {
    }
    point3_<ScalarT> data{0, 0, 0};
    octree_node<ScalarT>* children[2][2][2] = {
        {{nullptr, nullptr}, {nullptr, nullptr}},
        {{nullptr, nullptr}, {nullptr, nullptr}}};

    void insert(octree_node<ScalarT>& node) {
        auto bool2idx = [](bool b) -> size_t { return b ? 1 : 0; };
        auto d1       = bool2idx(node.data.x > data.x);
        auto d2       = bool2idx(node.data.y > data.y);
        auto d3       = bool2idx(node.data.z > data.z);
        auto& nx      = children[d1][d2][d3];
        if (nullptr == nx) {
            nx = &node;
        } else {
            nx->insert(node);
        }
    }

    static size_t count(octree_node<ScalarT>* root) {
        if (nullptr == root) {
            return 0;
        }
        return 1 + count(root->children[0][0][0]) +
               count(root->children[0][0][1]) + count(root->children[0][1][0]) +
               count(root->children[0][1][1]) + count(root->children[1][0][0]) +
               count(root->children[1][0][1]) + count(root->children[1][1][0]) +
               count(root->children[1][1][1]);
    }
};
#undef _debug
