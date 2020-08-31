#pragma once

#include <QString>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exception>
#include <sstream>
#include <string>
#include <vector>

namespace utils {

int stoi(const QString& s, int default_ = 0) {
    int res = default_;
    try {
        res = std::stoi(s.toStdString());
    } catch (std::exception& e) {
    }
    return res;
}

QString load_qstring(const QString& s, const QString& default_ = {""}) {
    return s == "" ? default_ : s;
}

template <typename T>
T reverse_value(T value) {
    const size_t sz = {sizeof(value)};
    std::uint8_t buff[sz];
    memcpy(buff, &value, sz);
    std::reverse(std::begin(buff), std::end(buff));
    return *((T*)buff);
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

}  // namespace utils
