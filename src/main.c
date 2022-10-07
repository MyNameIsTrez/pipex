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

// int	main(t_i32 argc, char *argv[], char *envp[])
// {
// 	if (argc != 5)
// 		return (EXIT_FAILURE);
// 	if (pipex_run((size_t)argc, argv, envp) != OK)
// 	{
// 		pipex_print_error();
// 		ft_free_allocations();
// 		return (EXIT_FAILURE);
// 	}
// 	ft_free_allocations();
// 	return (EXIT_SUCCESS);
// }

static void	perror_free_allocations_exit(char *msg)
{
	if (msg == NULL)
		perror("pipex");
	else
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(msg);
	}
	ft_free_allocations();
	exit(EXIT_FAILURE);
}

#include <stdio.h> // TODO: REMOVE THIS

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fds[2];
	pid_t	child_pid_1;
	int		infile_fd;
	pid_t	child_pid_2;
	int		outfile_fd;

	(void)argv;

	if (argc != 5)
	{
		// TODO: Is it supposed to print this as error?
		ft_putendl_fd("pipex: Wrong argument count", STDERR_FILENO);
		ft_free_allocations();
		exit(EXIT_FAILURE);
	}

	if (pipe(pipe_fds) == -1)
		perror_free_allocations_exit("pipe");

	child_pid_1 = fork();
	if (child_pid_1 == -1)
		perror_free_allocations_exit("fork 1");

	if (child_pid_1 == 0)
	{
		infile_fd = open("infile", O_RDONLY);
		dup2(infile_fd, STDIN_FILENO);

		dup2(pipe_fds[PIPE_WRITE_INDEX], STDOUT_FILENO);

		fprintf(stderr, "child 1\n");
		sleep(1);
		fprintf(stderr, "execve 1\n");

		execve("/usr/bin/wc", (char *[]){"/usr/bin/wc", "-l", NULL}, envp);
		perror("execve 1");
	}
	else
	{
		// TODO: Why do I need this? See the other TODO below
		close(pipe_fds[PIPE_WRITE_INDEX]);

		fprintf(stderr, "before wait 1\n");
		wait(NULL);
		fprintf(stderr, "after wait 1\n");

		child_pid_2 = fork();
		if (child_pid_2 == -1)
			perror_free_allocations_exit("fork 2");

		if (child_pid_2 == 0)
		{
			dup2(pipe_fds[PIPE_READ_INDEX], STDIN_FILENO);

			outfile_fd = open("outfile", O_CREAT | O_WRONLY, 0644);
			dup2(outfile_fd, STDOUT_FILENO);

			fprintf(stderr, "child 2\n");
			sleep(1);
			fprintf(stderr, "execve 2\n");

			// TODO: Why does this line cause the wait() below to hang? Also see the other TODO above
			execve("/usr/bin/wc", (char *[]){"/usr/bin/wc", "-l", NULL}, envp);
			perror("execve 2");
		}
		else
		{
			fprintf(stderr, "before wait 2\n");
			wait(NULL);
			fprintf(stderr, "after wait 2\n");
		}
	}

	ft_free_allocations();
	return (EXIT_SUCCESS);
}
