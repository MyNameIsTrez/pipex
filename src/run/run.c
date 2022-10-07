/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 18:12:26 by sbos          #+#    #+#                 */
/*   Updated: 2022/09/01 15:33:28 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static char	*get_env_value(char *name, char *envp[])
// {
// 	size_t	name_len;
// 	size_t	i;

// 	name_len = ft_strlen(name);
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		if (ft_strncmp(envp[i], name, name_len) == 0
// 			&& envp[i][name_len] == '=')
// 			return (envp[i] + name_len + 1);
// 		i++;
// 	}
// 	return (NULL);
// }

// static char	**get_env_subvalues(char *env_value)
// {
// 	return (ft_split(env_value, ' '));
// }

// static char	*get_path(char *path_subvalue, char *cmd1_path)
// {
// 	size_t	path_len;
// 	char	*path;

// 	path_len = ft_strlen(path_subvalue) + 1 + ft_strlen(cmd1_path) + 1;
// 	path = ft_malloc(path_len, sizeof(char));
// 	if (path == NULL)
// 		return (NULL);
// 	path[0] = '\0';
// 	ft_strlcat(path, path_subvalue, path_len);
// 	ft_strlcat(path, "/", path_len);
// 	ft_strlcat(path, cmd1_path, path_len);
// 	return (path);
// }

// static t_status	run_cmd(char *path, char *cmd_argv[], char *envp[])
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		return (ERROR);
// 	if (pid == 0)
// 	{
// 		// in child
// 		dup2(x, STDIN_FILENO);
// 		if (execve(path, cmd_argv, envp) == -1)
// 			return (pipex_set_error(PIPEX_E_SYSTEM));
// 	}
// 	else
// 	{
// 		// in parent
// 	}
// }

// static bool	accessible(char *path)
// {
// 	return (access(path, F_OK | X_OK) == 0);
// }

// static t_status	try_run_cmd(char *path, char *cmd_argv[], char *envp[])
// {
// 	if (accessible(path) && run_cmd(path, cmd_argv, envp) == OK)
// 		return (OK);
// 	return (ERROR);
// }

// static void	perror_free_allocations_exit(void)
// {
// 	perror("pipex");
// 	ft_free_allocations();
// 	exit(EXIT_FAILURE);
// }

// static t_status	try_run_cmd_path_subvalues(char *cmd1_path, char **path_subvalues, char *cmd_argv[], char *envp[])
// {
// 	size_t	i;
// 	char	*path;

// 	i = 0;
// 	while (path_subvalues[i] != NULL)
// 	{
// 		path = get_path(path_subvalues[i], cmd1_path);
// 		if (path == NULL)
// 			return (ERROR);
// 		if (try_run_cmd(path, cmd_argv, envp))
// 			return (OK);
// 		i++;
// 	}
// 	return (ERROR);
// }

// t_status	pipex_run(size_t argc, char *argv[], char *envp[])
// {
// 	int		x;
// 	char	*path_value;
// 	char	*path_subvalues;
// 	char	**cmd1_parts;
// 	char	*cmd1_path;
// 	char	**cmd1_argv;

// 	(void)argc;
// 	path_value = get_env_value("PATH", envp);
// 	path_subvalues = get_env_subvalues(path_value);

// 	cmd1_parts = ft_split(argv[2], ' ');
// 	cmd1_path = cmd1_parts[0];
// 	cmd1_argv = &cmd1_parts[1];

// 	x = open(argv[1], O_RDONLY);
// 	if (x == -1)
// 		return (ERROR); // TODO: shell won't execute cmd1 but *will* run the stuff after the pipe

// 	if (ft_chr_in_str('/', cmd1_path))
// 	{
// 		if (try_run_cmd(cmd1_path, cmd1_argv, envp) != OK)
// 		{

// 		}
// 	}
// 	else if (path_subvalues != NULL)
// 	{
// 		if (try_run_cmd_path_subvalues(cmd1_path, path_subvalues, cmd1_argv, envp) != OK)
// 		{
// 		}
// 	}
// 	else
// 	{
// 		ft_putstr_fd("pipex: ", STDERR_FILENO);
// 		ft_putstr_fd(cmd1_path, STDERR_FILENO);
// 		ft_putendl_fd(": command not found", STDERR_FILENO);
// 	}

// 	if (close(x) == -1)
// 		return (ERROR);

// 	return (OK);
// }
