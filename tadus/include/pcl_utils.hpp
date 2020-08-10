#pragma once
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/point_cloud_color_handlers.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <iterator>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#define _debug_ 1
#ifdef _debug_
#define info \
    { cout << __FILE__ << __LINE__ << endl; }
#else
#define info \
    {}
#endif

namespace utils {

typedef size_t axis_t;

template <typename PointT>
typename pcl::PointCloud<PointT>::Ptr makePntCld() {
    typename pcl::PointCloud<PointT>::Ptr res{new pcl::PointCloud<PointT>{}};
    return res;
}

template <typename PointT>
typename pcl::PointCloud<PointT>::Ptr makePntCld_like(
    const pcl::PointCloud<PointT>& other) {
    return makePntCld<PointT>();
}
template <typename PointT>
typename pcl::PointCloud<PointT>::Ptr makePntCld_randCube(
    const size_t pnt_count,
    const float (&range)[2],
    const axis_t axis_cout = 3) {
    auto res  = makePntCld<PointT>();
    auto& pts = res->points;
    std::mt19937 mt((unsigned int)std::time(0));
    std::uniform_real_distribution<float> uni{range[0], range[1]};
    for (int i = 0; i < pnt_count; ++i) {
        PointT p;
        for (int j = 0; j < axis_cout; ++j) {
            p.data[j] = uni(mt);
        }
        pts.emplace_back(p);
    }
    return res;
}

template <typename PointT>
typename pcl::PointCloud<PointT>::Ptr clone_from(
    pcl::PointCloud<PointT>& other) {
    auto res = makePntCld<PointT>();
    pcl::copyPointCloud(other, *res);
    return res;
}

template <typename PointT>
typename pcl::PointCloud<PointT>::Ptr ptcldFromFile(
    const std::string& file_path) {
    typename pcl::PointCloud<PointT>::Ptr ptr{new pcl::PointCloud<PointT>{}};
    pcl::io::loadPCDFile(file_path, *ptr);
    return ptr;
}

template <typename PointT, size_t N = 3>
typename pcl::visualization::PointCloudColorHandlerCustom<PointT>::Ptr
single_color(pcl::PointCloud<PointT>& cld, const double (&color)[N]) {
    typename pcl::PointCloud<PointT>::ConstPtr ptr{&cld};
    typename pcl::visualization::PointCloudColorHandlerCustom<PointT>::Ptr res{
        new pcl::visualization::PointCloudColorHandlerCustom<PointT>{
            ptr, color[0], color[1], color[2]}};
    return res;
}

template <typename PointT>
typename pcl::visualization::PointCloudColorHandlerCustom<PointT>::Ptr
single_color(pcl::PointCloud<PointT>& cld) {
    std::mt19937 m((unsigned int)std::time(0));
    std::uniform_real_distribution<double> rng{0.0, 255.0};
    single_color<PointT>(cld, {rng(m), rng(m), rng(m)});
}

template <typename PointT>
typename pcl::PointCloud<PointT>::Ptr loadPCDFile(
    const std::string& file_path) {
    auto res = makePntCld<PointT>();
    pcl::io::loadPCDFile(file_path, *res);
    return res;
}

template <typename PointT>
std::pair<float, float> axis_minmax(pcl::PointCloud<PointT>& ptcd,
                                    size_t axis) {
    auto& pts = ptcd.points;
    auto&& mm = std::minmax_element(
        pts.begin(), pts.end(), [axis](PointT& a, PointT& b) -> bool {
            return a.data[axis] < b.data[axis];
        });

    return {mm.first->data[axis], mm.second->data[axis]};
}

template <typename PointT>
float axis_mean(pcl::PointCloud<PointT>& ptcd, axis_t axis) {
    auto& pts  = ptcd.points;
    float _len = pts.size();
    if (0.f == _len) {
        return 0.0f;
    }

    float res = 0.0f;
    for (auto& p : pts) {
        res += (p.data[axis] / _len);
    }
    return res;
}

template <typename T, size_t N>
inline void __file(T (&arr)[N], const T& value) {
    std::fill(std::begin(arr), std::end(arr), value);
}

template <typename T, size_t N>
inline std::pair<T*, size_t> array_like(T (&arr)[N], const T& value) {
    T* res = new T[N];
    for (int i = 0; i < N; ++i) {
        res[i] = value;
    }
    return {res, N};
}

template <size_t N>
inline float* __numer_dot_addto(float numer,
                                float (&input)[N],
                                float* output = nullptr) {
    if (nullptr == output) {
        output = new float[N];
        std::memset(output, 0, sizeof(float) * N);
    }
    for (int i = 0; i < N; ++i) {
        output[i] += (input[i] * numer);
    }
    return output;
}

template <typename PointT>
PointT pos_mean(pcl::PointCloud<PointT>& ptcd) {
    auto& pts  = ptcd.points;
    float _len = pts.size();
    PointT res;
    auto& data = res.data;
    __file(data, 0.0f);
    if (0 == _len) {
        return res;
    }
    for (auto& p : pts) {
        __numer_dot_addto(1.0f / _len, p.data, data);
    }
    return res;
}

template <typename T, size_t N>
inline float euler_distance(const T (&a)[N], const T (&b)[N]) {
    float res = 0.0f;
    for (int i = 0; i < N; ++i) {
        res += std::pow(float(a[i]) + float(b[i]), 2);
    }
    return std::sqrt(res);
}

template <typename PointT>
inline float euler_distance(const PointT& a, const PointT& b) {
    return euler_distance(a.data, b.data);
}

template <typename Iter, typename Compare>
void __some_min_or_max_tail(Iter _b,
                            Iter _e,
                            size_t count,
                            const bool is_min,
                            Compare comp) {
    for (auto it = _b; next(it) != _e && count--; ++it) {
        auto pre = it;
        for (auto jt = next(it); jt != _e; ++jt) {
            if (is_min == comp(*it, *jt)) {
                std::swap(*it, *jt);
            }
        }
    }
}
template <typename Iter, typename Compare>
void some_max_tail(Iter _b, Iter _e, size_t count, Compare comp) {
    __some_min_or_max_tail(_b, _e, count, false, comp);
}
template <typename Iter, typename Compare>
void some_min_tail(Iter _b, Iter _e, size_t count, Compare comp) {
    __some_min_or_max_tail(_b, _e, count, true, comp);
}

template <typename PointT, typename Iter>
std::shared_ptr<std::vector<std::vector<PointT>>> ___nn(Iter _b,
                                                        Iter _e,
                                                        size_t count) {
    std::vector<PointT> pts{_b, _e};
    std::shared_ptr<std::vector<std::vector<PointT>>> res{
        new std::vector<std::vector<PointT>>{}};

    while (pts.empty() == false) {
        some_min_tail(pts.begin(),
                      pts.end(),
                      count,
                      [&](const PointT& a, const PointT& b) -> bool {
                          return utils::euler_distance(pts.back(), a) <
                                 utils::euler_distance(pts.back(), b);
                      });
        size_t cnt = count;
        res->push_back({});
        while (pts.empty() == false && cnt--) {
            res->back().push_back(pts.back());
            pts.pop_back();
        }
    }

    return res;
}

template <typename PointT>
std::shared_ptr<std::vector<typename pcl::PointCloud<PointT>::Ptr>> ___nn(
    pcl::PointCloud<PointT>& cld,
    size_t count) {
    info;
    auto ptr = ___nn<PointT>(cld.points.begin(), cld.points.end(), count);
    info;
    std::shared_ptr<std::vector<typename pcl::PointCloud<PointT>::Ptr>> res{
        new std::vector<typename pcl::PointCloud<PointT>::Ptr>{}};
    for (auto& pts : *ptr) {
        info;
        res->push_back(makePntCld_like(cld));
        auto& _ps = res->back()->points;
        std::copy(pts.begin(), pts.end(), std::back_inserter(_ps));
    }
    info;
    return res;
}

template <typename PointT>
std::shared_ptr<std::vector<std::vector<PointT>>> ___nn(
    const std::vector<PointT>& _pts,
    size_t count) {
    return ___nn<PointT>(_pts.begin(), _pts.end(), count);
}

template <typename PointT>
typename pcl::PointCloud<PointT>::Ptr pass_filte(pcl::PointCloud<PointT>& cld,
                                                 size_t tag,
                                                 const float (&range)[2],
                                                 bool inRange = true,
                                                 bool located = false) {
    auto in_range = [](float v, float mi, float mx) -> bool {
        return mi <= v && v <= mx;
    };
    auto res      = makePntCld<PointT>();
    res->width    = cld.width;
    res->height   = cld.height;
    res->is_dense = cld.is_dense;
    for (auto& p : cld.points) {
        if (in_range(p.data[tag], range[0], range[1]) != inRange) {
            continue;
        }

        res->points.push_back(p);
    }
    if (located) {
        cld.points.swap(res->points);
        res.reset(&cld);
    }
    return res;
}

}  // namespace utils
