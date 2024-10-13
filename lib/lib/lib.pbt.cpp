#include <lib/lib.hpp>

#include <rapidcheck.h>

#include <string>
#include <string_view>

namespace
{
using ::xzr::lib::stream;
auto to_string(auto a) -> std::string
{
    stream s{};
    s << a;
    return s.str();
}
}
int main()
{
    // signed
    ::rc::check("stream int", [](int a) {
        const auto str{to_string(a)};
        const auto b{std::stoll(str)};

        RC_ASSERT(a == b);
    });
    ::rc::check("stream long", [](long a) {
        const auto str{to_string(a)};
        const auto b{std::stoll(str)};

        RC_ASSERT(a == b);
    });
    ::rc::check("stream long long", [](long long a) {
        const auto str{to_string(a)};
        const auto b{std::stoll(str)};

        RC_ASSERT(a == b);
    });
    ::rc::check("stream signed char", [](signed char a) {
        const auto str{to_string(a)};
        const auto b{std::stoll(str)};

        RC_ASSERT(a == b);
    });
    // unsigned
    ::rc::check("stream unsigned int", [](unsigned int a) {
        const auto str{to_string(a)};
        const auto b{std::stoull(str)};

        RC_ASSERT(a == b);
    });
    ::rc::check("stream unsigned long", [](unsigned long a) {
        const auto str{to_string(a)};
        const auto b{std::stoull(str)};

        RC_ASSERT(a == b);
    });
    ::rc::check("stream unsigned long long", [](unsigned long long a) {
        const auto str{to_string(a)};
        const auto b{std::stoull(str)};

        RC_ASSERT(a == b);
    });
    ::rc::check("stream unsigned char", [](unsigned char a) {
        const auto str{to_string(a)};
        const auto b{std::stoull(str)};

        RC_ASSERT(a == b);
    });
    // char/string
    ::rc::check("stream char", [](char a) {
        const auto str{to_string(a)};

        RC_ASSERT(str.size() == 1u);
        RC_ASSERT(a == str[0]);
    });
    ::rc::check("stream string", [](std::string a) {
        const auto str{to_string(a)};

        RC_ASSERT(a == str);
    });
    ::rc::check("stream string_view", [](std::string a) {
        const auto str{to_string(std::string_view{a})};

        RC_ASSERT(a == str);
    });
    return 0;
}
