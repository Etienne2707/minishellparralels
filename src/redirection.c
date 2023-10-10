#include "minishell.h"

void    get_infile(t_token *token, char **arg, int i)
{
    int fd;

    fd = open(arg[i], O_RDONLY);
    token->infile = fd;
    close(fd);

}

void    get_outfile(t_token *token, char **arg, int i)
{
    int fd;

    printf("oui");
    fd = open(arg[i], O_TRUNC | O_CREAT | O_RDWR, 0000644);
    token->outfile = fd;
    close(fd);
}

int    redirection(t_token *token, char **arg)
{
    int i;

    i = 0;
    while (arg[i] != 0)
    {
        if (strcmp(">",arg[i]) == 0)
            get_outfile(token,arg,i + 1);
        else if (strcmp("<",arg[i]) == 0)
            get_infile(token,arg,i + 1);
        i++;
    }
}