#include <gtest/gtest.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "tadus.hpp"

using namespace tadus;

TEST(split_1, str_alg_test) {
    std::string s{"java cplusplus haskell  noname  lua  golang    python"};

    std::vector<string> strs;

    bool res = s | str_alg::split{"\\s+"} | strs;

    EXPECT_TRUE(res);
    EXPECT_FALSE(strs.empty());
    EXPECT_EQ(strs.size(), 7);
    std::regex patten{"\\s+"};
    std::vector<string> x{
        std::sregex_token_iterator{s.begin(), s.end(), patten, -1},
        std::sregex_token_iterator{}};
    EXPECT_EQ(x, strs);
}

TEST(joint_1, str_alg_test) {
    vector<string> arr{{"kanakn"}, {"noway"}, {"forevery"}, {"bitch"}, {"sb"}};
    string str;
    bool ok = arr | str_alg::joint{" ### "} | str;

    string res = "kanakn ### noway ### forevery ### bitch ### sb";

    EXPECT_FALSE(str.empty());
    EXPECT_EQ(res, str);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
