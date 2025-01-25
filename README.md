# wrapper-type

A c++23 type wrapper for strong typing with flexible operator enabling.

Uses [c++20 modules](https://en.cppreference.com/w/cpp/language/modules) and the [c++23 std module](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2465r3.pdf).

## Requirements

Requires compiler supporting the [c++23 standard module](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2465r3.pdf) (i.e. `import std`).

A [nix flake / shell](https://nix.dev/tutorials/first-steps/declarative-shell.html) is provided which includes a cmake + ninja + clang (w/ libc++) toolchain that supports the c++23 std module.

## Example

Creating a strong type for a bit mask. Only enable bitwise operations.

```cpp
import std;
import wrapper;

int main() {

  using bitmask = wrapper::wrap<std::uint8_t, struct id, wrapper::ops::all_bitwise>;

  auto x = bitmask{0b0000'1111};
  auto y = std::uint8_t{0b0000'1111};

  x & (x << 2)    // okay
  // x & (y << 2) // error (invalid operands)   -- strong typing
  // x + x        // error (undefined operator) -- flexible operator enabling

  return 0;
};
```

For more examples, see the [tests](/tests/wrapper_tests.cpp);

## Why

It is often useful to create type aliases to write more expressive code with clear intent. However, type alias are just alises and do not provide any additional type safety via strong typing:

```cpp
import std;

auto main() -> int {
  using bitmask = std::uint8_t;

  auto my_mask      = bitmask{0b0000'1111};
  auto not_a_mask   = std::uint8_t{0b0000'1111};
  auto what_is_this = my_mask & (not_a_mask << 2);

  return 0;
}
```

In order to achive strong typing, a type must be wrapped in a struct/class, but this creates the tedious task of overloading many operators:

```cpp
import std;

struct bitmask {
  std::uint8_t _mask{0b0000'0000};

  bitmask&
  operator|=(bitmask& rhs)
  {
    _mask |= rhs._mask;
    return *this;
  }

  friend bitmask
  operator|(bitmask const& lhs, bitmask const& rhs)
  {
    auto tmp = lhs;
    tmp |= rhs;
    return tmp;
  }

  // all the other operators ...
};
```

A solution is needed for strong type wrapping while also providing flexible operator overloads to avoid excessive boilerplate code.

## How

This library uses the [Curiously Recurring Template Pattern (CRTP)](https://en.cppreference.com/w/cpp/language/crtp) and [Variadic Templates](https://en.cppreference.com/w/cpp/language/pack) to provide flexible operator enabling.

The `base` class is the `op` which defines the operators/overloads for its template paremeter -- the `wrap` / `derived` class:

```cpp
// this is our "base" / "op"
template<typename derived>
struct add
{
  // friend because non-member needed
  friend derived&
  operator+=(derived& lhs, derived const& rhs)
  {
    lhs._val += rhs._val;
    return lhs;
  }

  friend derived
  operator+(derived const& lhs, derived const& rhs)
  {
    auto tmp = lhs;
    tmp += rhs;
    return tmp;
  }
};

// this is our "derived" / "wrap"
template<typename wrapped_type, typename wrap_op>
struct wrap : public wrap_ops<wrap<wrapped_type, wrap_op>>
{
  wrapped_type _val;
  // ...
};
```

By deriving the `op`, non-member operator overloads are instantiated / enabled. To make this more flexible, just add a [variadic template](https://en.cppreference.com/w/cpp/language/pack) to allow picking and choosing which operators are enabled:

```cpp
struct add      { ... };
struct subtract { ... };
// ...

template<typename wrapped_type, typename... wrap_ops>
struct wrap : public wrap_ops<wrap<wrapped_type, wrap_ops...>>...
{
  // ...
};
```

One last detail is that this does not actually enfore strong typing because the templated operators are specialized only by `wrap` which is in turn only specialized by the underlying type and `ops`. Therefore, `wraps` can still operate with one another as long as the underlying is the same:

```cpp

int main() {
  using bitmask      = wrap<std::uint8_t, bit_or>;
  using int_w_bit_or = wrap<std::uint8_t, bit_or>;

  auto my_bitmask       = bitmask{0b0000'1111};
  auto my_bitorable_int = int_w_bit_or{0b1111'0000};

  my_bitmask | my_bitorable_int; // okay -- but shouldn't be allowed

  return 0;
}

```

To fix this, just add a dummy template parameter to make the specialization unique:

```cpp
template<typename wrapped_type, typename wrap_id, typename... wrap_ops>
struct wrap : public wrap_ops<wrap<wrapped_type, wrap_id, wrap_ops...>>...
{
  // ...
};
```
