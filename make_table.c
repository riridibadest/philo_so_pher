/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:06:00 by yuerliu           #+#    #+#             */
/*   Updated: 2025/10/25 20:43:51 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//1.parse the numbers and time to initialize the system:
//number of ppl, and the things they do. Allocate memories too

//the parse take the arguements: and return a pointer/NULL
t_table	read_input(int ac, char **av)
{
	t_table	feast;

	feast.head = ft_atoi(av[1]);
	if (feast.head == 0)
	{
		printf("Wrong number of Philosophers");
		exit (EXIT_FAILURE);
	}
	feast.die_time = ft_atoi(av[2]);
	feast.eat_time = ft_atoi(av[3]);
	feast.sleep_time = ft_atoi(av[4]);
	feast.min_times_to_eat = -1;
	feast.someone_died = false;
	feast.start_time = 0;
	feast.garbabe_location = NULL;
	pthread_mutex_init(&feast.death, NULL);
	pthread_mutex_init(&feast.p_lock, NULL);
	if (ac == 6)
		feast.min_times_to_eat = ft_atoi(av[5]);
	if (check(&feast, ac) == 0)
	{
		printf("Wrong Input Values\n");
		exit (EXIT_FAILURE);
	}
	return (feast);
}

int	check(t_table *pp, int ac)
{
	if (pp->head < 0 || pp->die_time < 0 || pp->eat_time < 0
		|| pp->sleep_time < 0)
		return (0);
	if (ac == 6 && pp->min_times_to_eat < 0)
		return (0);
	return (1);
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
	int	i;

	i = 0;
	while (i < pimp->head)
	{
		pimp->philop[i].id = i + 1;
		pimp->philop[i].eat_count = 0;
		pimp->philop[i].last_time_eat = get_time_ms();
		pimp->philop[i].fork = i;
		pimp->philop[i].l_fork = &pimp->forks[i];
		pimp->philop[i].full = 0;
		pimp->philop[i].table = pimp;
		if (pimp->head == 1)
			pimp->philop[i].r_fork = &pimp->forks[i];
		else
			pimp->philop[i].r_fork = &pimp->forks[(i + 1) % pimp->head];
		pthread_mutex_init(&pimp->philop[i].eatime, NULL);
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
	pp->philop = malloc_table_sth(pp, splop);
	pp->forks = malloc_table_sth(pp, sfork);
	while (id < pp->head)
	{
		checker = pthread_mutex_init(&pp->forks[id], NULL);
		if (checker != 0)
			exit(EXIT_FAILURE);
		id++;
	}
}

t_table	make_table(int ac, char **av, t_table *pp)
{

	*pp = read_input(ac, av);
	make_philops(pp);
	init_philop(pp);
	// Fix: Set start_time after all initialization is complete
	//pimp.start_time = get_time_ms();
	// Update all philosophers' last_time_eat to match start_time
	return (*pp);
}
