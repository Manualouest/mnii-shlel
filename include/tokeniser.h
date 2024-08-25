/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:07:08 by mbirou            #+#    #+#             */
/*   Updated: 2024/08/25 21:22:59 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISER_H
# define TOKENISER_H

# include <mnii_shlel.h>

// ms_tokeniser_main.c
void		*ms_free_cmd(t_cmd *cmd);
t_cmd		*ms_tokeniser_main(char *line, char **envp);

// ms_first_setup.c
int			ms_nb_params(char *line, int index, int *line_index);
int			ms_get_cut_len(char *line, int main_index, int main_index_save,
				int *cut_len);
char		**ms_cut_text(char *line);
void		ms_base_setup(t_cmd *cmd, char *line);

// ms_setup_utils.c
int			ms_go_to_pipe(char *line, int *main_index);
int			ms_change_quote_level(char *line, int index, int old_quote_level);
char		*ms_tripple_join(char *first, char *second, char *third,
				int frees);
char		**ms_remove_empty_chars(char **args);

// ms_env_utils.c
char		*ms_find_env_name(char *content, char **envp);

// ms_env_checking.c
int			ms_has_dollar(char *arg);

// ms_second_setup.c
int			ms_setup_round_two(t_cmd *cmd, char **envp);
int			ms_get_var_start(char *arg, int *var_len);
char		*ms_get_var(char *arg, int var_pos, int var_len, char **envp);

// ms_expand_utils.c
void		ms_setup_var_info(char ***args, int index, int *var_pos, int *var_len);
char		*ms_replace_str(char *original, char *new);
char		ms_get_quote_to_index(char *arg, int pos);

// ms_expand.c
int			ms_expand_loop(char ***args, char **envp);

// ms_in_out_file_setup.c
void		ms_in_out_files_setup(t_cmd *cmd, char **envp);

// ms_file_setup_utils.c
int			ms_is_file_real(char *filename);
char		**ms_remove_filename(char **args, int elem_index);
int			ms_opens(t_cmd *cmd, char *filename, int is_created, int kind);
void		ms_handle_errors(t_cmd *cmd, int error_id, char *error,
				char *token);
char		*ms_clean_filename(char	*old_name);

// ms_string_cleaning.c
void		ms_separate_symbols_base(t_cmd *cmd, int quote);
void		ms_quote_hider(t_cmd *cmd, char **arg);

// ms_handle_quotes.c
void		ms_hide_quotes(t_cmd *cmd);
void		ms_remove_hiders(t_cmd *cmd, int arg_i);

// ms_heredoc_main.c
void		ms_launch_heredoc(t_cmd *cmd, char ***args,	int *i, char **envp);

// ms_heredoc_expand.c
int			ms_should_expand_heredoc(char **delimiter);
void		ms_insert_env(char **input, int i, int env_len, char **envp);
void		ms_do_heredoc_env(char **input, char **envp);

#endif