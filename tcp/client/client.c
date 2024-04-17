#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int PORT;

int main( int argc, char* argv[]){
	
	//validate args
	if( argc!= 4){

		printf("Usage: ./a.out ip port text\n");
		exit(1);
	}

	PORT = atoi(argv[2]);

	//create remote socket addr struct
	struct sockaddr_in rem_soc_addr;
	memset(&rem_soc_addr, sizeof(rem_soc_addr), 0);
	rem_soc_addr.sin_family = AF_INET;
	rem_soc_addr.sin_addr.s_addr = htonl( atoi(argv[1]) );
	rem_soc_addr.sin_port = htons(PORT);

	//create a socket
	int soc_fd;
	if( soc_fd= socket(PF_INET, SOCK_STREAM, 0) < 0){

		printf("Error: socket creation failed\n");
		exit(1);
	}

	//three way hand shake
	if( connect( soc_fd, (struct sockaddr* )&rem_soc_addr, sizeof(rem_soc_addr)) < 0){

		printf("Error: connection failed\n");
		exit(1);
	}
	
	//send
	char *senddata = argv[3];
	send( soc_fd, senddata, strlen(senddata), 0);
	
	//data buffer handling
	char buffer[256];
	memset( buffer, sizeof(buffer), 0);
	
	char *ptr = buffer;
	int max_len = sizeof(buffer);
	int len = 0;

	int n;
	while( (n = recv(soc_fd, ptr, max_len, 0)) > 0 ){

		ptr += n;
		max_len -= n;
		len += n;
	}

	printf("The echoed string is: %s\n", buffer);
}



	
