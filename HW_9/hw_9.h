#include <iostream>
#include <list>
#include <cstddef>

template <typename T>
class FreeListAllocator {
public:
    using value_type = T;

    FreeListAllocator() noexcept : buffer(nullptr), size(0) {}

    FreeListAllocator(T* buf, std::size_t s) noexcept : buffer(buf), size(s) {
        for (std::size_t i = 0; i < size; ++i) {
            freeList.push_back(buffer + i);
        }
    }

    template <typename U>
    FreeListAllocator(const FreeListAllocator<U>& other) noexcept : buffer(other.buffer), size(other.size) {}

    T* allocate(std::size_t n) {
        if (freeList.size() < n)
            throw std::bad_alloc();

        T* result = freeList.front();
        freeList.pop_front();
        return result;
    }

    void deallocate(T* p, std::size_t n) noexcept {
        for (std::size_t i = 0; i < n; ++i) {
            freeList.push_back(p + i);
        }
    }

private:
    T* buffer;
    std::size_t size;
    std::list<T*> freeList;
};

