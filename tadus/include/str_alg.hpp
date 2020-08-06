#pragma once

#include <regex>
#include <string>
#include <vector>

using namespace std;

namespace tadus {
namespace str_alg {
/********************
 *
 * split
 */
struct split {
    const string& patten;
    explicit split(const string& patten) : patten{patten} {
    }
    split(const split& other) = default;
};

struct split_function {
    const string& s;
    const split& sp;
    split_function(const string& s, const split& sp) : s{s}, sp{sp} {
    }

    bool operator()(vector<string>& res) const {
        res.clear();
        std::regex re{this->sp.patten};
        for (auto it = sregex_token_iterator{s.begin(), s.end(), re, -1};
             it != sregex_token_iterator{};
             ++it) {
            res.emplace_back(*it);
        }

        return !res.empty();
    }
};
split_function operator|(const string& _s, const split& _sp) {
    return split_function{_s, _sp};
}

bool operator|(const split_function& _sp_func, vector<string>& res) {
    return _sp_func(res);
}

/*******************
 * joint
 */
struct joint {
    const string& s;
    explicit joint(const string& s) : s{s} {
    }
};

struct joint_function {
    const vector<string>& arr;
    const joint& jo;
    joint_function(const vector<string>& arr, const joint& _jo)
        : arr{arr}, jo{_jo} {
    }

    bool operator()(string& res) const {
        return true;
    }
};

joint_function operator|(const vector<string>& arr, const joint& _jo) {
    return joint_function{arr, _jo};
}

bool operator|(const joint_function& _jo_func, string& res) {
    return _jo_func(res);
}

}  // namespace str_alg
}  // namespace tadus
