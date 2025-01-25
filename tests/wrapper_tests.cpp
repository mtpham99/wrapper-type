#include <doctest/doctest.h>

import std;

import wrapper;

template<typename T, typename U> concept can_add      = requires { std::declval<T>() + std::declval<U>(); };
template<typename T, typename U> concept can_subtract = requires { std::declval<T>() - std::declval<U>(); };
template<typename T, typename U> concept can_multiply = requires { std::declval<T>() * std::declval<U>(); };
template<typename T, typename U> concept can_divide   = requires { std::declval<T>() / std::declval<U>(); };
template<typename T, typename U> concept can_modulo   = requires { std::declval<T>() % std::declval<U>(); };
template<typename T, typename U> concept can_bit_or   = requires { std::declval<T>() | std::declval<U>(); };
template<typename T, typename U> concept can_bit_and  = requires { std::declval<T>() & std::declval<U>(); };
template<typename T, typename U> concept can_bit_xor  = requires { std::declval<T>() ^ std::declval<U>(); };

template<typename T>
concept can_bit_shift = requires {
  std::declval<T>() << std::declval<int>();
  std::declval<T>() >> std::declval<int>();
};

TEST_CASE("arithmetic")
{
  using wrap_int = wrapper::wrap<int, struct id, wrapper::ops::all_arithmetic>;
  static_assert(can_add<wrap_int, wrap_int>);
  static_assert(can_subtract<wrap_int, wrap_int>);
  static_assert(can_divide<wrap_int, wrap_int>);
  static_assert(can_multiply<wrap_int, wrap_int>);
  static_assert(can_modulo<wrap_int, wrap_int>);
  static_assert(!can_bit_or<wrap_int, wrap_int>);
  static_assert(!can_bit_and<wrap_int, wrap_int>);
  static_assert(!can_bit_xor<wrap_int, wrap_int>);
  static_assert(!can_bit_shift<wrap_int>);

  auto x = 5;
  auto y = 2;
  auto wx = wrap_int{ x };
  auto wy = wrap_int{ y };

  CHECK((wx + wy).get_underlying() == (x + y));
  CHECK((wx * wy).get_underlying() == (x * y));
  CHECK((wx - wy).get_underlying() == (x - y));
  CHECK((wx / wy).get_underlying() == (x / y));
  CHECK((wx % wy).get_underlying() == (x % y));

  CHECK((wx += wy).get_underlying() == (x += y));
  CHECK((wx *= wy).get_underlying() == (x *= y));
  CHECK((wx -= wy).get_underlying() == (x -= y));
  CHECK((wx /= wy).get_underlying() == (x /= y));
  CHECK((wx %= wy).get_underlying() == (x %= y));

  CHECK((wx++).get_underlying() == x++);
  CHECK((wx).get_underlying() == x);
  CHECK((++wx).get_underlying() == ++x);
  CHECK((wx).get_underlying() == x);

  CHECK((wy--).get_underlying() == y--);
  CHECK((wy).get_underlying() == y);
  CHECK((--wy).get_underlying() == --y);
  CHECK((wy).get_underlying() == y);
}

TEST_CASE("bitwise")
{
  using wrap_bitmap = wrapper::wrap<std::uint8_t, struct id, wrapper::ops::all_bitwise>;
  static_assert(!can_add<wrap_bitmap, wrap_bitmap>);
  static_assert(!can_subtract<wrap_bitmap, wrap_bitmap>);
  static_assert(!can_divide<wrap_bitmap, wrap_bitmap>);
  static_assert(!can_multiply<wrap_bitmap, wrap_bitmap>);
  static_assert(!can_modulo<wrap_bitmap, wrap_bitmap>);
  static_assert(can_bit_or<wrap_bitmap, wrap_bitmap>);
  static_assert(can_bit_and<wrap_bitmap, wrap_bitmap>);
  static_assert(can_bit_xor<wrap_bitmap, wrap_bitmap>);
  static_assert(can_bit_shift<wrap_bitmap>);

  auto x = std::uint8_t{ 0b0000'1111 };
  auto y = std::uint8_t{ 0b0011'1100 };
  auto wx = wrap_bitmap{ x };
  auto wy = wrap_bitmap{ y };
  auto shift = 2;

  CHECK((wx | wy).get_underlying() == (x | y));
  CHECK((wx & wy).get_underlying() == (x & y));
  CHECK((wx ^ wy).get_underlying() == (x ^ y));
  CHECK((wx << shift).get_underlying() == (x << shift));
  CHECK((wy >> shift).get_underlying() == (y >> shift));
  CHECK((~wx).get_underlying() == std::uint8_t{ 0b1111'0000 });

  CHECK((wx |= wy).get_underlying() == (x |= y));
  CHECK((wx &= wy).get_underlying() == (x &= y));
  CHECK((wx ^= wy).get_underlying() == (x ^= y));
  CHECK((wx <<= shift).get_underlying() == (x <<= shift));
  CHECK((wy >>= shift).get_underlying() == (y >>= shift));
}

TEST_CASE("conversion")
{
  using wrap_boolable_int = wrapper::wrap<int, struct id, wrapper::ops::conversion_to<bool>>;
  using wrap_nonboolable_int = wrapper::wrap<int, struct id>;

  // convertible_to -> implicit conversion
  // constructible_from -> explicit conversion
  static_assert(!std::convertible_to<wrap_boolable_int, bool>);
  static_assert(std::constructible_from<bool, wrap_boolable_int>);
  static_assert(!std::convertible_to<wrap_nonboolable_int, bool>);
  static_assert(!std::constructible_from<bool, wrap_nonboolable_int>);

  auto wx = wrap_boolable_int{ 1 };
  auto wy = wrap_boolable_int{ 0 };

  CHECK((wx || false) == true);
  CHECK((wy || false) == false);
  CHECK((wx || wy) == true);
  CHECK((wx && true) == true);
  CHECK((wy && true) == false);
  CHECK((wx && wy) == false);
}

TEST_CASE("operability")
{
  using wrap_int_1 = wrapper::wrap<int, struct id1, wrapper::ops::addition, wrapper::ops::addition_with<int>>;
  using wrap_int_2 = wrapper::wrap<int, struct id2, wrapper::ops::addition, wrapper::ops::addition_with<int>>;

  static_assert(can_add<wrap_int_1, int>);
  static_assert(can_add<wrap_int_1, wrap_int_1>);
  static_assert(!can_add<wrap_int_1, wrap_int_2>);

  static_assert(can_add<wrap_int_2, int>);
  static_assert(can_add<wrap_int_2, wrap_int_2>);
  static_assert(!can_add<wrap_int_2, wrap_int_1>);
}
