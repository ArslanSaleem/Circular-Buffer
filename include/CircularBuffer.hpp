#include <iterator>
#include <cstddef>

template <class size_type, size_type N>
struct CircularIndexer
{
    inline constexpr static size_type increment(size_type value) noexcept
    {
        return (value + 1) % N;
    }

    inline constexpr static size_type decrement(size_type value) noexcept
    {
        return (value + N - 1) % N;
    }
};

template <class T, size_t N>
struct CircularIterator : public std::iterator_traits<T *>
{
    CircularIterator(T *container_, size_t head_, size_t offset_)
        : _buffer(container_), head(head_), offset(offset_) {}

    T &operator*() const { return _buffer[(head + offset) % N]; }
    T &operator->() const { return &_buffer[(head + offset) % N]; }
    bool operator!=(const CircularIterator &other) const noexcept { return !(*this == other); }
    bool operator==(const CircularIterator &other) const noexcept { return (other._buffer == this->_buffer && other.offset == this->offset); }
    CircularIterator &operator++() noexcept
    {
        ++offset;
        return *this;
    }
    CircularIterator operator++(int) noexcept
    {
        CircularIterator clone(*this);
        ++offset;
        return clone;
    }
    CircularIterator &operator--() noexcept
    {
        --offset;
        return *this;
    }
    CircularIterator &operator--(int) noexcept
    {
        CircularIterator clone(*this);
        --offset;
        return clone;
    }

private:
    T *_buffer;
    size_t offset{0}, head{0};
};

template <class T, int N>
class CircularBuffer
{
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator = CircularIterator<T, N>;
    using const_iterator = CircularIterator<const T, N>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using indexer = CircularIndexer<size_type, N>;

    CircularBuffer() = default;
    CircularBuffer(const CircularBuffer &other)
        : head(0), tail(0), size(0), _buffer()
    {
        copy_buffer(other);
    }

    CircularBuffer(std::initializer_list<T> values)
    {
        for (auto val : values)
        {
            push_back(std::move(val));
        }
    }

    CircularBuffer &operator=(const CircularBuffer &other)
    {
        clear();
        copy_buffer(other);
        return *this;
    }

    inline void clear()
    {
        head = 0;
        tail = 0;
        size = 0;
    }

    inline void copy_buffer(const CircularBuffer &other)
    {
        const_iterator first = other.cbegin();
        const const_iterator last = other.cend();

        for (; first != last; ++first)
            push_back(*first);
    }

    T front() const { return size > 0 ? _buffer[head] : T(); }
    T back() const { return size > 0 ? _buffer[indexer::decrement(tail)] : T(); }
    inline constexpr bool full() const noexcept { return size == N; }
    inline constexpr bool empty() const noexcept { return size == 0; }

    inline constexpr T pop_front()
    {
        T val = front();
        head = indexer::increment(head);
        size = size > 0 ? size - 1 : 0;
        return val;
    }

    inline constexpr T pop_back()
    {
        T val = back();
        tail = indexer::decrement(tail);
        size = size > 0 ? size - 1 : 0;
        return val;
    }

    inline constexpr void push_back(const T &val)
    {
        _buffer[tail] = val;
        if (size < N)
        {
            size++;
        }
        else
        {
            head = indexer::increment(head);
        }
        tail = (head + size) % N;
    }

    inline constexpr void push_back(const T &&val)
    {
        _buffer[tail] = val;
        if (size < N)
        {
            size++;
        }
        else
        {
            head = indexer::increment(head);
        }
        tail = (head + size) % N;
    }

    inline constexpr void push_front(const T &val)
    {
        if (full())
        {
            tail = indexer::decrement(tail);
            head = indexer::decrement(head);
            _buffer[tail] = val;
        }
        else
        {
            head = indexer::decrement(head);
            _buffer[head] = val;
        }
    }

    inline constexpr void push_front(const T &&val)
    {
        if (full())
        {
            tail = indexer::decrement(tail);
            head = indexer::decrement(head);
            _buffer[tail] = val;
        }
        else
        {
            head = indexer::decrement(head);
            _buffer[head] = val;
        }
    }

    iterator begin() { return iterator(_buffer, head, 0); }
    iterator end() { return iterator(_buffer, head, size); }
    const_iterator cbegin() const { return const_iterator(_buffer, head, 0); }
    const_iterator cend() const { return const_iterator(_buffer, head, size); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }

    T &operator[](size_t index) { return _buffer[index]; }
    template <class T1, int N1>
    bool operator==(const CircularBuffer<T1, N1> &other) { return _buffer == other._buffer; }
    template <class T1, int N1>
    bool operator!=(const CircularBuffer<T1, N1> &other) { return (*this == other); }

private:
    T _buffer[N];
    size_type head{0}, size{0}, tail{0};
};