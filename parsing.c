/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:43:57 by moer-ret          #+#    #+#             */
/*   Updated: 2024/08/11 12:40:51 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	res;
	long	signe;

	i = 0;
	res = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
		if (!(ft_isdigit(str[i])))
			return (2147483649);
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res * 10) > 2147483647)
			return (2147483649);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * signe);
}

int	ft_num(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+' || s[0] == ' ')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
		write(fd, "\n", 1);
	}
	return (1);
}

int	check_speac(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\t')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	parsing(int ac, char **av)
{
	long	nb;
	int		i;

	i = 1;
	if (ac != 5 && ac != 6)
		if (ft_putendl_fd("U NEDD 5 or 6 ARGUMENT", 2) == 1)
			return (0);
	while (av[i])
	{
		nb = ft_atoi(av[i]);
		if (nb > INT_MAX || !ft_num(av[i]) \
			|| check_speac(av[i]))
			if (ft_putendl_fd("ERROR", 2) == 1)
				return (0);
		i++;
	}
	return (1);
}
