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

// t_status	pipex_run(size_t argc, char *argv[], char *envp[])
// {
// 	int		x;
// 	char	**cmd1_parts;
// 	char	*cmd1_path;
// 	char	**cmd1_argv;

// 	(void)argc;

// 	cmd1_parts = ft_split(argv[2], ' ');
// 	cmd1_path = cmd1_parts[0];
// 	cmd1_argv = &cmd1_parts[1];

// 	x = open(argv[1], O_RDONLY);
// 	if (x == -1)
// 		return (ERROR); // TODO: shell won't execute cmd1 but *will* run the stuff after the pipe

// 	if (ft_chr_in_str('/', cmd1_path))
// 	{
// 		if (run_cmd_if_accessible(cmd1_path, cmd1_argv, envp) != OK)
// 		{

// 		}
// 	}
// 	else if (path_subvalues != NULL)
// 	{
// 		if (run_cmd_if_accessible_path_subvalues(cmd1_path, path_subvalues, cmd1_argv, envp) != OK)
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
