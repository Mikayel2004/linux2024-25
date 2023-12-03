#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int do_command(const char* argv[]) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return -1;
    }
    else if (pid == 0) {
        // This is the child process
        execvp(argv[0], (char* const*)argv);
        // execvp only returns on error
        perror("execvp failed");
        return -1;
    }
    else {
        // This is the parent process
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid failed");
            return -1;
        }
        else if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        else {
            printf("child did not terminate normally\n");
            return -1;
        }
    }
}
