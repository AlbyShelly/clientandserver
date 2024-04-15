#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main(int argc, char* argv[] ){

	//create a localsocketfd
	int socketfd = socket(AF_INET, SOCK_DGRAM, 0 );

	//create a remotesocketaddress struct
	struct sockaddr_in remotesocketaddress;
	memset(&remotesocketaddress, 0, sizeof(remotesocketaddress) );

	remotesocketaddress.sin_family = AF_INET;
	remotesocketaddress.sin_port = htons(PORT);
	//remotesocketaddress.sin_addr.s_addr = INADDR_ANY;
	printf("inet_pton returns %i \n",inet_pton(AF_INET, argv[1], &remotesocketaddress.sin_addr));

	char *senddata = argv[2];
	int sen = sendto(socketfd, senddata, strlen(senddata), 0, (struct sockaddr_in *) &remotesocketaddress, sizeof(remotesocketaddress));

	printf("message sent\n");
	printf("send: %i\n",sen);

	//receive response
	char recvdata[MAXLINE];
	memset(recvdata, 0, MAXLINE);

	int n = recvfrom( socketfd, recvdata, MAXLINE, 0, NULL, NULL);

	printf("Server: %s\n", recvdata);
	
	return 0;
}	
	
