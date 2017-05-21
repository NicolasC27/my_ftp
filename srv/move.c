/*
** Move.c for Move.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:24:51 2017 Nicolas
** Last update Sun May 21 19:43:02 2017 Nicolas
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "ftp.h"

void		cdup(t_client *client)
{
  if (client->login == AUTH)
    {
      if ((chdir(client->c_path)) == -1)
	send_response(client, 550, NULL);
      else
	{
	  free(client->path);
	  client->path = strdup("/");
	  send_response(client, 250, NULL);
	}
    }
  else
    send_response(client, 530, ACCESS_DENIED);
}

static void	change_directory(t_client *client, char *buffer)
{
  int 		i;

  i = 0;
  free(client->path);
  if ((client->path = malloc(sizeof(char) * MAX_BUFFER)) != NULL)
    {
      getcwd(client->path, MAX_BUFFER);
      if (strlen(client->c_path) > strlen(client->path) ||
	  strlen(client->c_path) == strlen(client->path))
	{
	  chdir(client->c_path);
	  client->path = strdup("/");
	}
      else
	{
	  while (client->path[i] == client->c_path[i])
	    i += 1;
	  buffer = strdup(&(client->path[i]));
	  free(client->path);
	  client->path = strdup(buffer);
	}
      send_response(client, 250, NULL);
    }
  else
    send_response(client, 550, "Failed buffer malloc");
}

void		cwd(t_client *client)
{
  if (client->login == AUTH)
    {
      if (client->message[0] == '/')
	{
	  chdir(client->c_path);
	  if (client->message[1] == '\0')
	    client->path = strdup("/");
	  else
	    {
	      if ((chdir(&(client->message[1]))) == -1)
		send_response(client, 550, FAIL_CHDIR);
	      else
		change_directory(client, NULL);
	    }
	}
      else
	{
	  if ((chdir(client->message)) == -1)
	    send_response(client, 550, FAIL_CHDIR);
	  else
	    change_directory(client, NULL);
	}
    }
  else
    send_response(client, 530, ACCESS_DENIED);
}

