#pragma once

#include <functional>
#include <vector>
namespace tadus {
namespace functional {

template <typename T>
struct east_west {
    east_west(const east_west<T>&) = default;
    std::vector<T> east;
    std::vector<T> west;
    const east_west<T>& swap() const {
        std::swap(east, west);
        return *this;
    }
};

template <typename T>
using void_bin_function = std::function<void(const east_west<T>&)>;

template <typename T>
east_west<T>& operator|(const east_west<T>& ew, void_bin_function<T> func) {
    func(ew);
    return ew.swap();
}

}  // namespace functional
}  // namespace tadus
