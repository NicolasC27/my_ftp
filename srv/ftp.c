/*
** Ftp.c for Ftp.c in /home/nicolas/rendu/PSU_2016_myftp
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:41:13 2017 Nicolas
** Last update Sun May 21 20:20:56 2017 Nicolas
*/

#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "ftp.h"

void			error_ftp(const char *str)
{
    printf("%s\r\n", str);
    exit(EXIT_FAILURE);
}

void			manage_sigint(t_client *ptr)
{
  static t_client	*client;

  if (ptr)
    client = ptr;
  else
    {
      close(client->socketfd);
      puts("\nExiting server...");
      exit(0);
    }
}

void			catch_sigint(int sig)
{
  (void)sig;
  manage_sigint((t_client*)0);
}

void			ftp(int port, char *path)
{
  t_server		ftp;
  int			newsockfd;
  socklen_t		lg;
  int			pid;

  init_ftp(&ftp, port, path);
  init_command(&ftp);
  lg = sizeof(ftp.converse);
  while (1)
    if ((newsockfd = accept(ftp.socket, (struct sockaddr *)
			    &(ftp.converse), &lg)) > 0)
      {
	if ((pid = fork()) < 0)
	  error_ftp(ERROR_FORK);
	else
	  if (pid == 0)
	    {
	      close(ftp.socket);
	      handling_client(&ftp, newsockfd);
	      close(newsockfd);
	      exit(EXIT_SUCCESS);
	    }
	  else pid > 0 ? close(newsockfd) : printf("Serveur error\n");
      }
}
