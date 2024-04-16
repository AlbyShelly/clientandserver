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
