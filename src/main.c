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

static char	*get_env_value(char *name, char *envp[])
{
	size_t	name_len;
	size_t	i;

	name_len = ft_strlen(name);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

static char	**get_env_subvalues(char *env_value)
{
	return (ft_split(env_value, ':'));
}

static char	*get_path(char *path_directory, char *cmd_path)
{
	size_t	path_len;
	char	*path;

	path_len = ft_strlen(path_directory) + 1 + ft_strlen(cmd_path) + 1;
	path = ft_malloc(path_len, sizeof(char));
	if (path == NULL)
		return (NULL);
	path[0] = '\0';
	ft_strlcat(path, path_directory, path_len);
	ft_strlcat(path, "/", path_len);
	ft_strlcat(path, cmd_path, path_len);
	return (path);
}

static bool	accessible(char *path)
{
	return (access(path, F_OK | X_OK) == 0);
}

static void	exec(char *path, char *cmd_argv[], char *envp[])
{
	execve(path, cmd_argv, envp);
	// TODO: Print something and exit here!
}

static void	free_allocations_exit(int status)
{
	ft_free_allocations();
	// fprintf(stderr, "errno: %d\n", errno);
	exit(status);
}

static void	run_cmd_if_accessible_relative(char *cmd_passed, char *cmd_argv[], char *envp[])
{
	char	*path;

	path = get_path(".", cmd_passed);
	if (!accessible(path))
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(cmd_passed, STDERR_FILENO); // TODO: Should this print the path instead?
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		free_allocations_exit(126);
	}
	exec(path, cmd_argv, envp);
}

static t_status	run_cmd_if_accessible_path_subvalues(char *cmd_path, char **path_subvalues, char *cmd_argv[], char *envp[])
{
	size_t	i;
	char	*path;

	i = 0;
	while (path_subvalues[i] != NULL)
	{
		// fprintf(stderr, "i: %zu\n", i);
		path = get_path(path_subvalues[i], cmd_path);
		if (path == NULL)
			return (ERROR);
		if (accessible(path))
			exec(path, cmd_argv, envp);
		i++;
	}
	return (ERROR);
}

// #include <errno.h> // TODO: REMOVE

static void	perror_free_allocations_exit(char *msg)
{
	if (msg == NULL)
		perror("pipex");
	else
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(msg);
	}
	free_allocations_exit(EXIT_FAILURE);
}

void	foo(size_t cmd_index, char *argv[], char *envp[])
{
	char	**cmd_parts;
	char	*cmd_passed;
	char	**cmd_argv;
	cmd_parts = ft_split(argv[cmd_index], ' ');
	cmd_passed = cmd_parts[0];
	cmd_argv = cmd_parts;

	if (ft_chr_in_str('/', cmd_passed))
	{
		// fprintf(stderr, "slash\n");
		run_cmd_if_accessible_relative(cmd_passed, cmd_argv, envp);
	}
	else
	{
		char	*path_value;
		char	**path_subvalues;
		path_value = get_env_value("PATH", envp);
		// fprintf(stderr, "%s\n", path_value);
		path_subvalues = get_env_subvalues(path_value);
		// fprintf(stderr, "%s\n", path_subvalues[1]);

		if (path_subvalues == NULL || run_cmd_if_accessible_path_subvalues(cmd_passed, path_subvalues, cmd_argv, envp) == ERROR)
		{
			ft_putstr_fd("pipex: ", STDERR_FILENO);
			ft_putstr_fd(cmd_passed, STDERR_FILENO); // TODO: Should this print the path instead?
			ft_putendl_fd(": command not found", STDERR_FILENO);
			free_allocations_exit(127);
		}
	}
}

#include <stdio.h> // TODO: REMOVE THIS

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fds[2];
	pid_t	child_pid_1;
	int		infile_fd;
	pid_t	child_pid_2;
	int		outfile_fd;
	int		wstatus_2;

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
		close(pipe_fds[PIPE_READ_INDEX]);

		infile_fd = open(argv[1], O_RDONLY);
		if (infile_fd == -1)
			perror_free_allocations_exit(argv[1]);
		if (dup2(infile_fd, STDIN_FILENO) == -1)
			perror_free_allocations_exit("dup2");

		if (dup2(pipe_fds[PIPE_WRITE_INDEX], STDOUT_FILENO) == -1)
			perror_free_allocations_exit("dup2");

		// fprintf(stderr, "child 1\n");
		// sleep(1);
		// fprintf(stderr, "execve 1\n");

		foo(2, argv, envp);
	}

	close(pipe_fds[PIPE_WRITE_INDEX]);

	child_pid_2 = fork();
	// child_pid_2 = -1;
	if (child_pid_2 == -1)
		perror_free_allocations_exit("fork 2");

	if (child_pid_2 == 0)
	{
		dup2(pipe_fds[PIPE_READ_INDEX], STDIN_FILENO);

		outfile_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile_fd == -1)
			perror_free_allocations_exit(argv[4]); // TODO: Don't exit immediately?
		dup2(outfile_fd, STDOUT_FILENO);

		// fprintf(stderr, "child 2\n");
		// sleep(1);
		// fprintf(stderr, "execve 2\n");

		foo(3, argv, envp);
	}

	close(pipe_fds[PIPE_READ_INDEX]);

	// fprintf(stderr, "before wait 2\n");
	pid_t x = waitpid(child_pid_2, &wstatus_2, 0); // wait() can be used here, but means it can release child_pid_1 here
	(void)x;
	(void)wstatus_2;
	// fprintf(stderr, "x: %d\n", x);
	// fprintf(stderr, "wstatus 2: %d\n", wstatus_2);
	// fprintf(stderr, "WIFEXITED: %d\n", WIFEXITED(wstatus_2));
	// fprintf(stderr, "WIFSIGNALED: %d\n", WIFSIGNALED(wstatus_2));
	// fprintf(stderr, "WIFSTOPPED: %d\n", WIFSTOPPED(wstatus_2));
	// fprintf(stderr, "WEXITSTATUS: %d\n", WEXITSTATUS(wstatus_2));
	// fprintf(stderr, "WTERMSIG: %d\n", WTERMSIG(wstatus_2));
	// fprintf(stderr, "WCOREDUMP: %d\n", WCOREDUMP(wstatus_2));
	// fprintf(stderr, "WSTOPSIG: %d\n", WSTOPSIG(wstatus_2));
	// wait(NULL);
	// fprintf(stderr, "after wait 2\n");
	// }

	// fprintf(stderr, "before wait 1\n");
	waitpid(child_pid_1, NULL, 0);
	// wait(NULL);
	// fprintf(stderr, "after wait 1\n");

	ft_free_allocations();
	// fprintf(stderr, "wstatus_2:%d\n", wstatus_2);
	return (WEXITSTATUS(wstatus_2));
}
