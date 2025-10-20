/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:40:25 by marvin            #+#    #+#             */
/*   Updated: 2025/10/01 15:40:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_cleanup(int infile, int outfile, int *fd)
{
	close(infile);
	close(outfile);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}

void	check_args(int argc, char **argv)
{
	if (!argv[2] || !argv[3] || argv[2][0] == '\0' || argv[3][0] == '\0')
	{
		ft_printf(": command not found\n");
		exit(1);
	}
	if (argc != 5)
	{
		ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n");
		exit(1);
	}
}
