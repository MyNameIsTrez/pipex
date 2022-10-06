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

#include <stdio.h> // TODO: REMOVE THIS

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fds[2];
	pid_t	cpid;
	int		infile_fd;
	int		outfile_fd;

	(void)argc;
	(void)argv;

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	(void)infile_fd;
	(void)outfile_fd;

	if (cpid == 0)
	{
		close(pipe_fds[PIPE_READ_INDEX]);

		infile_fd = open("infile", O_RDONLY);
		dup2(infile_fd, STDIN_FILENO);
		dup2(pipe_fds[PIPE_WRITE_INDEX], STDOUT_FILENO);

		fprintf(stderr, "Executing 'wc -l'\n");

		sleep(2);

		execve("/usr/bin/wc", (char *[]){"/usr/bin/wc", "-l", NULL}, envp);

		// (void)envp;
		// printf("foo\n");
	}
	else
	{
		close(pipe_fds[PIPE_WRITE_INDEX]);

		fprintf(stderr, "Parent waiting\n");
		wait(NULL);
		fprintf(stderr, "Parent stopped waiting\n");

		dup2(pipe_fds[PIPE_READ_INDEX], STDIN_FILENO);
		outfile_fd = open("outfile", O_CREAT | O_WRONLY, 0644);
		dup2(outfile_fd, STDOUT_FILENO);

		char	buf;
		(void)outfile_fd;
		while (read(pipe_fds[PIPE_READ_INDEX], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);
			// write(STDERR_FILENO, &buf, 1);

		printf("xd\n");
		// execve("/usr/bin/wc", (char *[]){"/usr/bin/wc", "-l", NULL}, envp);
	}
}
