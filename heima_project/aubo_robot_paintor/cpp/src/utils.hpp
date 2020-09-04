#pragma once

#include <QString>
#include <algorithm>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exception>
#include <iterator>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace utils {

template <size_t n>
std::shared_ptr<std::vector<double>> arr2vec(double (&arr)[n]) {
    return std::shared_ptr<std::vector<double>>{
        new std::vector<double>{std::begin(arr), std::end(arr)}};
}

double stod(const std::string& s, double default_ = 0) {
    auto res = default_;
    try {
        res = std::stod(s);
    } catch (std::exception& e) {
        res = default_;
    }
    return res;
}

int stoi(const QString& s, int default_ = 0) {
    auto res = default_;
    try {
        res = std::stoi(s.toStdString());
    } catch (std::exception& e) {
        res = default_;
    }
    return res;
}

QString load_qstring(const QString& s, const QString& default_ = {""}) {
    return s == "" ? default_ : s;
}

template <typename T, size_t n>
void vector2array(std::vector<T> vec, T (&arr)[n]) {
    size_t sz = std::min(vec.size(), n);
    for (int i = 0; i < sz; ++i) {
        arr[i] = vec.at(i);
    }
}

inline void reverse_byte(std::uint8_t* begin, size_t sz) {
    // std::reverse(begin, begin + sz);
    for (int i = 0; i < sz / 2; ++i) {
        std::uint8_t t    = begin[i];
        begin[i]          = begin[sz - i - 1];
        begin[sz - i - 1] = t;
    }
}

template <typename T>
inline T reverse_value(T value) {
    const size_t sz = {sizeof(value)};
    std::uint8_t buff[sz];
    memcpy(buff, &value, sz);
    reverse_byte(buff, sz);
    memcpy(&value, buff, sz);
    return value;
}

template <typename T>
QString joint(const QString& delim, std::vector<T>& vec) {
    if (vec.empty()) {
        return "";
    }
    std::stringstream ss;
    ss << vec.front();
    auto d = delim.toStdString();
    for (int i = 1; i < vec.size(); ++i) {
        ss << d << vec.at(i);
    }
    return QString::fromStdString(ss.str());
}

std::shared_ptr<std::vector<std::string>> split(const std::string& s,
                                                const std::string& pat = ",") {
    std::regex reg{pat};
    auto* vk = new std::vector<std::string>{
        std::sregex_token_iterator{s.begin(), s.end(), reg, -1},
        std::sregex_token_iterator{}};
    return std::shared_ptr<std::vector<std::string>>{vk};
}

std::shared_ptr<std::vector<double>> strs2doubles(
    std::vector<std::string>& strs) {
    std::shared_ptr<std::vector<double>> res{new std::vector<double>{}};
    for (std::string& s : strs) {
        res->push_back(utils::stod(s));
    }
    return res;
}

inline float ang_distance0(float d1, float d2) {
    return std::sqrt(std::pow(std::cos(d1) - std::cos(d2), 2) +
                     std::pow(std::sin(d1) - std::sin(d2), 2));
}

inline float ang_distance(float d1, float d2) {
    std::complex<float> c1{0, d1};
    c1 = 1.0f * std::exp(c1);
    std::complex<float> c2{0, d2};
    c2 = 1.0f * std::exp(c2);
    return std::abs(std::log(c1 / c2));
}

inline float movel_error(double (&a)[6], double* b) {
    float x = 0.0f;
    for (int i = 0; i < 3; i++) {
        x += std::pow(a[i] - b[i], 2);
    }
    x       = std::sqrt(x);
    float y = 0.0f;
    for (int i = 3; i < 6; i++) {
        y += ang_distance0(a[i], b[i]);
    }
    y /= 3.0f;
    return (x + y) / 2.0f;
}

template <typename T, size_t n>
inline T variance(T (&a)[n], T* b) {
    T res = (T)(0);

    for (int i = 0; i < n; ++i) {
        res += std::pow(double(a[i] - b[i]), 2);
    }
    res /= double(n);
    return res;
}

template <typename T, size_t n>
inline T std_var(T (&a)[n], T* b) {
    return std::sqrt((double)(variance(a, b)));
}

template <typename T, size_t n>
inline T eular_distance(T (&a)[n], T* b) {
    T res = (T)(0);

    for (int i = 0; i < n; ++i) {
        res += std::pow(double(a[i] - b[i]), 2);
    }
    res = (T)std::sqrt((double)res);
    return res;
}

}  // namespace utils
