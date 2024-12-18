#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAXLINE 4096
#define PORT 8080
// TODO: figure out the right number for this
#define LISTEN_BACKLOG 10

#define SIMPLE_RESP "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 10\r\n\r\nayo waddup"

int main()
{
	// initialize globals
	int listen_fd;
	int conn_fd;
	int n;
	struct sockaddr_in server_addr;
	uint8_t buff[MAXLINE + 1];
	uint8_t recv_line[MAXLINE + 1];

	// create socket;
	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("failed to create socket\n");
		exit(EXIT_FAILURE);
	}

	// set up server address
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	// bind address
	if ((bind(listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr))) < 0)
	{
		perror("failed to bind\n");
		exit(EXIT_FAILURE);
	}

	// start listening
	if ((listen(listen_fd, LISTEN_BACKLOG)) < 0)
	{
		perror("failed to listen\n");
		exit(EXIT_FAILURE);
	}

	// loop to wait for connections
	while (1)
	{
		struct sockaddr_in addr;
		socklen_t addr_len;

		printf("waiting for connection\n");
		fflush(stdout);

		conn_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);
		printf("got connection\n");

		memset(recv_line, 0, MAXLINE);
		while ((n = read(conn_fd, recv_line, MAXLINE-1)) > 0)
		{
			fprintf(stdout, "\n%s\n", recv_line);
			if (recv_line[n-1] == '\n') break;
			memset(recv_line, 0, MAXLINE);
			if (n < 0)
			{
				perror("read error\n");
				exit(EXIT_FAILURE);
			}
		}
		snprintf((char*)buff, sizeof(buff), SIMPLE_RESP);
		write(conn_fd, (char*)buff, strlen((char*)buff));
		close(conn_fd);
	}
}
