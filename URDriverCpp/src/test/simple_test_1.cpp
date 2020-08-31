#include <cstdint>
#include <iostream>

#include "URDriver.h"

int main(int argc, char** argv) {
    std::uint32_t tv = 0x00000001;
    std::cout << std::hex << tv << std::endl;
    std::cout << std::hex << tool::byte_reverse(tv) << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::uint64_t lv = 0x00000000ffffffff;
    std::cout << std::hex << lv << std::endl;
    std::cout << std::hex << tool::byte_reverse(lv) << std::endl;
    return 0;
}
