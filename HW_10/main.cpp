int main() 
    {
    DirectoryIterator it("/home/tor/Desktop/linux2024-25/HW_10");
    while (it.hasNext()) 
    {
        std::cout << it.next() << std::endl;
    }

    return 0;
}
