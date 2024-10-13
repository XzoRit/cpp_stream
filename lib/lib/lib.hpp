#pragma once

#include <boost/charconv/limits.hpp>
#include <boost/container/small_vector.hpp>

#include <array>
#include <charconv>
#include <string>
#include <string_view>

namespace xzr
{
namespace lib
{
inline namespace v1
{
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
    auto fill_int(auto a) -> void
    {
        auto tmp{tmp_buf<decltype(a)>{}};
        const auto [ptr, ec]{std::to_chars(tmp.begin(), tmp.end(), a)};
        if (ec == std::errc{})
            m_buf.insert(m_buf.end(), tmp.data(), ptr);
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
}
