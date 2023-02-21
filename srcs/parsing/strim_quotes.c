/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strim_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontalb <amontalb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:57:31 by amontalb          #+#    #+#             */
/*   Updated: 2023/02/21 15:49:32 by amontalb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



static int  malloc_len(char *s)
{
    int size;
    int i;
    int simple_quotes;
    int double_quotes;

    i = 0;
    count = 0;
    simple_q = 0;
    double_quotes = 0;

    while (s[i])
    {
        simple_q = (simple_q + (!double_q && cmd[i] == '\'')) % 2 ;
        double_q = (double_q + (!simple_q && cmd[i] == '\"')) % 2 ;
        if (((s[i]) == '\"' && !simple_quotes) || ((s[i]) == '\"' && !double_quotes))
            size++;
        i++;
    }
    if (simple_quotes || double_quotes)
        return (-1)
     return (size);
}

char *ft_strim_quotes(char *s)
{
    int     simple_quotes;
    int     double_quotes;
    char    *trim;
    int     i;
    int     j;

    i = 0;
    j = -1;
    if (!s || malloc_len(s) == -1)
        return (NULL);
    trim = malloc((ft_strlen(s) - malloc_len(s) + !) * sizeof(char));
    if (!trim)
        return (NULL);
    while (s[i])
    {
        simple_q = (simple_q + (!double_q && cmd[i] == '\'')) % 2 ;
        double_q = (double_q + (!simple_q && cmd[i] == '\"')) % 2 ;
        if (s[i] != '\"' || simple_q) && (s[i] != '\'' || double_q)
            trim[++j] = s[i];
        i++;
    }
    trim[++j] = '\0';
    return(trim);
}