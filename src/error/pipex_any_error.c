/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_any_error.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 13:45:03 by sbos          #+#    #+#                 */
/*   Updated: 2022/08/31 18:25:29 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "private/pipex_private_error.h"

t_status	pipex_any_error(void)
{
	if (ft_any_error() != OK)
		return (ERROR);
	if (pipex_get_error() != PIPEX_OK)
		return (ERROR);
	return (OK);
}
