/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:34:35 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/29 15:45:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	timer(void)
{
	struct timeval	timing;
	long int		time;

	if (gettimeofday(&timing, NULL) == -1)
		return (0);
	time = (timing.tv_sec * 1000) + (timing.tv_usec / 1000);
	return (time);
}

void	ft_usleep(int time)
{
	long long	t;

	t = timer();
	while (timer() - t < time)
		usleep(60);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	parsing(ac, av);
	init_data(ac, av, data);
	return (0);
}
