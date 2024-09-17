/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:54:48 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/17 17:12:35 by yboumanz         ###   ########.fr       */
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
}			t_pip;

int		ft_strcmp_env(const char *s1, const char *s2);
void	free_all(char **split);
char	*find_path(char **env);
char	*join_paths(char **paths, char *cmd);
char	*check_path(char *cmd, char **env);
void	handle_error(char *message);
void	ft_execve_1(char *cmd_path, char **args, t_pip *struc, int fd);
void	ft_execve_2(char *cmd_path, char **args, t_pip *struc, int fd);
pid_t	handle_child_1(t_pip *struc);
pid_t	handle_child_2(t_pip *struc);
void	init_things(t_pip *struc, char **env, char **argv);
char	**ft_split(char const *s, char c);
void	init_quotes(int *in_single_quotes, int *in_double_quotes);
void	init_split_vars(size_t *i, size_t *j, int *index);
bool	only_space(char *str);
bool	find_count_exe(char **argv, int argc, t_pip *struc);
void	set_here_doc(t_pip *struc, int fd);

#endif
