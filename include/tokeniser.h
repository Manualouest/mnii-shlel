
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

typedef enum TYPE
{
	SYMBOL,
	STRING
}	TYPE;

typedef enum CMD
{
	NO_CMD,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	CMD;

typedef enum SYMBOLS
{
	NO_SYMBOL,
	QUOTE,
	DOUBLE_QUOTE,
	INPUT,// <
	HEREDOC,// <<
	REDIRECT,// >
	APPEND,// >>
	DOLLAR,
	SLASH
}	SYMBOLS;

typedef enum CMD_ERRORS
{
	NO_ERROR,
	BAD_PARAMS,
	BAD_CMD,
	BAD_PATH
}	CMD_ERRORS;

typedef	struct	s_pipes
{
	struct s_command	*command;
	struct s_pipes		*right;
	int					error;
}						t_pipes;

typedef struct s_params
{
	int				type;
	char			*text;
	int				symbol;
	int				quote_level;
	struct s_params	*next;
}				t_params;

typedef struct s_command
{
	int				cmd;
	int				has_option;
	struct s_params	*params;
	int				error;
}					t_command;

// ms_tokeniser_main.c
t_pipes	*ms_tokeniser_main(char *line);

// ms_tokeniser_cmd.c
void	ms_init_cmd(t_command *command, char *line, int *i);

// ms_tokeniser_params.c
void	ms_fill_params(t_command *cmd, t_params *params, char *line, int *i);

// ms_tokeniser_utils.c
int		ms_am_i_at_the_next_pipe(char *line, int i);
void	ms_head_to_next_pipe(char *line, int *main_index);
char	*ms_get_next_item(char *line, int *main_index, int quote);
int		ms_is_symbol(char c);
int		ms_is_not_symbol(int c);

#endif