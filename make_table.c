/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:06:00 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/16 21:52:38 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//1.parse the numbers and time to initialize the system:
//number of ppl, and the things they do. Allocate memories too

//the parse take the arguements: and return a pointer/NULL
t_table	*read_input(int ac, char **av)
{
	t_table	*feast;
	size_t	table;

	table = sizeof(t_table);
	feast = malloc_table_sth(table);//problem, where is pp from
	if (!feast)
		return ;
	feast->head = ft_atoi(av[1]);
	if (feast->head == 0)
	{
		printf("Wrong number of Philosophers");
		return (NULL);
	}
	feast->die_time = ft_atoi(av[2]);
	feast->eat_time = ft_atoi(av[3]);
	feast->sleep_time = ft_atoi(av[4]);
	feast->min_times_to_eat = -1;
	feast->someone_died = false;
	feast->start_time = get_time_ms();
	if (ac == 6)
		feast.min_times_to_eat = ft_atoi(av[5]);
	return (feast);
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
	while (i < pimp->head)
	{
		pimp->philop[i].id = i;
		pimp->philop[i].eat_count = 0;
		pimp->philop[i].last_time_eat = 0;
		pimp->philop[i].fork = i;
		pimp->philop[i].l_fork = &pimp->forks[i];
		if (pimp->head == 1)
			pimp->philop[i].r_fork = &pimp->forks[i];
		else if (i == pimp->head - 1)
			pimp->philop[i].r_fork = &pimp->forks[0];
		else
			pimp->philop[i].r_fork = &pimp->forks[i + 1];
		i++;
	}
}

//here allocating the memory for philosophers, mark each philop's id
void	make_philops(t_table *pp)
{
	size_t	splop;
	size_t	sfork;
	int		id;
	int		checker;

	id = 0;
	splop = (sizeof(t_philop) * pp->head);
	sfork = (sizeof(pthread_mutex_t) * pp->head);
	pp->philop = malloc_table_sth(splop, pp);
	pp->forks = malloc_table_sth(sfork, pp);
	while (id < pp->head)
	{
		checker = pthread_mutex_init(&pp->forks[id], NULL);
		if (checker != 0)
			exit(pp);
		id++;
	}
}

t_table	*make_table(int ac, char **av)
{
	t_table	*pimp;

	pimp = read_input(ac, av);
	make_philops(pimp);
	init_philop(pimp);
	return (pimp);
}
