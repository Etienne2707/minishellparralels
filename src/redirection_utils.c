#include "minishell.h"

int nb_outfile(t_token *token, char **arg)
{
    int i;

    i = 0;
    while (arg[i] != 0)
    {
        if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], ">>") == 0)
            token->last_o = i;
        i++;
    }
    return (token->last_o);
}

int nb_infile(t_token *token, char **arg)
{
    int i;

    i = 0;
    while (arg[i] != 0)
    {
        if (ft_strcmp(arg[i], "<") == 0)
            token->last_i = i;
        i++;
    }
    return (token->last_i);
}

