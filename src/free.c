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
