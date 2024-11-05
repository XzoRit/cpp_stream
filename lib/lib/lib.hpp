#pragma once

#include <boost/charconv/limits.hpp>
#include <boost/container/small_vector.hpp>

#include <array>
#include <charconv>
#include <concepts>
#include <string>
#include <string_view>
#include <system_error>

namespace xzr::lib
{
inline namespace v1
{
template <std::integral Int>
struct spec_int
{
    Int value;
    int base;
};
auto hex(bool) = delete;
auto hex(char8_t) = delete;
auto hex(char16_t) = delete;
auto hex(char32_t) = delete;
auto hex(wchar_t) = delete;
auto hex(std::integral auto a)
{
    return spec_int{.value = a, .base = 16};
}
inline constexpr auto default_buffer_size{500u};
template <class Num>
using tmp_buf = std::array<char, boost::charconv::limits<Num>::max_chars10>;
template <class Num>
using tmp_max_buf = std::array<char, boost::charconv::limits<Num>::max_chars>;
class stream
{
  public:
    // integral
    auto operator<<(bool) -> stream& = delete;
    auto operator<<(char8_t) -> stream& = delete;
    auto operator<<(char16_t) -> stream& = delete;
    auto operator<<(char32_t) -> stream& = delete;
    auto operator<<(wchar_t) -> stream& = delete;
    auto operator<<(std::integral auto a) -> stream&
    {
        fill_int(a);
        return *this;
    }
    // floating_point
    auto operator<<(std::floating_point auto a) -> stream&
    {
        fill_double(a);
        return *this;
    }
    // string
    auto operator<<(char a) -> stream&
    {
        fill_char(a);
        return *this;
    }
    auto operator<<(const char* a) -> stream&
    {
        fill_str(a);
        return *this;
    }
    auto operator<<(const std::string_view a) -> stream&
    {
        fill_str(a);
        return *this;
    }
    // integral with different base
    template <std::integral Int>
    auto operator<<(spec_int<Int> a) -> stream&
    {
        fill_spec_int(a);
        return *this;
    }
    auto c_str() const -> const char*
    {
        m_buf.reserve(m_buf.size() + 1);
        *const_cast<char*>(m_buf.data() + m_buf.size()) = '\0';
        return m_buf.data();
    }
    auto str() -> std::string const
    {
        return {m_buf.cbegin(), m_buf.cend()};
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
        const auto [ptr, ec]{std::to_chars(tmp.begin(), tmp.end(), a)};
        if (ec == std::errc{})
            m_buf.insert(m_buf.end(), tmp.data(), ptr);
    }
    template <std::integral Int>
    auto fill_spec_int(spec_int<Int> a) -> void
    {
        auto tmp{tmp_max_buf<Int>{}};
        const auto [ptr,
                    ec]{std::to_chars(tmp.begin(), tmp.end(), a.value, a.base)};
        if (ec == std::errc{})
            m_buf.insert(m_buf.end(), tmp.data(), ptr);
    }
    using Buffer = boost::container::small_vector<char, default_buffer_size>;
    mutable Buffer m_buf{};
};
}
}
