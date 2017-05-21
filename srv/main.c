/*
** main.c for main.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:18:00 2017 Nicolas
** Last update Sun May 21 20:21:50 2017 Nicolas
*/

#include <stdlib.h>
#include "ftp.h"

int		usage()
{
  printf("Usage : ./server port path\n");
  return (0);
}

int		main(int argc, char **argv)
{
  if (argc != 3)
    return (usage());
  else
    ftp(atoi(argv[1]), argv[2]);
}
