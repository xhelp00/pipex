/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:34:32 by phelebra          #+#    #+#             */
/*   Updated: 2023/04/25 14:28:28 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char *argv[])
{
	// fd[0] - read
	// fd[1] - write
	int fd[2];
	if (pipe(fd) == -1)
		printf("Error when opening pipe \n");
	int id = fork();
	if (id == 0)
	{
		close(fd[0]);
		int x;
		printf("Input number: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
		{
			printf("error with writing to the pipe");
			return 2;
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			printf("error with read from the pipe");
			return 3;
		}
		close(fd[0]);
		printf("got from child process %d \n", y);
	}
	return (0);
}