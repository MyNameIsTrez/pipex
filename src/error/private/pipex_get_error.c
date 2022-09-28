/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_get_error.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 13:54:22 by sbos          #+#    #+#                 */
/*   Updated: 2022/08/31 18:19:09 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "pipex_private_error.h"

t_pipex_error	pipex_get_error(void)
{
	return (*pipex_get_error_ptr());
}
