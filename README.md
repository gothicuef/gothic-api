# Gothic API

Gothic API is a collection of ZenGine headers with memory addresses for use in [Union API](https://gitlab.com/union-framework/union-api) plugins. It contains separate headers for:

* Gothic I (`Gothic_I_Classic`)
* Gothic Sequel (`Gothic_I_Addon`)
* Gothic II (Classic) (`Gothic_II_Classic`)
* Gothic II Night of the Raven (`Gothic_II_Addon`)

## Documentation
Documentation is available on [Union Framework Docs](https://union-framework.gitlab.io/docs/gothic-api/).

## Usage

### Build
Gothic API is built using [CMake](https://cmake.org/) and requires C++17 or later to compile. The recommended way to build is to use [Visual Studio 2022](https://visualstudio.microsoft.com/vs/) with CMake support enabled.

### Including

To include Gothic API in your project, you need to get its source using git submodule or CMake's `FetchContent` module.

If you are using git submodule, run the following command in your project root:

```bash
git submodule add https://gitlab.com/union-framework/gothic-api.git
```
This will add Gothic API as a submodule in your project. You can then include it in your CMake project by adding the following lines to your `CMakeLists.txt`:

```cmake
add_subdirectory(union-api)
```

If you are using CMake's `FetchContent`, add the following lines to your `CMakeLists.txt`:

```cmake
include(FetchContent)
FetchContent_Declare(
    gothic-api
    GIT_REPOSITORY https://gitlab.com/union-framework/gothic-api.git
    GIT_TAG main
)
FetchContent_MakeAvailable(gothic-api)
```

### Linking
After including Gothic API, you can link it to your target. For example, if your target is `your_target`, you can add the following line to your `CMakeLists.txt`:

```cmake
target_link_libraries(your_target PRIVATE gothic_api)
```

## Support

Community-driven support is provided on [Gothic Modding Community Discord](https://discord.gg/mCpS5b5SUY).

If you have found a bug, please [create an issue](https://gitlab.com/union-framework/union-api/-/issues) with a detailed description and your environment.

## License

Gothic API is licensed under [BSD 3-Clause](https://gitlab.com/union-framework/gothic-api/-/blob/main/LICENSE).