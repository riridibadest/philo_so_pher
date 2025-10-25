/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:26:25 by yuerliu           #+#    #+#             */
/*   Updated: 2025/10/26 00:47:30 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	pp;
	int 	i;

	if (ok_input(ac, av) == 0)
		return (printf("Wrong Input or Wrong Number of Arguments"), 1);
	pp = make_table(ac, av);
	feast_time(&pp);
	dead_yet(&pp);
	i = 0;
	while (i < pp.head)
	{
		pthread_join(pp.philop[i].thread, NULL);
		i++;
	}
	clean_up(pp.garbabe_location);
	// system("leaks philo");
	return (0);
}

//1.parse the numbers and time to initialize the system:number of ppl,
	//and the things they do. Allocate memories too
//2.the process of taking the fork,
	//eat and repeat. (have to now make sure all ppl eat,
		//and log the state of each plop)
//3.make sure they die if the condition not satisfied.
//4.Clear all the things stored within.
