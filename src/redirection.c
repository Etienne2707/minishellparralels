#include "minishell.h"

void    get_heredoc(t_token *token, char **arg)
{
    int i;
    int nbh;

    i = 0;
    nbh = 0;
    while (arg[i] != 0)
    {
        if (strcmp("<<", arg[i]) == 0)
            nbh++;
        i++;
    }
    if (nbh == 0)
        return ;
    token->delimiter = malloc(sizeof(char *) * nbh + 1);
    if (!token->delimiter)
        return ;
    i = 0;
    nbh = 0;
    while (arg[i] != 0)
    {
        if (strcmp("<<", arg[i]) == 0)
        {
            token->delimiter[nbh++] = ft_remove_quote(arg[i + 1]);
        }
        i++;
    }
    
    token->delimiter[nbh] = 0;
}

void    get_append(t_token *token, char **arg, int i)
{
    int fd;

    if (token->outfile == -1)
        return ;
    fd = open(arg[i], O_APPEND | O_CREAT | O_RDWR, 0000644);
    token->outfile = fd;
    token->append = 1;
    close(fd);
}

void    get_infile(t_token *token, char **arg, int i)
{
    int fd;

    if (token->infile == -1)
        return ;
    fd = open(arg[i], O_RDONLY);
    token->infile = fd;
    close(fd);

}

void    get_outfile(t_token *token, char **arg, int i)
{
    int fd;

    if (token->outfile == -1)
        return ;
    fd = open(arg[i], O_TRUNC | O_CREAT | O_RDWR, 0000644);
    token->outfile = fd;
    token->append = 0;
    close(fd);
}

int    redirection(t_token *token, char **arg)
{
    int i;

    i = 0;
    token->append = 0;
    token->outfile = 0;
    token->infile = 0;
    get_heredoc(token,arg);
    while (arg[i] != 0)
    {
        if (strcmp(">",arg[i]) == 0)
            get_outfile(token,arg,i + 1);
        else if (strcmp("<",arg[i]) == 0)
            get_infile(token,arg,i + 1);
        else if (strcmp(">>", arg[i]) == 0)
            get_append(token,arg,i + 1);
        i++;
    }
    return (1);
}