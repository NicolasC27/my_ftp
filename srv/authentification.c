/*
** Authentification.c for Authentification in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:08:05 2017 Nicolas
** Last update Sun May 21 17:43:03 2017 Nicolas
*/

#include <string.h>
#include "ftp.h"

void		user(t_client *client)
{
  if (client->login != AUTH)
    {
      if (strlen(client->message) > 0)
	{
	  strtolower(client->message);
	    client->login = !(strncmp(LOGIN_ID, client->message,
				      strlen(LOGIN_ID))) ? LOGGED : ERR_LOGIN;
	    send_response(client, 331, NULL);
	}
      else
	send_response(client, 530, PERMI_DENIED);
    }
  else
    send_response(client, 530, GUEST_USER);
}

void		password(t_client *client)
{
  if ((client->login == LOGGED) || (client->login == ERR_LOGIN))
    {
      if (client->login == ERR_LOGIN)
	{
	  client->login = NOT_LOGGED;
	  send_response(client, 530, INCORRECT_LOGIN);
	}
      else
	{
	  if ((client->login == LOGGED))
	    {
	      client->login = AUTH;
	      send_response(client, 230, NULL);
	    }
	  else if (client->login == NOT_LOGGED)
	    send_response(client, 332, NULL);
	}
    }
  else
    send_response(client, 503, client->login == AUTH ?
		  ALREADY_LOG : LOGIN_FIRST);
}
