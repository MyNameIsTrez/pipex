/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_get_error_ptr.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 14:00:43 by sbos          #+#    #+#                 */
/*   Updated: 2022/08/31 18:24:53 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex_error	*pipex_get_error_ptr(void)
{
	static t_pipex_error	pipex_error = PIPEX_OK;

	return (&pipex_error);
}
