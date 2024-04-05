// std
#include <iostream>
#include <random>
// linux API
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void shvaynish_handler(int sig, siginfo_t *info, void *context);

int main()
{
	int fd = open("postman.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	if (fd == -1)
	{
		std::cout << "Diese blöde Datei will nicht geöffnet werden!!\n";
		exit(EXIT_FAILURE);
	}	
	
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> shvayne(0, 1488);
	std::uniform_int_distribution<> dis(1488, 14888);

	int shvayne_number = shvayne(gen);

	for (int i = 0; i < 1488 + 1; i++)
	{
		if (i == shvayne_number)
		{
			const char* shvaynePID = std::string(std::to_string(getpid()) + " ").c_str();
			write(fd, shvaynePID, strlen(shvaynePID));
			continue;
		}
		const char* currentPID = std::string(std::to_string(dis(gen)) + " ").c_str();
		write(fd, currentPID, strlen(currentPID));
	}

	close(fd);

	struct sigaction sa;
	sa.sa_sigaction = shvaynish_handler;
	sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGCONT, &sa, NULL) == -1) {
        std::cerr << "Unable to register signal handler";
        exit(EXIT_FAILURE);
    }

	while (1)
	{
		sleep(50);
		continue;
	}

	return 0;
}

void shvaynish_handler(int sig, siginfo_t *info, void *context)
{
	pid_t senderPID = info->si_pid;

    if(senderPID != 0) {
        if(kill(senderPID, SIGILL) == -1) {
            std::cerr << "Error sending SIGILL\n";
            exit(EXIT_FAILURE);
        }
    }
}
