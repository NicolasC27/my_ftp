/*
** strtolower.c for strtolower in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:27:54 2017 Nicolas
** Last update Sun May 21 17:28:56 2017 Nicolas
*/

#include <ctype.h>
#include "ftp.h"

void		strtolower(char *string)
{
  char		*cp;

  cp = string;
  while (*cp && *cp != ' ' && *cp != '\t')
    {
      *cp = tolower(*cp);
      cp++;
    }
}
