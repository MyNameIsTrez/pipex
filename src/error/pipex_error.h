/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 16:15:18 by sbos          #+#    #+#                 */
/*   Updated: 2022/08/31 18:16:54 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_ERROR_H
# define PIPEX_ERROR_H

# include "pipex_error_enum.h"

t_status	pipex_any_error(void);
void		pipex_print_error(void);
t_status	pipex_set_error(t_pipex_error pipex_error);

#endif
