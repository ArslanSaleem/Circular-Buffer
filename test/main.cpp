#include <iostream>
#include <CircularBuffer.hpp>

template <class T, int N>
void display(CircularBuffer<T, N> cb)
{
    std::copy(cb.begin(), cb.end(), std::ostream_iterator<T>(std::cout, ", "));
    std::cout << std::endl;
}

int main()
{
    CircularBuffer<float, 4> cb;
    cb.push_back(1.f);
    cb.push_back(2.f);
    cb.push_back(3.f);
    cb.push_back(4.f);
    cb.push_back(5.f);
    display(cb);
    cb.pop_front();
    display(cb);
    cb.pop_back();
    display(cb);
    cb.push_back(1.f);
    cb.push_back(2.f);
    display(cb);
    cb.push_front(10.f);
    display(cb);
}
