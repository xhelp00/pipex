/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:34:32 by phelebra          #+#    #+#             */
/*   Updated: 2023/04/27 15:05:13 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char *argv[])
{
	int pid = fork();
	if (pid == -1)
		printf("Error on forking\n");
	if (pid == 0)
	{
		//child process
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
	}
	else
	{
		//parent process
		wait(NULL);
		printf("Success!\n");
	}

	return (0);
}