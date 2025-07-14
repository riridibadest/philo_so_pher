/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:06:00 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/14 03:13:23 by yuerliu          ###   ########.fr       */
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

void	init_philop(t_table *pimp)
{
	size_t	i;

	i = 0;
	while (i < ppl->head)
	{
		pimp->philop[i].id = i;
		pimp->philop[i].eat_count = 0;
		pimp->philop[i].last_time_eat = 0;
		pimp->philop[i].fork = i; 
		pimp->philop[i].l_fork = &pimp->forks[i];
		if (ppl->head != 1)
			pimp->philop[i].r_fork = &pimp->forks[i + 1];
		else
			pimp->philop[i].r_fork = &pimp->forks[i];
		i++;
	}
}

//here allocating the memory for philosophers, mark each philop's id
void	make_philops(t_table *pp)
{
	size_t	splop;
	size_t	sfork;
	int		id;
	int	checker;

	id = 0;
	splop = (sizeof(t_philop) * pp->head);
	sfork = (sizeof(pthread_mutex_t) * pp->head);
	pp->garbabe_location = malloc_table_sth(splop, pp);//do I need a pointer here?
	pp->forks = malloc_table_sth(sfork, pp);
	while (id < pp->head)
	{
		checker = pthread_mutex_init(&pp->forks[id], NULL);
		if (checker != 0)
			exit(pp);
		id++;
	}
}

void	make_table(int ac, char **av)
{
	t_table	*pimp;

	read_input(ac, av);
	make_philops(pimp);
	init_philop(pimp);
}
