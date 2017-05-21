/*
** wait.c for wait.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 22:10:31 2017 Nicolas
** Last update Sun May 21 22:11:48 2017 Nicolas
*/

#include <stdio.h>
#include <stdlib.h>
#include "ftp.h"

/*
** Wait client for mode passive
** get client connection
 */
t_client		*wait(t_client *client)
{
  t_client		*new_client;

  if ((new_client = malloc(sizeof(t_client))) != NULL)
    {
      new_client->len = sizeof(new_client->server_ad);
      new_client->socketfd = accept(client->socketpasv, (struct sockaddr *)
				    &(new_client->server_ad), &(new_client->len));
      return (new_client);
    }
  else
    send_response(client, 550, "Malloc client failed");
  return (NULL);
}
