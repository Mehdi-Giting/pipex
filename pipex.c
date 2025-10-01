/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:15:33 by marvin            #+#    #+#             */
/*   Updated: 2025/09/30 17:15:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(char *in_file, char *out_file, int *infile, int *outfile)
{
	*infile = open(in_file, O_RDONLY);
	if (*infile < 0)
	{
		ft_printf("%s: %s\n", in_file, strerror(errno));
		exit(1);
	}
	*outfile = open(out_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (*outfile < 0)
	{
		ft_printf("%s: %s\n", out_file, strerror(errno));
		exit(1);
	}
}

void	first_child(char **argv, char **envp, int *fd, int infile)
{
	char	**args;
	char	*path;

	args = ft_split(argv[2], ' ');
	path = find_path(args[0], envp);
	if (!path)
	{
		perror("command not found");
		free_arr(args);
		exit(127);
	}
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(infile);
	close(fd[0]);
	close(fd[1]);
	execve(path, args, envp);
	perror("execve");
	free(path);
	free_arr(args);
	exit(1);
}

void	second_child(char **argv, char **envp, int *fd, int outfile)
{
	char	**args;
	char	*path;

	args = ft_split(argv[3], ' ');
	path = find_path(args[0], envp);
	if (!path)
	{
		perror("command not found");
		free_arr(args);
		exit(127);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close(fd[0]);
	close(fd[1]);
	execve(path, args, envp);
	perror("execve");
	free(path);
	free_arr(args);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	check_args(argc, argv);
	open_files(argv[1], argv[4], &infile, &outfile);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid1 = fork();
	if (pid1 == 0)
		first_child(argv, envp, fd, infile);
	pid2 = fork();
	if (pid2 == 0)
		second_child(argv, envp, fd, outfile);
	parent_cleanup(infile, outfile, fd);
	return (0);
}
