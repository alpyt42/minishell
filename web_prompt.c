/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:04:22 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/24 16:05:30 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://codes-sources.commentcamarche.net/source/35020-un-prompt-linux

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *prompt (void)
{
   char *invite = NULL;
   char const *user = getenv("USERNAME");

   if (user == NULL)
   {
      user = getenv("USER");

      if (user == NULL)
      {
         user = "";
      }

   }

   {
      char const *host = getenv("HOSTNAME");

      if (host == NULL)
      {
         host = "";
      }

      {
         char const *aux = getenv("PWD");

         if (aux == NULL)
         {
            aux = "";
         }
         {
            char const *rep = aux + strlen(aux);

            while (rep >= aux && *rep != '/')
            {
               rep--;
            }

            rep++;

            invite = malloc(strlen(user) + strlen(host) + strlen(rep) + 6);

            if (invite != NULL)
            {
               strcpy(invite, "[");
               strcat(invite, user);
               strcat(invite, "@");
               strcat(invite, host);
               strcat(invite, " ");
               strcat(invite, rep);
               strcat(invite, "]");
               strcat(invite, "$");
               strcat(invite, " ");
            }

         }

      }
   }
   return invite;
}

int main (void)
{
   int end = 0;

   while (!end)
   {
      char *s = prompt();

      if (s != NULL)
      {
         printf ("%s", s);
         fflush (stdout);
         free (s), s = NULL;
      }

      {
         char line[128];
         fgets(line, sizeof line, stdin);
         end = strcmp(line, "quit\n") == 0;
      }

   }
   return 0;
}