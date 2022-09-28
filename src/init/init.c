/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 18:12:26 by sbos          #+#    #+#                 */
/*   Updated: 2022/09/01 15:33:28 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_status	pipex_init(size_t argc, char **argv, t_data *data)
{
	(void)argc;
	(void)argv;
	ft_bzero(data, sizeof(t_data));
	return (OK);
}
