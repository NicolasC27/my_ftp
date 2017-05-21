/*
** Ftp.h for Ftp.h in /home/nicolas/rendu/PSU_2016_myftp
** 
** Made by Nicolas
** Login   <nicolas1.chevalier@epitech.eu>
** 
** Started on  Sun May 21 17:52:47 2017 Nicolas
** Last update Sun May 21 20:03:50 2017 Nicolas
*/

#ifndef MYFTP_H_
# define MYFTP_H_

/*
 * Includes
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

/*
 *  Defines Error
 */
#define ERROR_SOCKET 	"Error create socket"
#define ERROR_BIND	"Error bind"
#define ERROR_LISTEN	"Error listen"
#define ERROR_FORK	"Error fork"

/* 
 * Define for RFC
 */
#define ACCESS_DENIED	"Please login with USER and PASS"
#define PATH_ERROR	"The path \"%s\" doesn't exist\r\n"
#define FAIL_CHDIR	"Failed to change directory"
#define PERMI_DENIED	"Permission denied."
#define CMD_NOT_FOUND	"Unknow command."
#define INCORRECT_LOGIN	"Login incorrect."
#define GUEST_USER	"Can't change from gest user."
#define LOGIN_FIRST	"Login with USER first."
#define ALREADY_LOG	"Already logged in."
#define NEED_FILE	"Need file to remove."
#define NO_FILE		"No file, can't remove it."
#define TYPE		"TYPE Please specify a type."
#define NO_TYPE		"Type only accept type I."
#define FAILED_OPEN_F	"Failed to open file."
#define FAILED_CREAT_F	"Failed to create file."
#define OPEN_BINARY	"150 Opening BINARY mode data connection for %s (%d bytes).\r\n"

/*
 * Login
 */
#define LOGIN_ID	"anonymous"
#define ERR_LOGIN	3
#define NOT_LOGGED	0
#define LOGGED		1
#define AUTH		2


/*
 * BUFFER
 */
#define BUFFER_FILE	4096
#define MAX_BUFFER	256
#define MAX_CONNECTION	5
#define SIZE_MAX_MSG	256

/*
 * Condition
 */
#define TRUE		1
#define FALSE		0

/*
 * Struct
 */

typedef struct		s_client
{
  struct sockaddr_in 	server_ad;
  char			*message;
  char 			*c_path;
  char 			*path;
  char 			*ip;
  int 			socketpasv;
  int			socketfd;
  int 			login;
  int 			pasv;
  int 			port;
  socklen_t		len;
  int 			old_fd;
}              		t_client;

typedef void (*g_ptr)(t_client *);

typedef struct		s_command
{
  char			*str;
  g_ptr 		fct;
  struct s_command 	*next;
}               	t_command;

typedef struct 		s_response
{
  int 			error;
  char 			*message;
}			t_response;

typedef struct 		s_server
{
  struct sockaddr_in  	server_ad;
  struct sockaddr_in  	converse;
  int                 	socket;
  char 			*path;
  t_command           	*command;
}              		t_server;

void			ftp(int, char *);
void 			strtolower(char *);
void			quit(t_client *);
void			help(t_client *);
void			noop(t_client *);
void			error_ftp(const char *);
void			pasv(t_client *);
void			manage_message(t_client *);
void			user(t_client *);
void			password(t_client *);
void			handling_client(t_server *, int );
void			catch_sigint(int);
void			init_ftp(t_server *, int, char *);
void			init_client(t_client *, int);
void			cdup(t_client *);
void			cwd(t_client *);
void			delete(t_client *);
void			pwd(t_client *);
void			list(t_client *);
void			manage_sigint(t_client *ptr);
bool 			exec_msg(t_command *, t_client *);
bool			send_response(t_client *, int, char *);
bool			add_command(t_command **, char *, g_ptr);
bool			init_command(t_server *);
bool			manage_read(t_client *);
void			type(t_client *);
void	 		retr(t_client *client);
t_client		*wait(t_client *client);
void 			stor(t_client *client);

#endif /* MYFTP_H_ */
