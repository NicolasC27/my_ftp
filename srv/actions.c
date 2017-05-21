/*
** Actions.c for Actions.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:08:15 2017 Nicolas
** Last update Sun May 21 21:51:37 2017 Nicolas
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ftp.h"

void 		delete(t_client *client)
{
  if (client->login == AUTH)
    {
      if (strlen(client->message) <= 0)
	send_response(client, 550, NEED_FILE);
      else if (remove(client->message) == -1)
	send_response(client, 550, NO_FILE);
      else
      	send_response(client, 250, NULL);
    }
  else
    send_response(client, 530, ACCESS_DENIED);
}

void		pwd(t_client *client)
{
  if (client->login == AUTH)
    send_response(client, 257, client->path);
  else
    send_response(client, 530, ACCESS_DENIED);
}

static void	list_wait(t_client *client, const char *ls)
{
  t_client	*new_client;

  new_client = wait(client);
  if (new_client != NULL)
    {
      send_response(client, 150, NULL);
      new_client->old_fd = dup(1);
      dup2(new_client->socketfd, 1);
      system(ls);
      if ((close(new_client->socketfd)) == -1 ||
	  close(client->socketpasv) == -1)
	send_response(client, 450, NULL);
      else
	send_response(client, 226, NULL);
      dup2(new_client->old_fd, 1);
      free(new_client);
    }
}

void		list(t_client *client)
{
  char 		*ls;

  if (client->login == AUTH)
    {
      if (client->pasv == TRUE)
	{
	  if ((ls = malloc(MAX_BUFFER)) == NULL)
	    send_response(client, 550, "Malloc ls failed");
	  else
	    {
	      strcpy(ls, "ls -la ");
	      strcat(ls, client->message);
	      list_wait(client, ls);
	      client->pasv = FALSE;
	    }
	}
      else
	send_response(client, 425, NULL);
    }
  else
    send_response(client, 530, ACCESS_DENIED);
}

void		type(t_client *client)
{
  if (strlen(client->message) > 0)
    {
      if (strncmp(client->message, "A", 1) != 0 &&
	  strncmp(client->message, "I", 1) != 0)
	send_response(client, 500, NO_TYPE);
      else
      	send_response(client, 200, NULL);
    }
  else
    send_response(client, 500, TYPE);
}
