# Circular-Buffer

[Cmake](https://img.shields.io/badge/cmake-3.21.1-green.svg)

A Header only libray for STL type Circular Buffer that support all the algorithms built for STL containers

## Usage
1. git clone https://github.com/ArslanSaleem/Circular-Buffer.git
2. cd Circular-Buffer
3. Make director build
4. cd build 
5. cmake ..
6. make 
7. ./test_circular_buffer

## Code Usage 
```
#include <CircularBuffer.hpp>

CircularBuffer<float, 4> cb{9.f, 6.f, 3.f};
cb.push_back(1.f);
cb.pop_front();
std::copy(cb.cbegin(), cb.cend(), std::ostream_iterator<T>(std::cout, ", "));
```

