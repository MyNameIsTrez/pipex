/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_private_error.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/05 15:45:07 by sbos          #+#    #+#                 */
/*   Updated: 2022/08/31 18:19:28 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_PRIVATE_ERROR_H
# define PIPEX_PRIVATE_ERROR_H

t_pipex_error	*pipex_get_error_ptr(void);
t_pipex_error	pipex_get_error(void);

#endif
