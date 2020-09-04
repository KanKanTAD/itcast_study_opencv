
#include <cstdint>
#include <iostream>

#include "URDriver.hpp"
#include "utils.hpp"

using namespace std;

union t_data {
    std::uint8_t data[4 + 8 * (5 + 9)];
    struct {
        int msg_size;
        union {
            double _double_data[5 + 9];
            struct {
                double a1[2];
                double a2[2];
                double b1;
                double c1[6];
                double d1[3];
            };
        };
    };
};

int main(int argc, char** argv) {
    // double target1[6] = {-0.2384, -0.3735, 0.029, -0.0015, 0, 0.0};
    // double target2[6] = {-0.2384, -0.3735, 0.027, 2 * 3.1415, -0.0, -0.0};

    // auto va = utils::variance(target1, target2);
    // auto sv = utils::std_var(target1, target2);
    // auto el = utils::eular_distance(target1, target2);
    // auto me = utils::movel_error(target1, target2);
    // cout << "va:" << va << " ,sv:" << sv << " ,el:" << el << " ,me:" << me
    //<< endl;

    t_data data;

    cout << sizeof(t_data) << endl;
    cout << sizeof(data) << endl;

    cout << sizeof(data.data) << endl;
    cout << sizeof(data._double_data) << endl;

    return 0;
}
