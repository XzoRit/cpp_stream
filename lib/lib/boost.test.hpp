#pragma once

#include "utils.test.hpp"

#include <lib/lib.hpp>

#include <boost/test/unit_test.hpp>

#include <cstdio>
#include <limits>

namespace xzr_test::lib
{
auto cmp_str(auto a, auto b) -> boost::test_tools::predicate_result
{
    if (a != b)
    {
        auto res{boost::test_tools::predicate_result{false}};
        res.message() << "not equal [" << a << " != " << b << "]";
        return res;
    }
    return true;
}
auto cmp_str(auto a) -> boost::test_tools::predicate_result
{
    return cmp_str(from_std_stream(a), to_string(a));
}
template <class Num>
using lim = std::numeric_limits<Num>;
template <class Num>
auto cmp_streams() -> boost::test_tools::predicate_result
{
    using lim = lim<Num>;
    auto res{cmp_str(lim::min())};
    if (!res)
        return res;
    res = cmp_str(lim::max());
    if (!res)
        return res;
    res = cmp_str(lim::lowest());
    if (!res)
        return res;
    res = cmp_str(lim::epsilon());
    if (!res)
        return res;
    return res;
}
auto cmp_hex_str(auto a) -> boost::test_tools::predicate_result
{
    return cmp_str(from_std_hex_stream(a), to_hex_string(a));
}
template <class Num>
auto cmp_hex_streams() -> boost::test_tools::predicate_result
{
    using lim = lim<Num>;
    auto res{cmp_hex_str(lim::min())};
    if (!res)
        return res;
    res = cmp_hex_str(lim::max());
    if (!res)
        return res;
    res = cmp_hex_str(lim::lowest());
    if (!res)
        return res;
    res = cmp_hex_str(lim::epsilon());
    if (!res)
        return res;
    return res;
}
template <class Num>
auto cmp_roundtrip(Num a) -> boost::test_tools::predicate_result
{
    auto str{::xzr::lib::stream{}};
    str << a;
    const auto s{str.str()};
    auto b{from_string<Num>(s)};
    if (a != b)
    {
        auto res{boost::test_tools::predicate_result{false}};
        res.message() << "not equal [" << a << " != " << b << "]";
        return res;
    }
    return true;
}
template <class Num>
auto roundtrip() -> boost::test_tools::predicate_result
{
    using lim = lim<Num>;
    auto res{cmp_roundtrip(lim::min())};
    if (!res)
        return res;
    res = cmp_roundtrip(lim::max());
    if (!res)
        return res;
    res = cmp_roundtrip(lim::lowest());
    if (!res)
        return res;
    res = cmp_roundtrip(lim::epsilon());
    if (!res)
        return res;
    return res;
    const auto a{lim::min()};
    auto s{::xzr::lib::stream{}};
    s << a;
    return cmp_roundtrip<Num>(a);
}
}
