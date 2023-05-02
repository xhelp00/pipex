/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:08:46 by phelebra          #+#    #+#             */
/*   Updated: 2023/05/02 11:05:18 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define READ_END	0
# define WRITE_END	1

int		error(void);
void	arg_error(int flag);
void	execute(char *argv, char **env);
int		open_file(char *argv, int i);

/* bonus */
int		ft_get_next_line(char **line);

#endif