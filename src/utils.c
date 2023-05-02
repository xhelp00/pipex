/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:34:32 by phelebra          #+#    #+#             */
/*   Updated: 2023/05/02 10:59:23 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	error(void)
{
	perror("Error: ");
	return (1);
}

void	arg_error(int flag)
{
	ft_putstr_fd("Error: Command not found\n", 2);
	if (flag)
		ft_putstr_fd("Usage: ./bonus here_doc LIMITATOR cmd1 cmd2 outfile\n", 1);
	else
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 1);
	exit(EXIT_SUCCESS);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*slashed;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		slashed = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slashed, cmd);
		free(slashed);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	execute(char *argv, char **env)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (execve(find_path(cmd[0], env), cmd, env) == -1)
		error();
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY | O_CLOEXEC, 0777);
	if (file == -1)
		error();
	return (file);
}
