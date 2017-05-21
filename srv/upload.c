/*
** upload.c for upload.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 22:10:43 2017 Nicolas
** Last update Sun May 21 23:40:23 2017 Nicolas
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "ftp.h"

static void		upload_file(t_client *new_client, t_client *client,
				     int len)
{
  char		upload[BUFFER_FILE];
  int 		fd;

  new_client = wait(client);
  if ((fd = creat(client->message, S_IRUSR | S_IWUSR | S_IRGRP |
				   S_IROTH)) != -1)
    {
      if (new_client != NULL)
	{
	  send_response(client, 150, NULL);
	  while ((len = read(new_client->socketfd, upload, BUFFER_FILE)) > 0)
	    {
	      upload[len] = '\0';
	      if (write(fd, upload, strlen(upload)) == -1)
		break;
	    }
	  send_response(client, (close(new_client->socketfd)) == -1 ||
			close(client->socketpasv) == -1 ?
			450 : 226, NULL);
	  free(new_client);
	  client->pasv = FALSE;
	}
    }
  else
    send_response(client, 550, FAILED_CREAT_F);
}

void 		stor(t_client *client)
{
  t_client		*new_client;

  new_client = NULL;
  if (client->login == AUTH)
    {
      if (client->pasv == TRUE)
	{
	  if (strlen(client->message) > 0)
	    upload_file(new_client, client, 0);
	  else
	    send_response(client, 550, FAILED_OPEN_F);
	}
      else
	send_response(client, 425, NULL);
    }
  else
    send_response(client, 530, ACCESS_DENIED);

}
