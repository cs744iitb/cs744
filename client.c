#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char hello[100];
	char buffer[2048] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
 //Convert IPv4 and IPv6 addresses from text to binary form
 	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	 {
 		printf("\nInvalid address/ Address not supported \n");
 		return -1;
	 }
 	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
 	{
 		printf("\nConnection Failed \n");
 		return -1;
	 }

	valread = read( sock , buffer, 2048);
 	printf("%s\n",buffer );
	gets(hello);
	
	while(1)
	{
	if(hello!="exit")
	{	send(sock , hello , strlen(hello) , 0 );
 		printf("message sent\n");
 		valread = read( sock , buffer, 2048);
		if(valread < 0)
		{
	
			printf("Error in reading");
		}
 		printf("%s\n",buffer );
		gets(hello);
	}
	else
		exit(1);

	}

	return 0;
}
