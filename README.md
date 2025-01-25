# wrapper-type

A c++23 type wrapper for strong typing with flexible operator enabling.

Uses [c++20 modules](https://en.cppreference.com/w/cpp/language/modules) and the [c++23 std module](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2465r3.pdf).

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

## Requirements

Requires compiler supporting the [c++23 standard module](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2465r3.pdf) (i.e. `import std`).

A [nix flake / shell](https://nix.dev/tutorials/first-steps/declarative-shell.html) is provided which includes a cmake + ninja + clang (w/ libc++) toolchain that supports the c++23 std module.
