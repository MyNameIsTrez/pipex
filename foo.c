#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

# define PIPE_READ_INDEX 0
# define PIPE_WRITE_INDEX 1

// int	main(int argc, char *argv[])
// {
// 	int pipe_fds[2];
// 	pid_t cpid;
// 	char buf;

// 	if (argc != 2) {
// 		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pipe(pipe_fds) == -1) {
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}

// 	cpid = fork();
// 	if (cpid == -1) {
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (cpid == 0) {
// 		close(pipe_fds[1]);

// 		while (read(pipe_fds[0], &buf, 1) > 0)
// 			write(STDOUT_FILENO, &buf, 1);

// 		write(STDOUT_FILENO, "\n", 1);
// 		close(pipe_fds[0]);
// 		_exit(EXIT_SUCCESS);
// 	} else {
// 		close(pipe_fds[0]);
// 		write(pipe_fds[1], argv[1], strlen(argv[1]));
// 		// close(pipe_fds[1]);
// 		// wait(NULL);
// 		// exit(EXIT_SUCCESS);
// 	}
// }
