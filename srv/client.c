/*
** Client.c for Client.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:08:24 2017 Nicolas
** Last update Sun May 21 20:17:16 2017 Nicolas
*/

#include <string.h>
#include <signal.h>
#include "ftp.h"

void 		handling_client(t_server *ftp, int sock)
{
  t_client	client;

  init_client(&client, sock);
  client.path = strdup("/");
  client.c_path = strdup(ftp->path);
  manage_sigint(&client);
  signal(SIGINT, catch_sigint);
  while (1)
    {
      if ((manage_read(&client)) != FALSE)
	{
	  strtolower(client.message);
	  exec_msg(ftp->command, &client);
	}
    }
}
