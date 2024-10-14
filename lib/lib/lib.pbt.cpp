#include <lib/lib.hpp>

#include <rapidcheck.h>

#include <ios>
#include <sstream>
#include <string>
#include <string_view>

namespace
{
using ::xzr::lib::hex;
using ::xzr::lib::stream;
auto to_string(auto a) -> std::string
{
    stream s{};
    s << a;
    return s.str();
}
auto to_std_string(auto a) -> std::string
{
    auto s{std::ostringstream{}};
    s << a;
    return s.str();
}
auto to_hex_string(auto a) -> std::string
{
    stream s{};
    s << hex(a);
    return s.str();
}
auto to_std_hex_string(auto a) -> std::string
{
    auto s{std::ostringstream{}};
    s << std::hex << a;
    return s.str();
}
}
int main()
{
    auto res{true};
    // signed
    res &= ::rc::check("stream int", [](int a) {
        const auto str{to_string(a)};
        const auto std{to_std_string(a)};

        RC_ASSERT(str == std);
    });
    res &= ::rc::check("stream long", [](long a) {
        const auto str{to_string(a)};
        const auto std{to_std_string(a)};

        RC_ASSERT(str == std);
    });
    res &= ::rc::check("stream long long", [](long long a) {
        const auto str{to_string(a)};
        const auto std{to_std_string(a)};

        RC_ASSERT(str == std);
    });
    res &= ::rc::check("stream signed char", [](signed char a) {
        const auto str{to_string(a)};
        const auto std{to_std_string(a)};

        RC_ASSERT(str == std);
    });
    // unsigned
    res &= ::rc::check("stream unsigned int", [](unsigned int a) {
        const auto str{to_string(a)};
        const auto std{to_std_string(a)};

        RC_ASSERT(str == std);
    });
    res &= ::rc::check("stream unsigned long", [](unsigned long a) {
        const auto str{to_string(a)};
        const auto std{to_std_string(a)};

        RC_ASSERT(str == std);
    });
    res &= ::rc::check("stream unsigned long long", [](unsigned long long a) {
        const auto str{to_string(a)};
        const auto std{to_std_string(a)};

        RC_ASSERT(str == std);
    });
    res &= ::rc::check("stream unsigned char", [](unsigned char a) {
        const auto str{to_string(a)};
        const auto std{to_std_string(a)};

        RC_ASSERT(str == std);
    });
    // float
    res &= ::rc::check("stream float", [](float a) {
        const auto str{to_string(a)};
        const auto std{to_std_string(a)};

        RC_ASSERT(str == std);
    });
    // char/string
    res &= ::rc::check("stream char", [](char a) {
        const auto str{to_string(a)};

        RC_ASSERT(str.size() == 1u);
        RC_ASSERT(a == str[0]);
    });
    res &= ::rc::check("stream string", [](std::string a) {
        const auto str{to_string(a)};

        RC_ASSERT(a == str);
    });
    res &= ::rc::check("stream string_view", [](std::string a) {
        const auto str{to_string(std::string_view{a})};

        RC_ASSERT(a == str);
    });
    // hex
    res &= ::rc::check("stream hex int", [](int a) {
        const auto str{to_hex_string(a)};
        const auto std{to_std_hex_string(a)};

        RC_ASSERT(str == std);
    });
    res &= ::rc::check("stream hex long", [](long a) {
        const auto str{to_hex_string(a)};
        const auto std{to_std_hex_string(a)};

        RC_ASSERT(str == std);
    });
    res &= ::rc::check("stream hex long long", [](long long a) {
        const auto str{to_hex_string(a)};
        const auto std{to_std_hex_string(a)};

        RC_ASSERT(str == std);
    });
    res &= ::rc::check("stream hex signed char", [](signed char a) {
        const auto str{to_hex_string(a)};
        const auto std{to_std_hex_string(a)};

        RC_ASSERT(str == std);
    });
    return res;
}
