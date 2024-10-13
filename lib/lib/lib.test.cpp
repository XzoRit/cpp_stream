#include <lib/lib.hpp>

#include <boost/test/unit_test.hpp>

#include <limits>
#include <string>

namespace
{
using ::xzr::lib::default_buffer_size;
using stream = ::xzr::lib::stream;

BOOST_AUTO_TEST_SUITE(lib_tests)

template <class Stream>
auto to_string(auto a) -> std::string
{
    auto s{Stream{}};
    s << a;
    return s.str();
}
template <class Stream>
auto to_string(signed char a) -> std::string
{
    auto s{Stream{}};
    s << int{a};
    return s.str();
}
template <class Stream>
auto to_string(unsigned char a) -> std::string
{
    auto s{Stream{}};
    s << unsigned{a};
    return s.str();
}
auto from_std_stream(auto a) -> std::string
{
    return to_string<std::ostringstream>(a);
}
auto from_stream(auto a) -> std::string
{
    return to_string<stream>(a);
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
}
BOOST_AUTO_TEST_CASE(stream_double)
{
    BOOST_REQUIRE(cmp_streams<float>());
    BOOST_REQUIRE(cmp_streams<double>());
    BOOST_REQUIRE(cmp_streams<long double>());
}
BOOST_AUTO_TEST_CASE(stream_str)
{
    BOOST_REQUIRE(cmp_streams<char>());
}
BOOST_AUTO_TEST_CASE(getter)
{
    stream s{};
    BOOST_REQUIRE(s.data() == nullptr);
    BOOST_REQUIRE(s.c_str() == s.data());
    BOOST_REQUIRE(s.str().empty());

    s << 123;
    const auto* dat_ptr{s.data()};
    BOOST_REQUIRE(dat_ptr != nullptr);
    BOOST_REQUIRE(dat_ptr[0] == '1');
    BOOST_REQUIRE(dat_ptr[1] == '2');
    BOOST_REQUIRE(dat_ptr[2] == '3');
    BOOST_REQUIRE(dat_ptr[3] == '\0');
    BOOST_REQUIRE(s.c_str() == dat_ptr);
    BOOST_REQUIRE(s.str() == "123");

    s << std::string(default_buffer_size - 3u, 'X');
    BOOST_REQUIRE(dat_ptr == s.data());
    BOOST_REQUIRE(s.c_str() == s.data());
    BOOST_REQUIRE(s.str() ==
                  "123" + std::string(default_buffer_size - 3u, 'X'));

    s << 'a';
    BOOST_REQUIRE(dat_ptr != s.data());
    BOOST_REQUIRE(s.data()[default_buffer_size] == 'a');
    BOOST_REQUIRE(s.data()[default_buffer_size + 1u] == '\0');
    BOOST_REQUIRE(s.c_str() == s.data());
    BOOST_REQUIRE(s.str() ==
                  "123" + std::string(default_buffer_size - 3u, 'X') + 'a');
}

BOOST_AUTO_TEST_SUITE_END()
}
