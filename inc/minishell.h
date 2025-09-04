/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:08:37 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/04 18:56:52 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define INPUT 1   //"<"
# define HEREDOC 2 //"<<"
# define TRUNC 3   //">"
# define APPEND 4  //">>"
# define PIPE 5    //"|"
# define CMD 6     //"|"
# define ARG 7     //"|"

# define MALLOC_ERROR "malloc error\n"
# define PIPE_ERROR "pipe error\n"
# define FORK_ERROR "fork error\n"

# define EXT_MALLOC 1
# define EXT_PIPE 1
# define EXT_FORK 1

extern pid_t			g_signal_pid;

typedef struct s_cmd
{
	bool				skip_cmd;
	int					infile;
	int					outfile;
	pid_t				pid;
	char				**cmd_param;
	struct s_cmd		*prev;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_token
{
	char				*str;
	int					type;
	char				*types;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_mini_list
{
	char				*str;
	struct s_mini_list	*prev;
	struct s_mini_list	*next;
}						t_mini_list;

typedef struct s_data
{
	t_mini_list			*env;
	t_token				*token;
	t_cmd				*cmd;
	int					exit_code;
	int					pip[2];
	bool				sq;
	char				*last_cmd;
}						t_data;

int						append(t_mini_list **list, char *elem);
bool					make_env2(t_data *data);
int						make_env(t_data *data, char **env);
void					free_all(t_data *data, char *err, int ext);
void					free_array(char **arr);
void					free_cmd(t_cmd **list);
void					free_token(t_token **list);
int						free_list(t_mini_list **list);
void					clear_rl_line(void);
void					signals(void);
bool					parseline(t_data *data, char *line);
int						open_quote(t_data *data, char *line);
bool					print_error(char *str);
int						add_dollar(char *line, int *index, char **str,
							t_data *data);
size_t					len_list(t_mini_list *list);
char					*get_dollar_word(char *line, int size);
char					*get_elem_env(t_mini_list *env, char *key);
int						add_char(char *c, char **str, t_data *data, int *index);
int						exist_in_env(char *line, int *i, t_data *data);
bool					is_space(char c);
int						is_special(char *str);
bool					create_list_token(t_token **begin, char *command);
int						append_token(t_token **list, char **str, int type,
							int quote);
bool					create_list_cmd(t_data *data);
int						append_cmd(t_cmd **list, int infile, int outfile,
							char **cmd_param);
bool					get_infile(t_data *data, t_token *token, t_cmd *cmd);
bool					print_error_token(t_token *token, t_data *data);
bool					get_outfile(t_token *token, t_cmd *cmd, t_data *data);
char					**get_param(t_data *data, t_token *token);
bool					check_pipe(t_data *data);
void					print_token(t_token *token);
int						here_doc(t_data *data, char *word);
int						replace_dollar(char **line, t_data *data);
int						append_substr(char **dest, char *src, int len);
int						ft_strlen_exp(char *line);
char					*ft_strjoin_free(char *s1, char *s2);
void					quoting_choice(bool *dq, bool *sq, int *index, char c);
size_t					len_cmd(t_cmd *list);
bool					is_builtin(char *cmd);
void					child_process(t_data *data, t_cmd *cmd, int *pip);
bool					launch_builtin(t_data *data, t_cmd *cmd);
void					absolute_path(char **path, char *cmd, t_data *data);
char					*find_cmd(t_data *data, char *sample, t_mini_list *env);
int						ft_strslashjoin(char *dest, char *str, char *env,
							int *index);
char					**lst_to_arr(t_mini_list *env);
void					signals2(void);
int						ft_cd(t_data *data, char **params);
int						ft_env(t_mini_list *env);
bool					exec(t_data *data);
int						ft_pwd(void);
int						ft_echo(char **args);
int						ft_unset(char **str, t_mini_list **env);
int						ft_export(char **str, t_mini_list **env);
void					ft_exit(t_data *data, char **args);
bool					export(char *str, t_mini_list **env);
void					sort_array(char **arr, int len);
void					free_part(t_data *data);
void					update_shlvl(t_data *data);
bool					condition(char *line, int i);
bool					condition1(char *line, int i);
int						add_chars(char *c, char **str, t_data *data,
							int *index);
char					*ft_strjoin_frees(char *s1, char *s2);
t_data					*get_data(t_data *data);
t_cmd					*get_cmd(t_cmd *cmd, int state);

#endif