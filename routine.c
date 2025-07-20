/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:19:44 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/19 20:32:37 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philop *pp)
{
	size_t	id;

	id = pp->id;
	if (pp->full == 1)
		return ;
	if (pp->table->head == 1)
		solo_eating(pp);
	pthread_mutex_lock(pp->r_fork);
	o_print(pp, 1, id);
	pthread_mutex_lock(pp->l_fork);
	o_print(pp, 1, id);
	o_print(pp, 2, id);
	pp->last_time_eat = get_time_ms();
	pp->eat_count++;
	smart_rest(pp, pp->table->eat_time);
	pthread_mutex_unlock(pp->r_fork);
	pthread_mutex_unlock(pp->l_fork);
}

void	p_sleep(t_philop *pp)
{
	o_print(pp, 3, pp->id);
	smart_rest(pp, pp->table->sleep_time);
}

void	thinking(t_philop *pp)
{
	o_print(pp, 4, pp->id);
}

void	solo_eating(t_philop *pp)
{
	int	id;

	id = pp->id;
	pthread_mutex_lock(pp->r_fork);
	o_print(pp, 1, id);
	smart_rest(pp, pp->table->die_time);
	pthread_mutex_unlock(pp->r_fork);
	o_print(pp, 5, id);
}
