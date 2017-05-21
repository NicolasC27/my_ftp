/*
** Commands.c for Commands.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:12:35 2017 Nicolas
** Last update Sun May 21 20:17:33 2017 Nicolas
*/

#include <stdlib.h>
#include <string.h>
#include "ftp.h"

bool 		add_command(t_command **command, char *str, g_ptr fct)
{
  t_command 	*node;
  t_command 	*tmp;

  if (!(node = (t_command *) malloc(sizeof(*node))))
    return (FALSE);
  tmp = *command;
  node->str = strdup(str);
  node->next = tmp;
  node->fct = fct;
  *command = node;
  return (TRUE);
}

bool 		init_command(t_server *ftp)
{
  if (!(ftp->command = malloc((sizeof(t_command)))))
    return (FALSE);
  if (!add_command(&ftp->command, "user", &user)
      || !add_command(&ftp->command, "pass", &password)
      || !add_command(&ftp->command, "cwd", &cwd)
      || !add_command(&ftp->command, "cdup", &cdup)
      || !add_command(&ftp->command, "dele", &delete)
      || !add_command(&ftp->command, "pwd", &pwd)
      || !add_command(&ftp->command, "pasv", &pasv)
      || !add_command(&ftp->command, "port", NULL)
      || !add_command(&ftp->command, "help", &help)
      || !add_command(&ftp->command, "noop", &noop)
      || !add_command(&ftp->command, "retr", &retr)
      || !add_command(&ftp->command, "stor", &stor)
      || !add_command(&ftp->command, "list", &list)
      || !add_command(&ftp->command, "quit", &quit)
      || !add_command(&ftp->command, "type", &type))
    return (FALSE);
  return (TRUE);
}
