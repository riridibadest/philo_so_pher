/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:24:33 by yuerliu           #+#    #+#             */
/*   Updated: 2025/10/26 00:59:24 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// start the routine

int	feast_time(t_table *pp)
{
	int			i;
	//pthread_t	td;

	i = 0;
	pp->start_time = get_time_ms();
	while (i < pp->head)
	{	
		pp->philop[i].last_time_eat = pp->start_time + 5;
		pthread_create(&pp->philop[i].thread, NULL, life_of_philop,
			&pp->philop[i]);
		i++;
	}
	// pthread_create(&td, NULL, dead_yet, pp);
	//pthread_join(td, NULL);
	return (1);
}

void	*life_of_philop(void *pp)
{
	t_philop	*philop;
	bool		state;

	philop = (t_philop *)pp;
	if (pp == NULL)
		return (NULL);
	while (1)
	{
		if ((philop->id % 2) == 0) 
			usleep(philop->table->eat_time * 0.75);
		pthread_mutex_lock(&philop->table->death);
		state = philop->table->someone_died;
		pthread_mutex_unlock(&philop->table->death);
		if (state)
			return (NULL);
		pthread_mutex_lock(&philop->eatime);
		if (philop->full == 1)
		{
			pthread_mutex_unlock(&philop->eatime);
			return (NULL);
		}
		pthread_mutex_unlock(&philop->eatime);
		eat(philop);
		p_sleep(philop);
		thinking(philop);
	}
	return (NULL);
}

//have to set checking_dead in the routine. so philops exit in time
void	*dead_yet(void *pp)
{
	int		id;
	t_table	*eye;

	eye = (t_table *)pp;
	while (1)
	{
		id = 0;
		while (id < eye->head)
		{
			if (we_r_full(eye) == 0)
				return (o_print(&eye->philop[0], 6, 1), NULL);
			if (eat_gap(eye, id) > eye->die_time)
			{
				pthread_mutex_lock(&eye->death);
				eye->someone_died = true;
				pthread_mutex_unlock(&eye->death);
				return (o_print(&eye->philop[id], 5, id + 1), NULL);
			}
			id++;
		}
		// smart_rest(pp, 1);
		usleep(100);
	}
	return (NULL);
}

int	we_r_full(t_table *pp)
{
	int	id;

	id = 0;
	if (pp->min_times_to_eat <= -1)
		return (1);
	while (id < pp->head)
	{
		pthread_mutex_lock(&pp->philop[id].eatime);
		// if (pp->philop[id].eat_count < pp->min_times_to_eat)
		// 	return (1);
		// if (pp->philop[id].eat_count == pp->min_times_to_eat)
		// 	pp->philop[id].full = 1;
		if (pp->philop[id].full == 0)
			return (pthread_mutex_unlock(&pp->philop[id].eatime), 1);
		pthread_mutex_unlock(&pp->philop[id].eatime);
		id++;
	}
	return (0);
}
