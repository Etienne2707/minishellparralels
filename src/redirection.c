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
    printf("je suis i : %d", i);
    if (i - 1 == token->last_o)
    {
        printf("je close pas le fd je suis le append");
        return ;
        
    }
    close(fd);
}

void    get_infile(t_token *token, char **arg, int i)
{
    int fd;

    if (token->infile == -1)
        return ;
    fd = open(arg[i], O_RDONLY);
    token->infile = fd;
    printf("je suis i : %d", i);
    if (i - 1 == token->last_i)
    {
        printf("je close pas le fd je suis le infile");
        return ;
        
    }
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
    printf("je suis i : %d", i);
    if (i - 1 == token->last_o)
    {
        printf("je close pas le fd");
        return ;
        
    }
    close(fd);
}


int nb_outfile(t_token *token, char **arg)
{
    int i;

    i = 0;
    while (arg[i] != 0)
    {
        if (strcmp(arg[i], ">") == 0 || strcmp(arg[i], ">>") == 0)
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
        if (strcmp(arg[i], "<") == 0)
            token->last_i = i;
        i++;
    }
    return (token->last_i);
}


int    redirection(t_token *token, char **arg)
{
    int i;
    int k;

    i = 0;
    token->append = 0;
    token->outfile = 0;
    token->infile = 0;
    token->delimiter = NULL;
    get_heredoc(token,arg);
    token->last_o = nb_outfile(token, arg);
    printf("nb = %d\n", token->last_o);
    token->last_i = nb_infile(token,arg);
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