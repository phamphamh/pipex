/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:54:48 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/29 20:08:11 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_pip
{
	pid_t	*pids;
	int		pipe_tab[2];
	int		pipe_fds[2];
	char	**argv;
	char	**cmd_args;
	char	*cmd_path;
	int		fd;
	char	**env;
	int		here_doc;
	int		exec_pos;
	int		nb_cmds;
}			t_pip;

// path
bool	find_count_exe(char **argv, int argc, t_pip *struc);
char	*find_path(char **env);
char	*join_paths(char **paths, char *cmd);
char	*check_path(char *cmd, char **env);

//utils
int		ft_strcmp_env(const char *s1, const char *s2);
void	free_all(char **split);
int		ft_strllen(char **str);
bool	only_space(char *str);
void	handle_error(char *message);
int		ft_strcmp_trimmed(const char *s1, const char *s2);

//dup
void	open_fd_out(t_pip *struc);
void	open_fd_in(t_pip *struc);
void	handle_mid_cmd(t_pip *struc);
void	handle_last_cmd(t_pip *struc);
void	handle_first_cmd(t_pip *struc);

//process
void	ft_execve(t_pip *struc);
pid_t	handle_child(t_pip *struc);
void	set_here_doc(t_pip *struc);
void	set_cmd_args(t_pip *struc, int idx);

//pipex
void	init_things(t_pip *struc, char **env, char **argv, int argc);
void	parse_args(char **argv, int argc, t_pip *struc);
int		main(int argc, char **argv, char **env);

#endif
