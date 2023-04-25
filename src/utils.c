/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:34:32 by phelebra          #+#    #+#             */
/*   Updated: 2023/04/25 11:07:03 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char *argv[])
{
	int id = fork();
	int n;

	if (id == 0)
	{
		n = 1;
	}
	else
	{
		n = 6;
	}
	if (id != 0)
		wait(0);
	int i = n;
	while (i < n + 5)
	{
		printf("%d", i);
		fflush(stdout);
		i++;
	}
	if (id != 0)
		printf("\n");
	
	return (0);
}