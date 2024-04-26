
#ifndef TOKENISER_H
# define TOKENISER_H

# include <libft.h>
# include <get_next_line_bonus.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef enum e_type
{
	SYMBOL,
	STRING
}	t_type;

typedef enum e_cmd
{
	NO_CMD,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_cmd;

typedef enum e_symbols
{
	NO_SYMBOL,
	QUOTE,
	DOUBLE_QUOTE,
	INPUT,// <
	HEREDOC,// <<
	REDIRECT,// >
	APPEND,// >>
	DOLLAR
}	t_symbols;

typedef enum e_cmd_errors
{
	NO_ERROR,
	BAD_PARAMS,
	BAD_CMD,
	BAD_PATH
}	t_cmd_errors;

typedef	struct	s_pipes
{
	struct s_command	*command;
	struct s_pipes		*right;
	t_cmd_errors		error;
}						t_pipes;

typedef struct s_command
{
	t_cmd			builtins;
	char			*cmd;
	int				has_option;
	struct s_params	*params;
	t_cmd_errors	error;
}					t_command;

typedef struct s_params
{
	t_type			type;
	char			*text;
	t_symbols		symbol;
	int				quote_level;
	struct s_params	*next;
}				t_params;

// ms_tokeniser_main.c
t_pipes	*ms_tokeniser_main(char *line);

// ms_tokeniser_cmd.c
void	ms_init_cmd(t_command *command, char *line, int *i);
char	*ms_get_next_item(char *line, int *main_index);

// ms_tokeniser_params.c
void	ms_fill_params(t_command *cmd, t_params *params, char *line, int *i);

// ms_tokeniser_utils.c
void	ms_head_to_next_pipe(char *line, int *main_index);
int		ms_is_line_done(char *line, int i, char *item);
int		ms_am_i_at_the_next_pipe(char *line, int i);
int		ms_is_not_symbol(int c);
int		ms_is_symbol(char c);

// ms_tokeniser_free.c
void	ms_pipes_free_main(t_pipes *pipes);

#endif