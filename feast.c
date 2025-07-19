/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:24:33 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/16 22:14:22 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// start the routine

int	feast_time(t_table *pp)
{
	int			i;
	pthread_t	td;

	i = 0;
	pp->start_time = get_time_ms();
	while (i < pp->head)
	{
		pthread_create(&pp->philop[i].thread, NULL, life_of_philop, &pp->philop[i]);
		i++;
	}
	i = 0;
	while (i < pp->head)
	{
		pthread_join(pp->philop[i].thread, NULL);
		i++;
	}
	pthread_create(&td, NULL, dead_yet, pp);
	pthread_join(td, NULL);
	return (1);
}

void	*life_of_philop(void *pp)
{
	t_philop	*philop;
	bool	state;

	philop = (t_philop *)pp;
	if (philop->full == 1)
		return	;
	while (1)
	{
		pthread_mutex_lock(&pp->death);
		state = philop->table->someone_died;
		pthread_mutex_unlock(&pp->death);
		if (state)
			return ;
		eat(philop);
		sleep(philop);
		think(philop);
	}
	return NULL;
}

//have to set checking_dead in the routine. so philops exit in time
int	dead_yet(t_table *eye)
{
	int	id;

	id = 0;
	while (id < eye->head && eye->someone_died != true)
	{
			if (eat_gap(eye, id) > eye->die_time)
			{

				return (o_print(eye, 5, id), 1);
			}
			id++;
			if (id == eye->head)
			{
				if (we_r_full(eye) == 0)
					return (o_print(eye, 6, id), 1);
				id = 0;
			}
	}
}

int	we_r_full(t_table *pp)
{
	int	id;

	id = 0;
	if (pp->min_times_to_eat == -1)
		return (1);
	while (id < pp->head)
	{
		if (pp->philop[id].eat_count < pp->min_times_to_eat)
			return (1);
		if (pp->philop[id].eat_count == pp->min_times_to_eat)
			pp->philop[id].full = 1;
		id++;
	}
	return (0);
}
