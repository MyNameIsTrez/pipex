/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 12:31:34 by sbos          #+#    #+#                 */
/*   Updated: 2022/10/13 12:31:34 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_free_allocs_exit(char *prefix, char *msg, int status)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (prefix != NULL)
	{
		ft_putstr_fd(prefix, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	ft_free_allocations();
	exit(status);
}

void	strerror_free_allocs_exit_failure(char *prefix)
{
	print_free_allocs_exit(prefix, strerror(errno), EXIT_FAILURE);
}
