/*
** Init.c for Init.c in /home/nicolas/rendu/PSU_2016_myftp/srv
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:17:19 2017 Nicolas
** Last update Sun May 21 20:21:28 2017 Nicolas
*/

#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "ftp.h"

void		init_path(t_server *server, char *path)
{
  DIR *rep = NULL;

  rep = opendir(path);
  if (rep == NULL)
    {
      printf(PATH_ERROR, path);
      exit(EXIT_FAILURE);
    }
  if (closedir(rep) == -1)
    exit(EXIT_FAILURE);
  if ((chdir(path)) == -1)
    {
      printf(PATH_ERROR, path);
      exit(EXIT_FAILURE);
    }
  server->path = strdup(path);
}

void		init_ftp(t_server *ftp, int port, char *path)
{
  init_path(ftp, path);
  if ((ftp->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    error_ftp(ERROR_SOCKET);
  memset(&ftp->server_ad, 0, sizeof(ftp->server_ad));
  ftp->server_ad.sin_family = AF_INET;
  ftp->server_ad.sin_port = htons(port);
  ftp->server_ad.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(ftp->socket, (struct sockaddr *) &(ftp->server_ad),
	   sizeof(ftp->server_ad)) < 0)
    error_ftp(ERROR_BIND);
  if (listen(ftp->socket, MAX_CONNECTION) == -1)
    error_ftp(ERROR_LISTEN);
}

void 		init_client(t_client *client, int sock)
{
    struct 	in_addr locaddr;
    struct 	hostent *phe;
  char 		ac[256];

  gethostname(ac, sizeof(ac));
  phe = gethostbyname(ac);
  memcpy(&locaddr, phe->h_addr_list[0], sizeof(struct in_addr));
  client->ip = strdup(inet_ntoa(locaddr));
  client->pasv = FALSE;
  client->socketfd = sock;
  client->login = NOT_LOGGED;
  if (((client->message = malloc(sizeof(char *) * SIZE_MAX_MSG))) == NULL)
    printf("ERROR");
  send_response(client, 220, NULL);
}
