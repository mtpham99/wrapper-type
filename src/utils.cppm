export module wrapper:utils;

import std;

import :wrap;

namespace wrapper
{

template<typename T, typename... Us>
concept any_of = (... || std::same_as<T, Us>);

template<typename T>
struct is_wrap : std::false_type
{

};

template<typename wrapper_type, typename wrap_id, typename... wrap_ops>
struct is_wrap<wrap<wrapper_type, wrap_id, wrap_ops...>> : std::true_type
{

};

template<typename T>
inline constexpr bool is_wrap_v = is_wrap<T>::value;

namespace concepts
{

template<typename T>
concept wrap = is_wrap_v<T>;

};

constexpr decltype(auto)
unwrap(auto&& val) noexcept
{
  using val_type = std::remove_cvref_t<decltype(val)>;

  if constexpr (is_wrap_v<val_type>) {
    return std::forward_like<decltype(val)>(val.get_underlying());
  } else {
    return std::forward<decltype(val)>(val);
  }
}

} // namespace wrapper
