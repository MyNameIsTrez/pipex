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

static void	perror_free_allocs_exit(char *prefix, char *msg, int status)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (prefix != NULL)
	{
		ft_putstr_fd(prefix, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	ft_free_allocations();
	exit(status);
}

static void	perror_free_allocs_exit_failure(char *prefix)
{
	perror_free_allocs_exit(prefix, strerror(errno), EXIT_FAILURE);
}

static void	exec(char *path, char *cmd_argv[], char *envp[])
{
	execve(path, cmd_argv, envp);
	perror_free_allocs_exit_failure("execve");
}

static void	run_cmd_with_slashes(char *path, char *cmd_argv[], char *envp[])
{
	if (access(path, F_OK) == -1)
		perror_free_allocs_exit(path, strerror(errno), 127);
	if (access(path, X_OK) == -1)
		perror_free_allocs_exit(path, strerror(errno), 126);
	exec(path, cmd_argv, envp);
}

static void	run_cmd_without_slashes(char *cmd_path, char **path_subvalues, char *cmd_argv[], char *envp[])
{
	size_t	i;
	char	*path;
	char	*first_existing_path;

	first_existing_path = NULL;
	i = 0;
	while (path_subvalues[i] != NULL)
	{
		path = get_path(path_subvalues[i], cmd_path);
		if (path == NULL)
			perror_free_allocs_exit_failure("get_path");
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
				exec(path, cmd_argv, envp);
			if (first_existing_path == NULL)
				first_existing_path = path;
		}
		i++;
	}
	if (first_existing_path == NULL)
		perror_free_allocs_exit(cmd_path, "command not found", 127);
	perror_free_allocs_exit(first_existing_path, strerror(EACCES), 126);
}

static void	run_cmd(size_t cmd_index, char *argv[], char *envp[])
{
	char	**cmd_argv;
	char	*cmd_passed;
	char	*path_value;
	char	**path_subvalues;

	cmd_argv = ft_split(argv[cmd_index], ' ');
	if (cmd_argv == NULL)
		perror_free_allocs_exit_failure("ft_split");
	cmd_passed = cmd_argv[0];
	if (ft_chr_in_str('/', cmd_passed))
		run_cmd_with_slashes(cmd_passed, cmd_argv, envp);
	else
	{
		path_value = get_env_value("PATH", envp);
		path_subvalues = ft_split(path_value, ':');

		if (path_subvalues == NULL)
			perror_free_allocs_exit(cmd_passed, "command not found", 127);

		run_cmd_without_slashes(cmd_passed, path_subvalues, cmd_argv, envp);
	}
}

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
		ft_putendl_fd("pipex: Wrong argument count", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	if (pipe(pipe_fds) == -1)
		perror_free_allocs_exit_failure("pipe");

	child_pid_1 = fork();
	if (child_pid_1 == -1)
		perror_free_allocs_exit_failure("fork");

	if (child_pid_1 == 0)
	{
		close(pipe_fds[PIPE_READ_INDEX]);

		infile_fd = open(argv[1], O_RDONLY);
		if (infile_fd == -1)
			perror_free_allocs_exit_failure(argv[1]);
		if (dup2(infile_fd, STDIN_FILENO) == -1)
			perror_free_allocs_exit_failure("dup2");

		if (dup2(pipe_fds[PIPE_WRITE_INDEX], STDOUT_FILENO) == -1)
			perror_free_allocs_exit_failure("dup2");

		run_cmd(2, argv, envp);
	}

	close(pipe_fds[PIPE_WRITE_INDEX]);

	child_pid_2 = fork();
	if (child_pid_2 == -1)
		perror_free_allocs_exit_failure("fork");

	if (child_pid_2 == 0)
	{
		if (dup2(pipe_fds[PIPE_READ_INDEX], STDIN_FILENO) == -1)
			perror_free_allocs_exit_failure("dup2");

		outfile_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile_fd == -1)
			perror_free_allocs_exit_failure(argv[4]); // TODO: Don't exit immediately?
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
			perror_free_allocs_exit_failure("dup2");

		run_cmd(3, argv, envp);
	}

	close(pipe_fds[PIPE_READ_INDEX]);

	waitpid(child_pid_2, &wstatus_2, 0); // wait() can't be used here since this can catch either child_pid_1 or child_pid_2 first
	waitpid(child_pid_1, NULL, 0);

	ft_free_allocations();
	return (WEXITSTATUS(wstatus_2));
}
