int main() {
    const std::size_t size = 10;
    int buffer[size];

    FreeListAllocator<int> allocator(buffer, size);

    int* p = allocator.allocate(1);
    *p = 42;

    std::cout << "Allocated integer: " << *p << std::endl;

    allocator.deallocate(p, 1);

    return 0;
}
