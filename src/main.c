/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 14:52:44 by sbos          #+#    #+#                 */
/*   Updated: 2022/09/28 14:52:44 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(t_i32 argc, char **argv)
{
	t_data	data;

	// if (argc <= 1)
	// 	return (EXIT_SUCCESS);
	if (pipex_init((size_t)argc, argv, &data) != OK)
	{
		pipex_print_error();
		ft_free_allocations();
		return (EXIT_FAILURE);
	}
	ft_free_allocations();
	return (EXIT_SUCCESS);
}
