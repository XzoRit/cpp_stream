#pragma once

#include <boost/charconv/limits.hpp>
#include <boost/container/small_vector.hpp>

#include <array>
#include <charconv>
#include <string>
#include <string_view>
#include <utility>

namespace xzr::lib
{
inline namespace v1
{
template <class Int>
struct spec_int
{
    Int value{};
    int base{};
};
template <class Int>
auto hex(Int a) -> spec_int<Int>
{
    return {.value = a, .base = 16};
}
inline constexpr auto default_buffer_size{500u};
template <class Num>
using tmp_buf = std::array<char, boost::charconv::limits<Num>::max_chars10>;
class stream
{
  public:
    auto operator<<(int a) -> stream&
    {
        fill_int(a);
        return *this;
    }
    auto operator<<(unsigned int a) -> stream&
    {
        fill_int(a);
        return *this;
    }
    auto operator<<(long a) -> stream&
    {
        fill_int(a);
        return *this;
    }
    auto operator<<(unsigned long a) -> stream&
    {
        fill_int(a);
        return *this;
    }
    auto operator<<(long long a) -> stream&
    {
        fill_int(a);
        return *this;
    }
    auto operator<<(unsigned long long a) -> stream&
    {
        fill_int(a);
        return *this;
    }
    auto operator<<(double a) -> stream&
    {
        fill_double(a);
        return *this;
    }
    auto operator<<(long double a) -> stream&
    {
        fill_double(a);
        return *this;
    }
    auto operator<<(char a) -> stream&
    {
        fill_char(a);
        return *this;
    }
    auto operator<<(const std::string_view a) -> stream&
    {
        fill_str(a);
        return *this;
    }
    template <class Int>
    auto operator<<(spec_int<Int>&& a) -> stream&
    {
        fill_spec_int(std::move(a));
        return *this;
    }
    auto data() -> const char* const
    {
        if (m_buf.empty())
            return nullptr;
        return m_buf.data();
    }
    auto c_str() -> const char* const
    {
        return data();
    }
    auto str() -> std::string const
    {
        return {m_buf.data(), m_buf.data() + m_buf.size()};
    }

  private:
    auto fill_char(char a) -> void
    {
        m_buf.push_back(a);
    }
    auto fill_str(const std::string_view a) -> void
    {
        m_buf.insert(m_buf.end(), a.cbegin(), a.cend());
    }
    template <class Int>
    auto fill_spec_int(spec_int<Int>&& a) -> void
    {
        auto tmp{tmp_buf<decltype(a.value)>{}};
        auto offset{0u};
        if (a.base == 16)
        {
            tmp[0] = '0';
            tmp[1] = 'x';
            offset = 2;
        }
        const auto [ptr, ec]{
            std::to_chars(tmp.begin() + offset, tmp.end(), a.value, a.base)};
        if (ec == std::errc{})
            m_buf.insert(m_buf.end(), tmp.data(), ptr);
    }
    auto fill_int(auto a) -> void
    {
        fill_spec_int(spec_int<decltype(a)>{.value = a, .base = 10});
    }
    auto fill_double(auto a) -> void
    {
        auto tmp{tmp_buf<decltype(a)>{}};
        const auto [ptr, ec]{std::to_chars(tmp.begin(),
                                           tmp.end(),
                                           a,
                                           std::chars_format::general,
                                           6)};
        if (ec == std::errc{})
            m_buf.insert(m_buf.end(), tmp.data(), ptr);
    }
    boost::container::small_vector<char, default_buffer_size> m_buf{};
};
}
}
