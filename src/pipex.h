/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 14:53:19 by sbos          #+#    #+#                 */
/*   Updated: 2022/09/28 14:53:19 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define PIPE_READ_INDEX 0
# define PIPE_WRITE_INDEX 1

# include "libft.h"

# include <stdio.h>
# include <errno.h>
# include <string.h>

void	print_free_allocs_exit(char *prefix, char *msg, int status);
void	strerror_free_allocs_exit_failure(char *prefix);

char	*get_env_value(char *name, char *envp[]);
char	*get_path(char *path_directory, char *cmd_path);

void	run_cmd(size_t cmd_index, char *argv[], char *envp[]);

#endif
