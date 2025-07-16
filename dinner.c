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

void	feast_time(t_table *pp)
{
	int			i;
	pthread_t	td;

	i = 0;
	pthread_create(&td, NULL, do_death_come, pp);
	pthread_join(td, NULL);
	i = 0;
	while (i < pp->head)
	{
		pthread_create(&pp->philop[i].thread, NULL, life_of_philop, &pp);
		pthread_join(pp->philop[i].thread, NULL);
		i++;
	}
}

void	life_of_philop(t_table *pp)
{
	size_t	id;
	bool	finish;

	id = 0;
	finish = we_r_full(pp);
	while (pp->someone_died != true && finish != true)
	{
		eat(pp, id);
		sleep(pp);
		think(pp);
	}
}

int	do_death_come(t_table *eye)
{
	int	id;

	id = 0;
	while (1)
	{
		while (id <= eye->head)
		{
			if (eat_gap(eye, id) > eye->die_time)
				return (o_print(eye, 5, id),
					eye->someone_died = true, 1);
			if ((id + 1) > eye->head)
				id = 0;
			id++;
		}
	}
}

bool	we_r_full(t_table *pp)
{
	int	id;

	id = 0;
	while ()
}
