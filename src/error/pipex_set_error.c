/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_set_error.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 13:50:42 by sbos          #+#    #+#                 */
/*   Updated: 2022/08/31 18:27:12 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "private/pipex_private_error.h"

t_status	pipex_set_error(t_pipex_error pipex_error)
{
	*pipex_get_error_ptr() = pipex_error;
	return (ERROR);
}
