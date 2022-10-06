/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_run.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 18:28:09 by sbos          #+#    #+#                 */
/*   Updated: 2022/08/31 18:29:26 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_INIT_H
# define PIPEX_INIT_H

typedef struct s_data	t_data;

t_status	pipex_run(size_t argc, char *argv[], char *envp[]);

#endif
