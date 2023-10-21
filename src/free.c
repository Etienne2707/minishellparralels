#include "minishell.h"

void    free_token(t_token **token, int k)
{
    int i;

    while (k >= 0) 
    {
        if (token[k] != NULL) 
        {
            i = 0;
            if (token[k]->delimiter != NULL) {
                while (token[k]->delimiter[i] != NULL) 
                {
                    free(token[k]->delimiter[i]);
                    i++;
                }
                free(token[k]->delimiter);
            }

            i = 0;
            while (token[k]->arg[i] != NULL) 
            {
                free(token[k]->arg[i]);
                i++;
            }
            free(token[k]);
        }
        k--;
    }
}



void free_maillon(t_pars *pars)
{
    int i;

    i = 0;
    while (pars->cmd[i] != 0)
    {
        free(pars->cmd[i]);
        i++;
    }
     free(pars->cmd);
     i = 0;
    if (pars->delimiter != NULL)
    while (pars->delimiter[i] != 0)
    {
        free(pars->delimiter[i]);
        i++;
    }
    free(pars->delimiter);
    free(pars);
}

void    ft_free_list(t_pars **pars)
{
    if (*pars == NULL)
        return ;
    t_pars *next;

    next = (*pars)->next;
    free_maillon((*pars));
    ft_free_list(&next);  
}