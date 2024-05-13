#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        std::cerr << "Error calling fork()" << std::endl;
        exit(1);
    } else if (pid == 0) {
        char *args[] = {(char*)"ls", (char*)"-al", (char*)"/", NULL};
        execvp(args[0], args);
        std::cerr << "Error calling execvp()" << std::endl;
        exit(1);
    } else {
        waitpid(pid, &status, 0);
    }

    return 0;
}

