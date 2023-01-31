/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-cont <ale-cont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:39:07 by ale-cont          #+#    #+#             */
/*   Updated: 2023/01/31 16:47:55 by ale-cont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
  char *old_value = getenv("USER");
  printf("Old value: %s\n", old_value);
  setenv("USER", "alric", 1);
  char *new_value = getenv("USER");
  printf("New value: %s\n", new_value);
  return 0;
}
