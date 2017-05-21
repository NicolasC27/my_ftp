/*
** Execute.c for Execute.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:13:05 2017 Nicolas
** Last update Sun May 21 20:18:29 2017 Nicolas
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "ftp.h"

void		quit(t_client *client)
{
  free(client->message);
  send_response(client, 221, NULL);
  close(client->socketfd);
  exit(EXIT_SUCCESS);
}

void		noop(t_client *client)
{
  if (client->login == AUTH)
    send_response(client, 200, NULL);
  else
    send_response(client, 530, ACCESS_DENIED);
}

void		help(t_client *client)
{
  if (client->login == AUTH)
    send_response(client, 214, NULL);
  else
    send_response(client, 530, ACCESS_DENIED);
}

bool 		exec_msg(t_command *command, t_client *client)
{
  t_command 	*search;

  search = command;
  while (search->next)
    {
      if (!(strncmp(search->str, client->message, strlen(search->str))))
	{
	  manage_message(client);
	  search->fct(client);
	  return (TRUE);
	}
      search = search->next;
    }
  if (client->login != AUTH)
    send_response(client, 530, ACCESS_DENIED);
  else
    send_response(client, 500, CMD_NOT_FOUND);
  return (FALSE);
}
