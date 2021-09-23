#include <iostream>
#include <CircularBuffer.hpp>

template <class T, int N>
void display(const CircularBuffer<T, N> &cb)
{
    std::copy(cb.cbegin(), cb.cend(), std::ostream_iterator<T>(std::cout, ", "));
    std::cout << std::endl;
}

int main()
{
    // Initialize with member initialization list
    CircularBuffer<float, 4> cb{9.f, 6.f, 3.f};

    display(cb);
    cb.push_back(1.f);
    display(cb);
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

    // Check Copy constructor and equal operator
    CircularBuffer<float, 4> cb2 = cb;
    cb.push_front(11.f);
    display(cb2);
    cb2 = cb;
    display(cb2);
}
