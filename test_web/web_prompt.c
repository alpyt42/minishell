/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:04:22 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/24 16:53:06 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://codes-sources.commentcamarche.net/source/35020-un-prompt-linux

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "includes/minishell.h"

int main(int argc, char **argv, char **env) {
    char *command;

    while(1) {
        command = readline("minishell> ");
        add_history(command);
        pid_t pid = fork();
        if (pid == 0) {
            // child process
            char *argv[100];
            char **token = ft_split(command, " ");
            int i = 0;
            while (token != NULL) {
                argv[i] = token;
                token = ft_split(NULL, " ");
                i++;
            }
            argv[i] = NULL;
            execve(argv[0], argv, NULL);
            printf("Command not found\n");
            exit(0);
        } else {
            // parent process
            int status;
            waitpid(pid, &status, 0);
        }
        free(command);
    }

    return 0;
}
