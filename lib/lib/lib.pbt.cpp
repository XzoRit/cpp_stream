#include "utils.test.hpp"

#include <lib/lib.hpp>

#include <rapidcheck.h>

#include <string>
#include <string_view>

namespace
{
using ::xzr_test::lib::from_hex_string;
using ::xzr_test::lib::from_string;
using ::xzr_test::lib::to_hex_string;
using ::xzr_test::lib::to_string;
}
int main()
{
    auto res{true};
    // signed
    res &= ::rc::check("stream int", [](int a) {
        const auto str{to_string(a)};
        const auto b{from_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    res &= ::rc::check("stream long", [](long a) {
        const auto str{to_string(a)};
        const auto b{from_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    res &= ::rc::check("stream long long", [](long long a) {
        const auto str{to_string(a)};
        const auto b{from_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    res &= ::rc::check("stream signed char", [](signed char a) {
        const auto str{to_string(a)};
        const auto b{from_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    // unsigned
    res &= ::rc::check("stream unsigned int", [](unsigned int a) {
        const auto str{to_string(a)};
        const auto b{from_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    res &= ::rc::check("stream unsigned long", [](unsigned long a) {
        const auto str{to_string(a)};
        const auto b{from_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    res &= ::rc::check("stream unsigned long long", [](unsigned long long a) {
        const auto str{to_string(a)};
        const auto b{from_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    res &= ::rc::check("stream char", [](char a) {
        const auto str{to_string(a)};
        const auto b{from_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    res &= ::rc::check("stream unsigned char", [](unsigned char a) {
        const auto str{to_string(a)};
        const auto b{from_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    res &= ::rc::check("stream unsigned char", [](signed char a) {
        const auto str{to_string(a)};
        const auto b{from_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    // float
    res &= ::rc::check("stream float", [](float a) {
        const auto str{to_string(a)};
        const auto b{from_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    // string
    res &= ::rc::check("stream string", [](std::string a) {
        const auto str{to_string(a)};

        RC_ASSERT(a == str);
    });
    res &= ::rc::check("stream string_view", [](std::string a) {
        const auto str{to_string(std::string_view{a})};

        RC_ASSERT(a == str);
    });
    res &= ::rc::check("stream string_view", [](std::string a) {
        const auto str{to_string(a.c_str())};

        RC_ASSERT(a == str);
    });
    // hex
    res &= ::rc::check("stream hex int", [](int a) {
        const auto str{to_hex_string(a)};
        const auto b{from_hex_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    res &= ::rc::check("stream hex long", [](long a) {
        const auto str{to_hex_string(a)};
        const auto b{from_hex_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    res &= ::rc::check("stream hex long long", [](long long a) {
        const auto str{to_hex_string(a)};
        const auto b{from_hex_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    res &= ::rc::check("stream hex signed char", [](signed char a) {
        const auto str{to_hex_string(a)};
        const auto b{from_hex_string<decltype(a)>(str)};

        RC_ASSERT(a == b);
    });
    return !res;
}
