/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_print_error.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 14:12:24 by sbos          #+#    #+#                 */
/*   Updated: 2022/08/31 18:26:50 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_print_error(void)
{
	ft_putendl_fd("Error", STDERR_FILENO);
}
