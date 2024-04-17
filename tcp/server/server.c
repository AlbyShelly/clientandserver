#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

int main( void ){

	//create local server address
	struct sockaddr_in loc_soc_addr;
	memset( &loc_soc_addr, 0, sizeof(loc_soc_addr) );
	loc_soc_addr.sin_family = AF_INET;
	loc_soc_addr.sin_port = htons(PORT);
	loc_soc_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int lis_soc_fd = socket(PF_INET, SOCK_STREAM, 0);
	if( lis_soc_fd < 0){

		printf("Error: Listen socket failed\n");
		exit(1);
	}

	//bind lis_soc to address
	int bind_res = bind(lis_soc_fd, &loc_soc_addr, sizeof(loc_soc_addr) );
	if( bind_res < 0){
		
		printf("Error: Binding failed\n");
		exit(1);
	}
	
	//listening for connection
	int wait_size = 16;

	if(listen(lis_soc_fd, wait_size) < 0){

		printf("Error: listening failed");
		exit(1);
	}

	//handle queued clients iteratively
	while(1){
		
		//client details buffer
		struct sockaddr_in rem_soc_addr;
		int rem_soc_addr_len;
		
		//create a serving socket
		int soc_fd;
		if(soc_fd = accept( lis_soc_fd, &rem_soc_addr, &rem_soc_addr_len) < 0){

			printf("Error: socket creation failed");
			exit(1);
		}

		//data buffer
		char buffer[256];
		char* ptr = buffer; //next write ptr
		int max_len = sizeof(buffer); //max write ptr
		int len;

		//Data transfer
		int n;
		while( (n = recv(soc_fd, ptr, max_len, 0)) > 0 ){

				ptr += n;
				max_len -= n;
				len +=n;
		}

		//send data
		send( soc_fd, buffer, len, 0);

		close(soc_fd);
	}
}
