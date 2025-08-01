/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:26:25 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/24 19:44:10 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	pp;
	t_table	*pimp;

	if (ok_input(ac, av) == 0)
		return (printf("Wrong Input or Wrong Number of Arguments"), 1);
	pimp = read_input(&pp, ac, av);
	feast_time(pimp);
	clean_up(pp.garbabe_location);
	//system("leaks philo");
	return (0);
}

//1.parse the numbers and time to initialize the system:number of ppl,
	//and the things they do. Allocate memories too
//2.the process of taking the fork,
	//eat and repeat. (have to now make sure all ppl eat,
		//and log the state of each plop)
//3.make sure they die if the condition not satisfied.
//4.Clear all the things stored within.
