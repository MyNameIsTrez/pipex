void	perror(const char *str); // Prints error and prepends it with str (if str is not NULL/NUL)

// int		dup(int from); // Duplicates the data at the filedes `from` to the first unused filedes and returns that filedes
int		dup2(int from, int to); // Copies the data at the filedes `from` to the filedes `to`

pid_t	wait(int *stat_loc); // Waits until any child process exits

int		execve(const char *path, char *const argv[], char *const envp[]); // Runs executable at path, replacing the current process
void	exit(int status); // Terminates its process
int		access(const char *path, int mode); // Returns whether the pipex process has the access rights defined in mode to path
pid_t	fork(void); // Creates a parellel universe of the process at this point
int		pipe(int pipe_fds[2]); // Allocates two file descriptors, where the data written to the WRITE end can be read from the READ end

/*
pipe(pipe_fds[2])
fork()

child:
	open(infile)
	dup2(infile_fd, STDIN_FILENO)
	dup2(pipe_fds[PIPE_WRITE_INDEX], STDOUT_FILENO)

	execve(cmd1)

parent:
	close(pipe_fds[PIPE_WRITE_INDEX])

	wait(NULL); // TODO: According to Marius this needs to happen after the child's/parent's execve?

	dup2(pipe_fds[PIPE_READ_INDEX], STDIN_FILENO)
	open(outfile)
	dup2(outfile_fd, STDOUT_FILENO)

	execve(cmd2)
*/
