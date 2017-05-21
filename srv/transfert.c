/*
** Transfert.c for Transfer.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:36:38 2017 Nicolas
** Last update Sun May 21 20:23:53 2017 Nicolas
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ftp.h"

static void		print_pasv(t_client *client, struct sockaddr_in server,
				   char buffer[MAX_BUFFER])
{
  client->port = ntohs(server.sin_port);
  snprintf(buffer, MAX_BUFFER, "127,0,0,1,%d,%d", (client->port / 256),
	   (client->port) - ((client->port / 256) * 256));
  send_response(client, 227, buffer);
}

void			pasv(t_client *client)
{
  struct sockaddr_in  	server;
  socklen_t		len;
  char 			buffer[MAX_BUFFER];

  if (client->login == AUTH)
    {
      if ((client->socketpasv = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	error_ftp(ERROR_SOCKET);
      memset(&server, 0, sizeof(server));
      server.sin_family = AF_INET;
      server.sin_port = 0;
      server.sin_addr.s_addr = htonl(INADDR_ANY);
      if (bind(client->socketpasv, (struct sockaddr *) &(server),
	       sizeof(server)) < 0)
	error_ftp(ERROR_BIND);
      if (listen(client->socketpasv, MAX_CONNECTION) == -1)
	error_ftp(ERROR_LISTEN);
      len = sizeof(server);
      getsockname(client->socketpasv, (struct sockaddr *) &server, &len);
      print_pasv(client, server, buffer);
      client->pasv = TRUE;
    }
  else
    send_response(client, 530, ACCESS_DENIED);
}
