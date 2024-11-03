#include <boost/config/helper_macros.hpp>
#include <lib/lib.hpp>

#include <boost/test/unit_test.hpp>

#include <array>
#include <charconv>
#include <concepts>
#include <cstdio>
#include <ios>
#include <limits>
#include <sstream>
#include <string>

namespace
{
using ::xzr::lib::default_buffer_size;
using ::xzr::lib::hex;
using stream = ::xzr::lib::stream;
using std_stream = std::ostringstream;

BOOST_AUTO_TEST_SUITE(lib_tests)

auto to_string_with_std(std::integral auto a) -> std::string
{
    auto s{std_stream{}};
    s << a;
    return s.str();
}
auto to_string_with_std(double a) -> std::string
{
    auto buf{std::array<char, 32>{}};
    const auto num_chars{std::snprintf(buf.data(), buf.size(), "%le", a)};
    return {buf.data(), buf.data() + num_chars};
}
auto to_string_with_std(long double a) -> std::string
{
    auto buf{std::array<char, 32>{}};
    const auto num_chars{std::snprintf(buf.data(), buf.size(), "%Lg", a)};
    return {buf.data(), buf.data() + num_chars};
}
auto to_string_with_std(signed char a) -> std::string
{
    auto s{std_stream{}};
    s << int{a};
    return s.str();
}
auto to_string_with_std(unsigned char a) -> std::string
{
    auto s{std_stream{}};
    s << unsigned{a};
    return s.str();
}
auto from_std_stream(auto a) -> std::string
{
    return to_string_with_std(a);
}
auto from_stream(auto a) -> std::string
{
    auto s{stream{}};
    s << a;
    return s.str();
}
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
    return cmp_str(from_std_stream(a), from_stream(a));
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
auto from_std_hex_stream(std::unsigned_integral auto a) -> std::string
{
    auto s{std::ostringstream{}};
    s << std::hex << a;
    return s.str();
}
auto from_std_hex_stream(std::signed_integral auto a) -> std::string
{
    auto s{std::ostringstream{}};
    if (a < 0)
        s << '-';
    s << std::hex << std::abs(a);
    return s.str();
}
auto from_hex_stream(auto a) -> std::string
{
    auto s{stream{}};
    s << hex(a);
    return s.str();
}
auto cmp_hex_str(auto a) -> boost::test_tools::predicate_result
{
    return cmp_str(from_std_hex_stream(a), from_hex_stream(a));
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
    stream str{};
    str << a;
    const auto s{str.str()};
    auto b{Num{}};
    std::from_chars(s.data(), s.data() + s.size(), b);
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
    stream s{};
    s << a;
    return cmp_roundtrip<Num>(a);
}
BOOST_AUTO_TEST_CASE(stream_int)
{
    BOOST_REQUIRE(cmp_streams<signed char>());
    BOOST_REQUIRE(cmp_streams<unsigned char>());
    BOOST_REQUIRE(cmp_streams<short>());
    BOOST_REQUIRE(cmp_streams<unsigned short>());
    BOOST_REQUIRE(cmp_streams<int>());
    BOOST_REQUIRE(cmp_streams<unsigned int>());
    BOOST_REQUIRE(cmp_streams<long>());
    BOOST_REQUIRE(cmp_streams<unsigned long>());
    BOOST_REQUIRE(cmp_streams<long long>());
    BOOST_REQUIRE(cmp_streams<unsigned long long>());

    BOOST_REQUIRE(roundtrip<signed char>());
    BOOST_REQUIRE(roundtrip<unsigned char>());
    BOOST_REQUIRE(roundtrip<short>());
    BOOST_REQUIRE(roundtrip<unsigned short>());
    BOOST_REQUIRE(roundtrip<int>());
    BOOST_REQUIRE(roundtrip<unsigned int>());
    BOOST_REQUIRE(roundtrip<long>());
    BOOST_REQUIRE(roundtrip<unsigned long>());
    BOOST_REQUIRE(roundtrip<long long>());
    BOOST_REQUIRE(roundtrip<unsigned long long>());
}
BOOST_AUTO_TEST_CASE(stream_double)
{
    BOOST_REQUIRE(roundtrip<float>());
    BOOST_REQUIRE(roundtrip<double>());
    BOOST_REQUIRE(roundtrip<long double>());
}
BOOST_AUTO_TEST_CASE(stream_str)
{
    BOOST_REQUIRE(cmp_streams<char>());
}
BOOST_AUTO_TEST_CASE(getter)
{
    stream s{};
    BOOST_REQUIRE(std::string{s.c_str()}.empty());
    BOOST_REQUIRE(s.str().empty());

    s << 123;
    const auto* dat_ptr{s.c_str()};
    BOOST_REQUIRE(dat_ptr != nullptr);
    BOOST_REQUIRE(dat_ptr[0] == '1');
    BOOST_REQUIRE(dat_ptr[1] == '2');
    BOOST_REQUIRE(dat_ptr[2] == '3');
    BOOST_REQUIRE(dat_ptr[3] == '\0');
    BOOST_REQUIRE(s.c_str() == dat_ptr);
    BOOST_REQUIRE(s.str() == "123");

    s << std::string(default_buffer_size - 3u, 'X');
    BOOST_REQUIRE_EQUAL(dat_ptr, s.c_str());
    BOOST_REQUIRE(s.str() ==
                  "123" + std::string(default_buffer_size - 3u, 'X'));

    s << 'a';
    BOOST_REQUIRE(dat_ptr != s.c_str());
    BOOST_REQUIRE(s.c_str()[default_buffer_size] == 'a');
    BOOST_REQUIRE(s.c_str()[default_buffer_size + 1u] == '\0');
    BOOST_REQUIRE(s.str() ==
                  "123" + std::string(default_buffer_size - 3u, 'X') + 'a');
}
BOOST_AUTO_TEST_CASE(fmt_hex)
{
    // BOOST_REQUIRE(cmp_hex_streams<signed char>());
    // BOOST_REQUIRE(cmp_hex_streams<unsigned char>());
    BOOST_REQUIRE(cmp_hex_streams<short>());
    BOOST_REQUIRE(cmp_hex_streams<unsigned short>());
    BOOST_REQUIRE(cmp_hex_streams<int>());
    BOOST_REQUIRE(cmp_hex_streams<unsigned int>());
    BOOST_REQUIRE(cmp_hex_streams<long>());
    BOOST_REQUIRE(cmp_hex_streams<unsigned long>());
    BOOST_REQUIRE(cmp_hex_streams<long long>());
    BOOST_REQUIRE(cmp_hex_streams<unsigned long long>());
}

BOOST_AUTO_TEST_SUITE_END()
}
