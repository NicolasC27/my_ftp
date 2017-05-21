/*
** Manage_input.c for Manage_input.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:18:23 2017 Nicolas
** Last update Sun May 21 20:27:37 2017 Nicolas
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "ftp.h"

bool		manage_read(t_client *client)
{
  char		buffer[MAX_BUFFER];
  int		len;
  int		size;
  int		i;
  bool 		ok[1];

  ok[0] = false;
  ok[1] = false;
  if ((client->message = malloc(MAX_BUFFER)) == NULL)
    return (FALSE);
  memset(client->message, 0, SIZE_MAX_MSG);
  size = 0;
  while ((len = read(client->socketfd, buffer, 1)) > 0)
    {
      i = -1;
      buffer[len] = '\0';
      while (buffer[++i] != '\0')
	{
	  buffer[i] == '\r' ? (ok[0] = TRUE) : buffer[i] == '\n' ? (ok[1] = TRUE) :
	    (client->message[size++] = buffer[i]);
	  if (ok[0] == TRUE && ok[1] == TRUE)
	    return ((client->message[size] = '\0'), TRUE);
	}
    }
  return (free(client->message), FALSE);
}

/*
** Erase the mandatory FTP commands of the string client->message
*/
void		manage_message(t_client *client)
{
  char 		*buffer;
  int 		i;
  int 		y;

  y = 0;
  i = 0;
  buffer = strdup(client->message);
  while (buffer[i] && buffer[i] != ' ' && buffer[i] != '\t')
    i += 1;
  if (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'))
    i += 1;
  memset(client->message, 0, strlen(client->message));
  while (buffer[i] != '\0')
    {
      client->message[y] = buffer[i];
      y += 1;
      i += 1;
    }
  client->message[y] = '\0';
}
