/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 12:31:41 by sbos          #+#    #+#                 */
/*   Updated: 2022/10/13 12:31:41 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec(char *path, char *cmd_argv[], char *envp[])
{
	execve(path, cmd_argv, envp);
	strerror_free_allocs_exit_failure("execve");
}

static void	run_cmd_with_slashes(char *path, char *cmd_argv[], char *envp[])
{
	if (access(path, F_OK) == -1)
		print_free_allocs_exit(path, strerror(errno), 127);
	if (access(path, X_OK) == -1)
		print_free_allocs_exit(path, strerror(errno), 126);
	exec(path, cmd_argv, envp);
}

static void	run_cmd_without_slashes(char *cmd_path, char **path_subvalues,
				char *cmd_argv[], char *envp[])
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
			strerror_free_allocs_exit_failure("get_path");
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
		print_free_allocs_exit(cmd_path, "command not found", 127);
	print_free_allocs_exit(first_existing_path, strerror(EACCES), 126);
}

void	run_cmd(size_t cmd_index, char *argv[], char *envp[])
{
	char	**cmd_argv;
	char	*cmd_passed;
	char	*path_value;
	char	**path_subvalues;

	cmd_argv = ft_split(argv[cmd_index], ' ');
	if (cmd_argv == NULL)
		strerror_free_allocs_exit_failure("ft_split");
	cmd_passed = cmd_argv[0];
	if (ft_chr_in_str('/', cmd_passed))
		run_cmd_with_slashes(cmd_passed, cmd_argv, envp);
	else
	{
		path_value = get_env_value("PATH", envp);
		path_subvalues = ft_split(path_value, ':');
		if (path_subvalues == NULL)
			print_free_allocs_exit(cmd_passed, "command not found", 127);
		run_cmd_without_slashes(cmd_passed, path_subvalues, cmd_argv, envp);
	}
}
