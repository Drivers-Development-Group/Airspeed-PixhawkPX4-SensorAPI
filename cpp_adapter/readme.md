# MS4525DO C++ Adapter

A thin C++ wrapper around the C driver. The `MS4525DO` class forwards each call
to its C counterpart, providing an object-oriented interface without changing
the underlying behaviour. Use this adapter when integrating the driver into a
C++ codebase; otherwise the C API in `include/ms4525do.h` is sufficient.

## Files

| Path                            | Description                          |
| ------------------------------- | ------------------------------------ |
| `cpp_adapter/include/ms4525do.hpp` | `MS4525DO` class declaration.     |
| `cpp_adapter/src/ms4525do.cpp`     | `MS4525DO` class implementation.  |

## Building

Register both the C core and the C++ adapter in your component
`CMakeLists.txt`:

```cmake
idf_component_register(
    SRCS
        "src/ms4525do.c"
        "cpp_adapter/src/ms4525do.cpp"
    INCLUDE_DIRS
        "include"
        "cpp_adapter/include"
)
```

## Usage

See [`../example/example.cpp`](../example/example.cpp) for a complete example,
and the [top-level README](../README.md) for the full API reference.