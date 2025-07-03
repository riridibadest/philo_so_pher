/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:06:00 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/03 16:19:12 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//1.parse the numbers and time to initialize the system:
//number of ppl, and the things they do. Allocate memories too

//the parse take the arguements: and return a pointer/NULL
void	read_input(int ac, char **av)
{
	t_table	feast;

	if (ac == 5 || ac == 6)
	{
		feast.head = ft_atoi(av[1]);
		if (feast.head == 0)
		{
			printf("Wrong number of Philosophers");
			return (NULL);
		}
		feast.die_time = ft_atoi(av[2]);
		feast.eat_time = ft_atoi(av[3]);
		feast.sleep_time = ft_atoi(av[4]);
		if (ac == 6)
			feast.min_time_to_eat = ft_atoi(av[5]);
	}
	else
	{
		printf("Wrong number of arguments");
		return (NULL);
	}
}

// int	create(void)
// {
// 	pthread_t	thread1;
// 	pthread_t	thread2;

// 	pthread_create(thread1, NULL, threadFunc, NULL);
// 	pthread_create(thread2, NULL, threadFunc, NULL);
// }

void	init_philop(t_philop *pimp)
{
	size_t	i;
	t_table	*ppl;

	while (i < ppl->head)
	{
		pimp->id = i;
		pimp->eat_count = 0;
		pimp->last_time_eat = 0;
		i++;
	}
}

void	make_philops(t_philop *pp)
{
	size_t	size;
	t_table	*pimp;
	int		id;

	id = 0;
	size = (sizeof(t_philop) * pimp->head);
	while (id < pimp->head)
	{
		pimp = malloc_table_sth((void *)pimp, size);
		pimp = 
		id++;
	}
}

void	make_table(int ac, char **av)
{
	t_philop	*pimp;

	read_input(ac, av);
	init_philop(pimp);
	make_philops(pimp);
}
