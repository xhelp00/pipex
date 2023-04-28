/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:34:32 by phelebra          #+#    #+#             */
/*   Updated: 2023/04/28 21:16:06 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	error(void)
{
	perror("Error: ");
	return (1);
}

int	arg_error(void)
{
	ft_putstr_fd("Error: Bad arguments\n", 2);
	return (2);
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
