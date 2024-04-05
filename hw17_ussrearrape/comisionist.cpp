//std
#include <iostream>
//linux API
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

bool isFound = false;

void shvayn_shpion_find(int sig, siginfo_t *info, void *context);

int main()
{
	int fd = open("postman.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	if (fd == -1)
	{
		std::cout << "Failed to open postman.txt file!";
		exit(EXIT_FAILURE);
	}

	char buffer[BUFSIZ];
	ssize_t bytesRead;
	int numbers[5952];
	int num_count = 0;

	while ((bytesRead = read(fd, buffer, BUFSIZ)) > 0) {
        char *start = buffer;
        for (ssize_t i = 0; i < bytesRead; i++) {
            if (buffer[i] == ' ') {
                buffer[i] = '\0';
                numbers[num_count++] = atoi(start);
                start = buffer + i + 1;
            }
        }
    }

	struct sigaction sa;
	sa.sa_sigaction = shvayn_shpion_find;
	sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGILL, &sa, NULL) == -1) {
        std::cerr << "Unable to register signal handler";
        exit(EXIT_FAILURE);
    }

	for (int i = 0; i < 5952; i++)
	{
		kill(numbers[i], SIGCONT);
	}

	while(1)
	{
		if (isFound)
			break;
		std::cout << "Investigation underway...\n";
		sleep(1);
	}

	return 0;
}

void shvayn_shpion_find(int sig, siginfo_t *info, void *context)
{
	pid_t senderPID = info->si_pid;

	std::cout << "Shvine was been found with PID: " << senderPID;
	isFound = true;
}