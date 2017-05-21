/*
** download.c for downloads.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 20:17:41 2017 Nicolas
** Last update Sun May 21 22:12:12 2017 Nicolas
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "ftp.h"

static void		msg_download(t_client *client, int size)
{
  char		msg[MAX_BUFFER];

  snprintf(msg, MAX_BUFFER, OPEN_BINARY, client->message, size);
  write(client->socketfd, msg, strlen(msg));
}

static void		send_file(t_client *new_client, t_client *client,
				  int len, int size)
{
  char		buffer[BUFFER_FILE];
  int 		fd;

  if ((fd = open(client->message, O_RDONLY)) != -1)
    {
      new_client = wait(client);
      if (new_client != NULL)
	{
	  while ((len = read(fd, buffer, 1)))
	    {
	      buffer[len] = '\0';
	      if (write(new_client->socketfd, buffer, strlen(buffer)) == -1)
		break;
	      size += 1;
	    }
	  msg_download(client, size);
	  send_response(client, (close(new_client->socketfd)) == -1
				|| close(client->socketpasv) == -1
				? 450 : 226, NULL);
	  free(new_client);
	  client->pasv = FALSE;
	}
    }
  else
    send_response(client, 550, FAILED_OPEN_F);
}

void 			retr(t_client *client)
{
  t_client		*new_client;

  new_client = NULL;
  if (client->login == AUTH)
    {
      if (client->pasv == TRUE)
	{
	  if (strlen(client->message) > 0)
	    send_file(new_client, client, 0, 0);
	  else
	    send_response(client, 550, FAILED_OPEN_F);
	}
      else
	send_response(client, 425, NULL);
    }
  else
    send_response(client, 530, ACCESS_DENIED);
}
