#include "boost.test.hpp"

#include <lib/lib.hpp>

#include <boost/config/helper_macros.hpp>
#include <boost/test/unit_test.hpp>

#include <cstdio>
#include <sstream>
#include <string>

namespace
{
using ::xzr::lib::default_buffer_size;
using ::xzr_test::lib::cmp_hex_streams;
using ::xzr_test::lib::cmp_streams;
using ::xzr_test::lib::roundtrip;
using stream = ::xzr::lib::stream;
using std_stream = std::ostringstream;

BOOST_AUTO_TEST_SUITE(lib_tests)
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
