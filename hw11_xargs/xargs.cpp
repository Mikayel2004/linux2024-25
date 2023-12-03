#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command>" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::vector<std::string> args;

    // Read arguments from standard input
    std::string argument;
    while (std::cin >> argument) {
        args.push_back(argument);
    }

    // Prepare arguments for command execution
    char* cmdArgs[args.size() + 2]; // +2 for command and NULL terminator
    cmdArgs[0] = const_cast<char*>(command.c_str());

    for (size_t i = 0; i < args.size(); ++i) {
        cmdArgs[i + 1] = const_cast<char*>(args[i].c_str());
    }
    cmdArgs[args.size() + 1] = NULL;

    // Execute the command with arguments
    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Error: Fork failed" << std::endl;
        return 1;
    } else if (pid == 0) {
        // Child process
        execvp(command.c_str(), cmdArgs);
        // If execvp fails, print an error
        std::cerr << "Error: Execution failed" << std::endl;
        return 1;
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
