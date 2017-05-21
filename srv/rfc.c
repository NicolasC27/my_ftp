/*
** RFC.c for RFC.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:27:44 2017 Nicolas
** Last update Sun May 21 20:27:56 2017 Nicolas
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "ftp.h"

t_response g_rfc[] =
  {
    {120, "120 Service ready in %s minutes.\r\n"},
    {125, "125 Data connection already open; transfer starting.\r\n"},
    {150, "150 File status okay; about to open data connection.\r\n"},
    {200, "200 Command okay.\r\n"},
    {214, "214 Help On how to use the server or the meaning of "
     "a particular non-standard command.  This reply is "
     "useful only to the human user.\r\n"},
    {220, "220 Service ready for new user.\r\n"},
    {221, "221 Service closing control connection.\r\n"},
    {226, "226 Closing data connection.\r\n"},
    {227, "227 Entering Passive Mode (%s).\r\n"},
    {230, "230 User logged in, proceed.\r\n"},
    {250, "250 Requested file action okay, completed.\r\n"},
    {257, "257 \"%s\" created.\r\n"},
    {331, "331 User name okay, need password.\r\n"},
    {332, "332 Need account for login.\r\n"},
    {425, "425 Use PORT or PASV first.\r\n"},
    {450, "450 Requested file action not taken."},
    {215, "215 UNIX Type: L8\r\n"},
    {227, "227 Entering Passive Mode (%s).\r\n"},
    {503, "503 %s\r\n"},
    {500, "500 %s\r\n"},
    {530, "530 %s\r\n"},
    {550, "550 %s\r\n"},
    {0,   (char *) 0}
  };

bool		send_response(t_client *client, int code_rfc, char *opt)
{
  char		buffer[MAX_BUFFER];
  int 		i;

  i = 0;
  while (g_rfc[i].error != code_rfc)
    i += 1;
  if (opt != NULL)
    snprintf(buffer, MAX_BUFFER, g_rfc[i].message, opt, 1);
  else
    snprintf(buffer, MAX_BUFFER, g_rfc[i].message);
  write(client->socketfd, buffer, strlen(buffer));
  return (TRUE);
}
