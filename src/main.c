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

static char	*get_path(char *path_subvalue, char *cmd1_path)
{
	size_t	path_len;
	char	*path;

	path_len = ft_strlen(path_subvalue) + 1 + ft_strlen(cmd1_path) + 1;
	path = ft_malloc(path_len, sizeof(char));
	if (path == NULL)
		return (NULL);
	path[0] = '\0';
	ft_strlcat(path, path_subvalue, path_len);
	ft_strlcat(path, "/", path_len);
	ft_strlcat(path, cmd1_path, path_len);
	return (path);
}

static bool	accessible(char *path)
{
	return (access(path, F_OK | X_OK) == 0);
}

static t_status	run_cmd_if_accessible(char *path, char *cmd_argv[], char *envp[])
{
	if (accessible(path))
	{
		// fprintf(stderr, "is accessible\n");
		if (execve(path, cmd_argv, envp) != -1)
		{
			// fprintf(stderr, "is OK\n");
			return (OK);
		}
	}
	// fprintf(stderr, "not accessible\n");
	return (ERROR);
}

static t_status	run_cmd_if_accessible_path_subvalues(char *cmd1_path, char **path_subvalues, char *cmd_argv[], char *envp[])
{
	size_t	i;
	char	*path;

	i = 0;
	while (path_subvalues[i] != NULL)
	{
		// fprintf(stderr, "i: %zu\n", i);
		path = get_path(path_subvalues[i], cmd1_path);
		if (path == NULL)
			return (ERROR);
		if (run_cmd_if_accessible(path, cmd_argv, envp) == OK)
			return (OK);
		i++;
	}
	return (ERROR);
}

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

		// execve("/usr/bin/wc", (char *[]){"/usr/bin/wc", "-l", NULL}, envp);

		char	**cmd1_parts;
		char	*cmd1_path;
		char	**cmd1_argv;
		cmd1_parts = ft_split(argv[2], ' ');
		cmd1_path = cmd1_parts[0];
		cmd1_argv = &cmd1_parts[1];

		char	*path_value;
		char	**path_subvalues;
		path_value = get_env_value("PATH", envp);
		// fprintf(stderr, "%s\n", path_value);
		path_subvalues = get_env_subvalues(path_value);
		// fprintf(stderr, "%s\n", path_subvalues[1]);

		if (ft_chr_in_str('/', cmd1_path))
		{
			// fprintf(stderr, "slash\n");
			if (run_cmd_if_accessible(cmd1_path, cmd1_argv, envp) != OK)
			{

			}
		}
		else if (path_subvalues != NULL)
		{
			// fprintf(stderr, "has subvalues\n");
			if (run_cmd_if_accessible_path_subvalues(cmd1_path, path_subvalues, cmd1_argv, envp) != OK)
			{
				// fprintf(stderr, "not OK\n");
			}
		}
		else
		{
			fprintf(stderr, "error\n");
			ft_putstr_fd("pipex: ", STDERR_FILENO);
			ft_putstr_fd(cmd1_path, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}

		// perror("execve 1");
	}
	else
	{
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
