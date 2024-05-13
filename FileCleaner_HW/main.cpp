#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
        return 1;
    }
    
    int fileDescriptor = open(argv[1], O_WRONLY | O_TRUNC);
    if (fileDescriptor == -1) {
        std::cerr << "Error: Unable to open the file" << std::endl;
        return 1;
    }
    
    struct stat fileStat;
    if (fstat(fileDescriptor, &fileStat) == -1) {
        std::cerr << "Error: Unable to get file information" << std::endl;
        close(fileDescriptor);
        return 1;
    }

    if (write(fileDescriptor, "", 0) == -1) {
        std::cerr << "Error: Unable to clear the file" << std::endl;
        close(fileDescriptor);
        return 1;
    }
    
    close(fileDescriptor);
    
    std::cout << "File '" << argv[1] << "' has been cleared successfully." << std::endl;
    
    return 0;
}
