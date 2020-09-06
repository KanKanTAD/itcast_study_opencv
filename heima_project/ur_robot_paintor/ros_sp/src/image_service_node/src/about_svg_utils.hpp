#pragma once

#include <assert.h>

#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#define print_line                                                  \
    {                                                               \
        std::cout << __FILE__ << "  ---  " << __func__ << "  ---  " \
                  << __LINE__ << std::endl;                         \
    }

namespace utils {

inline int round(float v) {
    return int(std::round(v));
}

inline cv::Point2f __add__(const cv::Point2f& a, const std::vector<float>& b) {
    return cv::Point2f{a.x + b.at(0), a.y + b.at(1)};
}

inline cv::Point2i pntf2pnti(const cv::Point2f& pnt) {
    return cv::Point2i{round(pnt.x), round(pnt.y)};
}

inline void setpntf(cv::Point2f& pntf, std::vector<float>& pt) {
    assert(pt.size() >= 2);
    pntf.x = pt.at(0);
    pntf.y = pt.at(1);
}

std::shared_ptr<std::vector<float>> arange(float b, float e, float t) {
    assert(b < e && t > 0);
    std::shared_ptr<std::vector<float>> res{new std::vector<float>{}};
    for (; b < e; b += t) {
        res->push_back(b);
    }
    return res;
}
std::shared_ptr<std::vector<float>> linspace(float b, float e, int cnt = 2) {
    float c = std::max(2, cnt);
    assert(b < e && c >= 2.0f);
    std::shared_ptr<std::vector<float>> res{new std::vector<float>{}};
    float it = b;
    float sp = e - b;
    res->push_back(it);
    while (c > 2) {
        float delta = sp / (c - 1.0f);
        it += delta;
        sp -= delta;
        c -= 1.0f;
        res->push_back(it);
    }
    res->push_back(e);
    return res;
}

inline float eular_distance(const cv::Point2f& a, const cv::Point2f& b) {
    cv::Point2f c = a - b;
    return std::sqrt(c.x * c.x + c.y * c.y);
}

inline cv::Point2f _get_quadratic_bezier_pnt(const cv::Point2f& b,
                                             const cv::Point2f& c1,
                                             const cv::Point2f& c2,
                                             const cv::Point2f& e,
                                             float t) {
    return std::pow((1.0f - t), 3) * b + 3 * std::pow((1.0f - t), 2) * t * c1 +
           3 * std::pow(t, 2) * (1.0f - t) * c2 + std::pow(t, 3) * e;
}
std::shared_ptr<std::vector<cv::Point2i>> quadratic_bezier(
    const cv::Point2f& b,
    const cv::Point2f& c1,
    const cv::Point2f& c2,
    const cv::Point2f& e,
    int cnt = -1) {
    std::shared_ptr<std::vector<cv::Point2i>> res{
        new std::vector<cv::Point2i>{}};

    cnt = cnt <= 0 ? int(eular_distance(b, c1) + eular_distance(c1, c2) +
                         eular_distance(c2, e))
                   : cnt;
    auto ts = linspace(0, 1, cnt);
    for (auto& t : *ts) {
        res->push_back(pntf2pnti(_get_quadratic_bezier_pnt(b, c1, c2, e, t)));
    }

    return res;
}

void _get_paths_from_g(boost::property_tree::ptree& pt,
                       std::vector<boost::property_tree::ptree>& paths) {
    for (auto& el : pt) {
        if (el.first == "g") {
            _get_paths_from_g(el.second, paths);
        } else if (el.first == "path") {
            paths.push_back(el.second);
        }
    }
}

std::pair<int, int> get_size_from_svg(boost::property_tree::ptree& svg) {
    auto res = std::make_pair(0, 0);
    try {
        res.first  = svg.get<int>("<xmlattr>.width");
        res.second = svg.get<int>("<xmlattr>.height");

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return res;
}

std::pair<int, int> get_size_from_doc(boost::property_tree::ptree& doc) {
    auto svg = doc.get_child("svg");
    return get_size_from_svg(svg);
}

std::shared_ptr<std::vector<boost::property_tree::ptree>> get_paths_from_svg(
    boost::property_tree::ptree& doc) {
    std::shared_ptr<std::vector<boost::property_tree::ptree>> res{
        new std::vector<boost::property_tree::ptree>{}};
    auto root = doc.get_child("svg");
    auto g    = root.get_child("g");
    _get_paths_from_g(g, *res);
    return res;
}

std::shared_ptr<std::vector<boost::property_tree::ptree>> get_paths_from_svg(
    const std::string& svg_filepath) {
    boost::property_tree::ptree pt;
    boost::property_tree::read_xml(svg_filepath, pt);
    return get_paths_from_svg(pt);
}

std::shared_ptr<std::vector<std::string>> get_pathd_from_doc(
    boost::property_tree::ptree& doc) {
    auto paths = get_paths_from_svg(doc);
    std::shared_ptr<std::vector<std::string>> res{
        new std::vector<std::string>{}};

    for (auto& path : *paths) {
        res->push_back(path.get<std::string>("<xmlattr>.d"));
    }
    return res;
}

inline std::shared_ptr<std::vector<std::string>> split(
    const std::string& s,
    const std::string& p = "[\\s]+") {
    std::regex reg{p};
    std::shared_ptr<std::vector<std::string>> res{new std::vector<std::string>{
        std::sregex_token_iterator{s.begin(), s.end(), reg, -1},
        std::sregex_token_iterator{}}};
    return res;
}

inline std::shared_ptr<std::vector<float>> split_to_floats(
    const std::string& s,
    const std::string& p = ",") {
    print_line;
    std::cout << "split s:" << s << " ;; by:" << p << std::endl;
    std::regex reg{p};
    std::shared_ptr<std::vector<float>> res{new std::vector<float>{}};
    std::vector<std::string> strs{
        std::sregex_token_iterator{s.begin(), s.end(), reg, -1},
        std::sregex_token_iterator{}};
    std::transform(
        strs.begin(), strs.end(), std::back_inserter(*res), [](std::string& s) {
            float res = 0;
            try {
                res = std::stof(s);
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
            return res;
        });
    return res;
}

static std::map<std::string,
                std::function<bool(cv::Point2f&,
                                   std::vector<std::vector<cv::Point2i>>&,
                                   const std::vector<std::string>&,
                                   int&)>>
    __handle_mapper__{
        {"m",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             ways.push_back(std::vector<cv::Point2i>{});
             ++i;
             if (i >= pathd.size()) {
                 return false;
             }
             auto pts = split_to_floats(pathd.at(i));
             prev_pt.x += pts->at(0);
             prev_pt.y += pts->at(1);
             ways.back().push_back(prev_pt);
             ++i;
             return true;
         }},
        {"M",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             ways.push_back(std::vector<cv::Point2i>{});
             ++i;

             if (i >= pathd.size()) {
                 return false;
             }
             auto pts = split_to_floats(pathd.at(i));
             setpntf(prev_pt, *pts);
             ways.back().push_back(prev_pt);
             ++i;
             return true;
         }},
        {"l",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             ++i;
             if (i >= pathd.size()) {
                 return false;
             }
             auto pts = split_to_floats(pathd.at(i));
             prev_pt.x += pts->at(0);
             prev_pt.y += pts->at(1);
             ways.back().push_back(prev_pt);
             ++i;
             return true;
         }},
        {"L",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             ++i;
             if (i >= pathd.size()) {
                 return false;
             }
             auto pts = split_to_floats(pathd.at(i));
             setpntf(prev_pt, *pts);
             ways.back().push_back(prev_pt);
             ++i;
             return true;
         }},
        {"h",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             ++i;
             if (i >= pathd.size()) {
                 return false;
             }
             auto pts = split_to_floats(pathd.at(i));
             prev_pt.x += pts->at(0);
             ways.back().push_back(prev_pt);
             ++i;
             return true;
         }},
        {"H",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             ++i;
             if (i >= pathd.size()) {
                 return false;
             }
             auto pts  = split_to_floats(pathd.at(i));
             prev_pt.x = pts->at(0);
             ways.back().push_back(prev_pt);
             ++i;
             return true;
         }},
        {"v",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             ++i;
             if (i >= pathd.size()) {
                 return false;
             }
             auto pts = split_to_floats(pathd.at(i));
             prev_pt.y += pts->at(0);
             ways.back().push_back(prev_pt);
             ++i;
             return true;
         }},
        {"V",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             ++i;
             if (i >= pathd.size()) {
                 return false;
             }
             auto pts  = split_to_floats(pathd.at(i));
             prev_pt.y = pts->at(0);
             ways.back().push_back(prev_pt);
             ++i;
             return true;
         }},
        {"c",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             cv::Point2f b = prev_pt;

             if (++i >= pathd.size()) {
                 return false;
             }
             cv::Point2f c1 = __add__(prev_pt, *split_to_floats(pathd.at(i)));

             if (++i >= pathd.size()) {
                 return false;
             }
             cv::Point2f c2 = __add__(prev_pt, *split_to_floats(pathd.at(i)));

             if (++i >= pathd.size()) {
                 return false;
             }
             cv::Point2f e = __add__(prev_pt, *split_to_floats(pathd.at(i)));

             auto pts = quadratic_bezier(b, c1, c2, e);
             prev_pt  = pts->back();
             std::copy(
                 pts->begin(), pts->end(), std::back_inserter(ways.back()));

             ++i;
             return true;
         }},
        {"C",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             cv::Point2f b = prev_pt;

             if (++i >= pathd.size()) {
                 return false;
             }
             cv::Point2f c1;
             setpntf(c1, *split_to_floats(pathd.at(i)));

             if (++i >= pathd.size()) {
                 return false;
             }
             cv::Point2f c2;
             setpntf(c2, *split_to_floats(pathd.at(i)));

             if (++i >= pathd.size()) {
                 return false;
             }
             cv::Point2f e;
             setpntf(e, *split_to_floats(pathd.at(i)));

             auto pts = quadratic_bezier(b, c1, c2, e);
             prev_pt  = pts->back();
             std::copy(
                 pts->begin(), pts->end(), std::back_inserter(ways.back()));

             ++i;
             return true;
         }},
        {"z",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             ways.back().push_back(ways.back().front());
             prev_pt = ways.back().back();
             ++i;
             return true;
         }},
        {"Z",
         [](cv::Point2f& prev_pt,
            std::vector<std::vector<cv::Point2i>>& ways,
            const std::vector<std::string>& pathd,
            int& i) -> bool {
             ways.back().push_back(ways.back().front());
             prev_pt = ways.back().back();
             ++i;
             return true;
         }}};

void get_way_from_pathd(std::vector<std::string>& pathd,
                        std::vector<std::vector<cv::Point2i>>& ways) {
    print_line;

    auto prev_func_it = __handle_mapper__.begin();
    int i             = 0;
    cv::Point2f prev_pt{0, 0};
    while (i < pathd.size()) {
        auto key = pathd.at(i);
        auto fit = __handle_mapper__.find(key);
        if (fit == __handle_mapper__.end()) {
            --i;
            fit = prev_func_it;
        }
        std::cout << "handle in " << fit->first << std::endl;
        if (false == fit->second(prev_pt, ways, pathd, i)) {
            return;
        }
        std::cout << "this i is " << i << std::endl;
        prev_func_it = fit;
    }
}

std::shared_ptr<std::vector<std::vector<cv::Point2i>>> get_ways_form_paths(
    std::vector<boost::property_tree::ptree>& paths) {
    //
    print_line;
    std::shared_ptr<std::vector<std::vector<cv::Point2i>>> res{
        new std::vector<std::vector<cv::Point2i>>{}};
    for (auto& pt : paths) {
        auto d     = pt.get<std::string>("<xmlattr>.d");
        auto pathd = split(d);
        for (auto& s : *pathd) {
            std::cout << s << " ; ";
        }
        std::cout << "%%" << std::endl;
        get_way_from_pathd(*pathd, *res);
    }
    return res;
}

std::shared_ptr<std::vector<std::vector<cv::Point2i>>> get_ways_form_svg(
    boost::property_tree::ptree& doc) {
    auto paths = get_paths_from_svg(doc);
    return get_ways_form_paths(*paths);
}

std::shared_ptr<std::vector<std::vector<cv::Point2i>>> get_ways_form_svg(
    const std::string& svg_filepath) {
    boost::property_tree::ptree pt;
    boost::property_tree::read_xml(svg_filepath, pt);
    return get_ways_form_svg(pt);
}

}  // namespace utils
