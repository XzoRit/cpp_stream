#pragma once

#include <lib/lib.hpp>

#include <array>
#include <concepts>
#include <cstdint>
#include <cstdio>
#include <sstream>
#include <string>

namespace xzr_test::lib
{
inline auto to_string_with_std(std::integral auto a) -> std::string
{
    auto s{std::ostringstream{}};
    s << a;
    return s.str();
}
inline auto to_string_with_std(double a) -> std::string
{
    auto buf{std::array<char, 32>{}};
    const auto num_chars{std::snprintf(buf.data(), buf.size(), "%le", a)};
    return {buf.data(), buf.data() + num_chars};
}
inline auto to_string_with_std(long double a) -> std::string
{
    auto buf{std::array<char, 32>{}};
    const auto num_chars{std::snprintf(buf.data(), buf.size(), "%Lg", a)};
    return {buf.data(), buf.data() + num_chars};
}
inline auto to_string_with_std(signed char a) -> std::string
{
    auto s{std::ostringstream{}};
    s << int{a};
    return s.str();
}
inline auto to_string_with_std(unsigned char a) -> std::string
{
    auto s{std::ostringstream{}};
    s << unsigned{a};
    return s.str();
}
inline auto from_std_stream(auto a) -> std::string
{
    return to_string_with_std(a);
}
inline auto to_string(auto a) -> std::string
{
    auto s{::xzr::lib::stream{}};
    s << a;
    return s.str();
}
inline auto from_std_hex_stream(unsigned char a) -> std::string
{
    auto s{std::ostringstream{}};
    s << std::hex;
    s.operator<<(a);
    return s.str();
}
inline auto from_std_hex_stream(std::unsigned_integral auto a) -> std::string
{
    auto s{std::ostringstream{}};
    s << std::hex << a;
    return s.str();
}
inline auto from_std_hex_stream(std::signed_integral auto a) -> std::string
{
    auto s{std::ostringstream{}};
    if (a < 0)
        s << '-';
    s << std::hex << std::abs(a);
    return s.str();
}
inline auto to_hex_string(auto a) -> std::string
{
    auto s{::xzr::lib::stream{}};
    s << ::xzr::lib::hex(a);
    return s.str();
}
template <class Num>
inline auto from_string(const std::string_view s) -> Num
{
    auto n{Num{}};
    std::from_chars(s.data(), s.data() + s.size(), n);
    return n;
}
template <>
inline auto from_string<char>(const std::string_view s) -> char
{
    return s[0];
}
template <class Num>
inline auto from_string(const std::string_view s, int base) -> Num
{
    auto n{Num{}};
    std::from_chars(s.data(), s.data() + s.size(), n, base);
    return n;
}
template <class Num>
inline auto from_hex_string(const std::string_view s) -> Num
{
    return from_string<Num>(s, 16);
}
}
