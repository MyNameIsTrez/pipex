/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 12:31:38 by sbos          #+#    #+#                 */
/*   Updated: 2022/10/13 12:31:38 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env_value(char *name, char *envp[])
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

char	*get_path(char *path_directory, char *cmd_path)
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
