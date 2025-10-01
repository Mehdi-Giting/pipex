/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:15:39 by marvin            #+#    #+#             */
/*   Updated: 2025/09/30 17:15:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

# include "libft/libft.h"
# include "ft_printf/ft_printf.h" 

char	*find_path(char *cmd, char **envp);
void	free_arr(char **all_path);
void	parent_cleanup(int infile, int outfile, int *fd);
void	check_args(int argc, char **argv);

#endif
