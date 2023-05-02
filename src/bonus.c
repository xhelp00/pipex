/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:34:45 by phelebra          #+#    #+#             */
/*   Updated: 2023/05/02 11:01:30 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child(char *av, char **env)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		execute(av, env);
	}
	else
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

/* Function who make a child process that will read from the stdin with
 get_next_line until it find the limiter word and then put the output inside a
 pipe. The main process will change his stdin for the pipe file descriptor. */
void	here_doc(char *limiter, int ac)
{
	int		pid;
	int		fd[2];
	char	*line;

	if (ac < 6)
		arg_error(1);
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == 0)
	{
		close(fd[READ_END]);
		while (ft_get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[WRITE_END]);
		wait(NULL);
	}
}

/* Makes a dup2 from the file given and then closes the file */
void	dup_close(int src, int dst)
{
	dup2(src, dst);
	close(src);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	infile;
	int	outfile;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			i = 3;
			outfile = open_file(av[ac - 1], 0);
			here_doc(av[2], ac);
		}
		else
		{
			i = 2;
			outfile = open_file(av[ac - 1], 1);
			infile = open_file(av[1], 2);
			dup_close(infile, STDIN_FILENO);
		}
		while (i < ac - 2)
			child(av[i++], env);
		dup2(outfile, STDOUT_FILENO);
		execute(av[ac - 2], env);
	}
	arg_error(1);
}
