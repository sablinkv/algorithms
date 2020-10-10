**algorithms** is a C++17 header-only collections of sorting and searching algorithms library.

## Building the project

```bash
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=<install_path>
cmake --build . --target install --config Release
```

## Compiling and running unit tests

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Debug/Release
ctest -C Debug/Release
```

## Using free function of sorting and searching algorithms 

```cpp
#include <iostream>
#include <vector>
#include <algorithms/sort>
#include <algorithms/search>

int main() {
    std::vector<int> vc{ 7, 2, 1, 9, 8, 3, 0 };
    algorithms::quick_sort_hoare(vc.begin(), vc.end(), [](const auto& lhs, const auto& rhs) {
        return lhs < rhs; 
    });
    // Out -> 0 1 2 3 7 8 9
    std::copy(vc.cbegin(), vc.cend(), std::ostream_iterator<int>(std::cout, " "));

    auto found = algorithms::binary_search(vc.cbegin(), vc.cend(), 1, std::less<>());
    // Out -> 1
    std::cout << '\n' << (found != vc.cend() ? *found : "not found") << '\n';
    return 0;
}
```