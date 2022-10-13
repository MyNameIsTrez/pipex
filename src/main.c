/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 14:52:44 by sbos          #+#    #+#                 */
/*   Updated: 2022/09/28 14:52:44 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_1(int pipe_fds[2], char *argv[], char *envp[])
{
	int		infile_fd;

	close(pipe_fds[PIPE_READ_INDEX]);
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		strerror_free_allocs_exit_failure(argv[1]);
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		strerror_free_allocs_exit_failure("dup2");
	if (dup2(pipe_fds[PIPE_WRITE_INDEX], STDOUT_FILENO) == -1)
		strerror_free_allocs_exit_failure("dup2");
	run_cmd(2, argv, envp);
}

static void	child_2(int pipe_fds[2], char *argv[], char *envp[])
{
	int		outfile_fd;

	if (dup2(pipe_fds[PIPE_READ_INDEX], STDIN_FILENO) == -1)
		strerror_free_allocs_exit_failure("dup2");
	outfile_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile_fd == -1)
		strerror_free_allocs_exit_failure(argv[4]);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		strerror_free_allocs_exit_failure("dup2");
	run_cmd(3, argv, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fds[2];
	pid_t	child_pid_1;
	pid_t	child_pid_2;
	int		wstatus_child_2;

	if (argc != 5)
		print_free_allocs_exit(NULL, "Wrong argument count", EXIT_FAILURE);
	if (pipe(pipe_fds) == -1)
		strerror_free_allocs_exit_failure("pipe");
	child_pid_1 = fork();
	if (child_pid_1 == -1)
		strerror_free_allocs_exit_failure("fork");
	if (child_pid_1 == 0)
		child_1(pipe_fds, argv, envp);
	close(pipe_fds[PIPE_WRITE_INDEX]);
	child_pid_2 = fork();
	if (child_pid_2 == -1)
		strerror_free_allocs_exit_failure("fork");
	if (child_pid_2 == 0)
		child_2(pipe_fds, argv, envp);
	close(pipe_fds[PIPE_READ_INDEX]);
	waitpid(child_pid_2, &wstatus_child_2, 0);
	waitpid(child_pid_1, NULL, 0);
	ft_free_allocations();
	return (WEXITSTATUS(wstatus_child_2));
}
