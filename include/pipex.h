/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:54:48 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/26 23:26:13 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_pip
{
	pid_t	*pids;
	int		**pipes;
	int		nb_pipes;
	char	**argv;
	char	**cmd_args;
	char	*cmd_path;
	int		fd;
	char	**env;
	int		here_doc;
	int		exec_pos;
	int		nb_cmds;
	int		exit_status;
	int		argc;
	int		idx;
}			t_pip;

// path
bool	find_count_exe(char **argv, int argc, t_pip *struc);
char	*find_path(char **env);
char	*join_paths(char **paths, char *cmd);
char	*check_path(char *cmd, char **env);

//utils
int		ft_strcmp_env(const char *s1, const char *s2);
int		ft_strllen(char **str);
bool	only_space(char *str);
int		ft_strcmp_trimmed(const char *s1, const char *s2);
void	close_all_pipes(t_pip *struc);

//errors
void	free_all(char **split);
void	handle_error(char *message, t_pip *struc, int nb_error);
void	free_parent(t_pip *struc);
void	free_pipes(t_pip *struc);
void	return_message(char *message, int nb_error);

//dup
void	open_fd_out(t_pip *struc);
void	open_fd_in(t_pip *struc);

//process
void	ft_execve(t_pip *struc);
void	dup_child(t_pip *struc);
pid_t	handle_child(t_pip *struc);
void	set_here_doc(t_pip *struc, int temp_fd);
void	set_cmd_args(t_pip *struc);

//pipex
void	init_things(t_pip *struc, char **env, char **argv, int argc);
void	init_pipes(t_pip *struc);
void	parse_args(char **argv, int argc, t_pip *struc);
int		main(int argc, char **argv, char **env);
void	wait_for_children(t_pip *struc);

#endif
