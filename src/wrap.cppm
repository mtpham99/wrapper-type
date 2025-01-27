export module wrapper:wrap;

import std;

namespace wrapper
{

template<typename wrapped_type>
class wrap_base
{
private:
  wrapped_type _val;

public:
  explicit constexpr wrap_base()
    noexcept(std::is_nothrow_default_constructible_v<wrapped_type>)
    requires(std::is_default_constructible_v<wrapped_type>)
  = default;

  explicit constexpr wrap_base(wrapped_type const& val)
    noexcept(std::is_nothrow_copy_constructible_v<wrapped_type>)
    requires(std::is_copy_constructible_v<wrapped_type>)
      : _val{ val }
  {

  }

  explicit constexpr wrap_base(wrapped_type&& val)
    noexcept(std::is_nothrow_move_constructible_v<wrapped_type>)
    requires(std::is_move_constructible_v<wrapped_type>)
      : _val{ std::move(val) }
  {

  }

  constexpr wrap_base(wrap_base const&)
    noexcept(std::is_nothrow_copy_constructible_v<wrapped_type>)
    requires(std::is_copy_constructible_v<wrapped_type>)
  = default;

  constexpr wrap_base(wrap_base&&)
    noexcept(std::is_nothrow_move_constructible_v<wrapped_type>)
    requires(std::is_move_constructible_v<wrapped_type>)
  = default;

  constexpr wrap_base&
  operator=(wrap_base const&)
    noexcept(std::is_nothrow_copy_constructible_v<wrapped_type>)
    requires(std::is_copy_constructible_v<wrapped_type>)
  = default;

  constexpr wrap_base&
  operator=(wrap_base&&)
    noexcept(std::is_nothrow_move_constructible_v<wrapped_type>)
    requires(std::is_move_constructible_v<wrapped_type>)
  = default;

  constexpr ~wrap_base()
    noexcept(std::is_nothrow_destructible_v<wrapped_type>)
    requires(std::is_destructible_v<wrapped_type>)
  = default;

  constexpr decltype(auto)
  get_underlying(this auto&& self) noexcept
  {
    return std::forward_like<decltype(self)>(self._val);
  }
};

export template<typename wrapped_type, typename wrap_id, typename... wrap_ops>
class wrap
  : public wrap_base<wrapped_type>,
    public wrap_ops::template op<wrap<wrapped_type, wrap_id, wrap_ops...>>...
{
public:
  using value_type = wrapped_type;
  using value_id = wrap_id;

  using wrap_base<wrapped_type>::wrap_base;
};

} // namespace wrapper
