export module wrapper:ops;

import :utils;

namespace wrapper::ops
{

template<typename T, typename... Us>
struct addition_ops
{
  friend constexpr T&
  operator+=(T &lhs, any_of<Us...> auto const& rhs) noexcept
  {
    unwrap(lhs) += unwrap(rhs);
    return lhs;
  }

  friend constexpr T
  operator+(T const& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    auto tmp = lhs;
    tmp += rhs;
    return tmp;
  }
};

export struct addition
{
  template<concepts::wrap wrap>
  using op = addition_ops<wrap, wrap>;
};

export template<typename... operands>
struct addition_with
{
  template<concepts::wrap wrap>
  using op = addition_ops<wrap, operands...>;
};

template<typename T, typename... Us>
struct subtraction_ops
{
  friend constexpr T&
  operator-=(T &lhs, any_of<Us...> auto const& rhs) noexcept
  {
    unwrap(lhs) -= unwrap(rhs);
    return lhs;
  }

  friend constexpr T
  operator-(T const& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    auto tmp = lhs;
    tmp -= rhs;
    return tmp;
  }
};

export struct subtraction
{
  template<concepts::wrap wrap>
  using op = subtraction_ops<wrap, wrap>;
};

export template<typename... operands>
struct subtraction_with
{
  template<concepts::wrap wrap>
  using op = subtraction_ops<wrap, operands...>;
};

template<typename T, typename... Us>
struct multiplication_ops
{
  friend constexpr T&
  operator*=(T& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    unwrap(lhs) *= unwrap(rhs);
    return lhs;
  }

  friend constexpr T
  operator*(T const& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    auto tmp = lhs;
    tmp *= rhs;
    return tmp;
  }
};

export struct multiplication
{
  template<concepts::wrap wrap>
  using op = multiplication_ops<wrap, wrap>;
};

export template<typename... operands>
struct multiplication_with
{
  template<concepts::wrap wrap>
  using op = multiplication_ops<wrap, operands...>;
};

template<typename T, typename... Us>
struct division_ops
{
  friend constexpr T&
  operator/=(T& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    unwrap(lhs) /= unwrap(rhs);
    return lhs;
  }

  friend constexpr T
  operator/(T const& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    auto tmp = lhs;
    tmp /= rhs;
    return tmp;
  }
};

export struct division
{
  template<concepts::wrap wrap>
  using op = division_ops<wrap, wrap>;
};

export template<typename... operands>
struct division_with
{
  template<concepts::wrap wrap>
  using op = division_ops<wrap, operands...>;
};

template<typename T, typename... Us>
struct modulus_ops
{
  friend constexpr T&
  operator%=(T& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    unwrap(lhs) %= unwrap(rhs);
    return lhs;
  }

  friend constexpr T
  operator%(T const& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    auto tmp = lhs;
    tmp %= rhs;
    return tmp;
  }
};

export struct modulus
{
  template<concepts::wrap wrap>
  using op = modulus_ops<wrap, wrap>;
};

export template<typename... operands>
struct modulus_with
{
  template<concepts::wrap wrap>
  using op = modulus_ops<wrap, operands...>;
};

template<typename T> struct increment_ops
{
  friend constexpr T&
  operator++(T &t) noexcept
  {
    ++unwrap(t);
    return t;
  }

  friend constexpr T
  operator++(T& t, int) noexcept
  {
    auto tmp = t;
    ++t;
    return tmp;
  }
};

export struct increment
{
  template<concepts::wrap wrap>
  using op = increment_ops<wrap>;
};

template<typename T>
struct decrement_ops
{
  friend constexpr T&
  operator--(T& t) noexcept
  {
    --unwrap(t);
    return t;
  }

  friend constexpr T
  operator--(T& t, int) noexcept
  {
    auto tmp = t;
    --t;
    return tmp;
  }
};

export struct decrement
{
  template<concepts::wrap wrap>
  using op = decrement_ops<wrap>;
};

template<typename T, typename... Us>
struct bit_or_ops
{
  friend constexpr T&
  operator|=(T& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    unwrap(lhs) |= unwrap(rhs);
    return lhs;
  }

  friend constexpr T
  operator|(T const& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    auto tmp = lhs;
    tmp |= rhs;
    return tmp;
  }
};

export struct bit_or
{
  template<concepts::wrap wrap>
  using op = bit_or_ops<wrap, wrap>;
};

export template<typename... operands>
struct bit_or_with
{
  template<concepts::wrap wrap>
  using op = bit_or_ops<wrap, operands...>;
};

template<typename T, typename... Us> struct bit_and_ops
{
  friend constexpr T&
  operator&=(T& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    unwrap(lhs) &= unwrap(rhs);
    return lhs;
  }

  friend constexpr T
  operator&(T const& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    auto tmp = lhs;
    tmp &= rhs;
    return tmp;
  }
};

export struct bit_and
{
  template<concepts::wrap wrap>
  using op = bit_and_ops<wrap, wrap>;
};

export template<typename... operands>
struct bit_and_with
{
  template<concepts::wrap wrap>
  using op = bit_and_ops<wrap, operands...>;
};

template<typename T, typename... Us>
struct bit_xor_ops
{
  friend constexpr T&
  operator^=(T& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    unwrap(lhs) ^= unwrap(rhs);
    return lhs;
  }

  friend constexpr T
  operator^(T const& lhs, any_of<Us...> auto const& rhs) noexcept
  {
    auto tmp = lhs;
    tmp ^= rhs;
    return tmp;
  }
};

export struct bit_xor
{
  template<concepts::wrap wrap>
  using op = bit_xor_ops<wrap, wrap>;
};

export template<typename... operands>
struct bit_xor_with
{
  template<concepts::wrap wrap>
  using op = bit_xor_ops<wrap, operands...>;
};

template<typename T>
struct bit_shift_ops
{
  friend constexpr T&
  operator<<=(T& lhs, std::integral auto rhs) noexcept
  {
    unwrap(lhs) <<= rhs;
    return lhs;
  }

  friend constexpr T
  operator<<(T const& lhs, std::integral auto rhs) noexcept
  {
    auto tmp = lhs;
    tmp <<= rhs;
    return tmp;
  }

  friend constexpr T&
  operator>>=(T& lhs, std::integral auto rhs) noexcept
  {
    unwrap(lhs) >>= rhs;
    return lhs;
  }

  friend constexpr T
  operator>>(T const& lhs, std::integral auto rhs) noexcept
  {
    auto tmp = lhs;
    tmp >>= rhs;
    return tmp;
  }
};

export struct bit_shift
{
  template<concepts::wrap wrap>
  using op = bit_shift_ops<wrap>;
};

template<typename T>
struct bit_not_ops
{
  friend constexpr T
  operator~(T const& t) noexcept
  {
    return static_cast<T>(~unwrap(t));
  }
};

export struct bit_not
{
  template<concepts::wrap wrap>
  using op = bit_not_ops<wrap>;
};

template<typename T, typename... Us>
struct comparison_ops
{
  friend constexpr bool
  operator<(T const& lhs, T const& rhs) noexcept
  {
    return unwrap(lhs) < unwrap(rhs);
  }

  friend constexpr bool
  operator<=(T const& lhs, T const& rhs) noexcept
  {
    return unwrap(lhs) <= unwrap(rhs);
  }

  friend constexpr bool
  operator>(T const& lhs, T const& rhs) noexcept
  {
    return unwrap(lhs) > unwrap(rhs);
  }

  friend constexpr bool
  operator>=(T const& lhs, T const& rhs) noexcept
  {
    return unwrap(lhs) >= unwrap(rhs);
  }

  friend constexpr bool
  operator==(T const& lhs, T const& rhs) noexcept
  {
    return unwrap(lhs) == unwrap(rhs);
  }
};

export struct comparison
{
  template<concepts::wrap wrap>
  using op = comparison_ops<wrap, wrap>;
};

export template<typename... operands>
struct comparison_with
{
  template<concepts::wrap wrap>
  using op = comparison_ops<wrap, operands...>;
};

template<typename T, typename... Us>
struct conversion_op
{
  template<any_of<Us...> R> explicit constexpr
  operator R() const noexcept
  {
    return static_cast<R>(unwrap(*static_cast<T const *const>(this)));
  }
};

export template<typename... operands>
struct conversion_to
{
  template<concepts::wrap wrap>
  using op = conversion_op<wrap, operands...>;
};

template<typename T, typename... Us>
struct all_arithmetic_ops
  : addition_ops<T, Us...>,
    subtraction_ops<T, Us...>,
    multiplication_ops<T, Us...>,
    division_ops<T, Us...>,
    modulus_ops<T, Us...>,
    increment_ops<T>,
    decrement_ops<T>
{

};

export struct all_arithmetic
{
  template<concepts::wrap wrap>
  using op = all_arithmetic_ops<wrap, wrap>;
};

export template<typename... operands>
struct all_arithmetic_with
{
  template<concepts::wrap wrap>
  using op = all_arithmetic_ops<wrap, operands...>;
};

template<typename T, typename... Us>
struct all_bit_ops
  : bit_or_ops<T, Us...>,
    bit_and_ops<T, Us...>,
    bit_xor_ops<T, Us...>,
    bit_shift_ops<T>,
    bit_not_ops<T>
{

};

export struct all_bitwise
{
  template<concepts::wrap wrap>
  using op = all_bit_ops<wrap, wrap>;
};

export template<typename... operands>
struct all_bitwise_with
{
  template<concepts::wrap wrap>
  using op = all_bit_ops<wrap, operands...>;
};

} // namespace wrapper::ops
