#include <stdio.h>/* for perror(), fprintf(), sprintf() */
#include <stdlib.h>/* for atoi() */
#include <string.h>/* for memset(), memcpy(), strlen() */
#include <sys/socket.h> /* for sockaddr, socket(), connect(),
                           recv(), send(), htonl(), htons() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <netdb.h>      /* for hostent, gethostbyname() */
#include <unistd.h>     /* for close() */
#define RECVBUFSIZE 256 /* Size of receive buffer */
#define ERR_EXIT(msg) { perror(msg); exit(1); }
int main(int argc, char *argv[]) { 
	int c_sock, port_num, msg_len; 
	int cut = 0;
	struct sockaddr_in serv_addr; 
	struct hostent *serverIP; 
	char buffer[RECVBUFSIZE];
	unsigned long h;
    if (argc != 3) {   /* Test for correct number of arguments */
        char msg[64];  
        memset((char *) &msg, 0, 64);  /* erase */
        sprintf(msg, "Usage: %s serv_name serv_port\n", argv[0]);
        ERR_EXIT(msg);
	}
	// serverIP = gethostbyname(argv[1]); /* 1st arg: server name */ 
	// printf("serverIP_name: %s\n", serverIP->h_name);
	// h = get_hostIPaddr(argv[1]);
	// printf("%lu\n", h);

	// if (serverIP == NULL)
	// 	ERR_EXIT("ERROR, server host name unknown");
	// char ip_addr[1024] = argv[1];
	port_num = atoi(argv[2]); /* Second arg: server port num. */ 
	c_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (c_sock < 0) 
		ERR_EXIT("ERROR opening socket"); 
	memset((char *) &serv_addr, 0, sizeof(serv_addr)); 
	serv_addr.sin_family = AF_INET;
	// memcpy((char *) &serv_addr.sin_addr.s_addr,
	// 	(char *) &(serverIP->h_addr), serverIP->h_length); 
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(port_num);

	if (connect(c_sock,
		(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		ERR_EXIT("ERROR connecting");
	
	while (!cut) {
		int isCorrect = 0;
		do {
			fprintf(stdout, "\nUser, enter your message: "); 
			memset(buffer, 0, RECVBUFSIZE); /* erase */ 
			fgets(buffer, RECVBUFSIZE, stdin); /* read input */ 			
			if (!(strncmp(buffer, "GET ", 4) ==0 || strncmp(buffer, "EXIT ", 5)== 0
				|| strncmp(buffer, "BOUNCE ", 6)== 0 || strcmp(buffer, "EXIT\n")== 0)) {
				/* Incorrect command*/
				isCorrect = 0;
				fprintf(stdout, "Incorrect command: %s\n", buffer);
			} else {
				isCorrect = 1;
			}
		} while(!isCorrect);
		

		/* Send Request */
		msg_len = send(c_sock, buffer, strlen(buffer), 0); 
		if (msg_len < 0) 
			ERR_EXIT("ERROR writing to socket"); 
		
		if (strcmp(buffer, "EXIT\n") == 0 || strncmp(buffer, "EXIT ", 5) == 0) {
			fprintf(stdout, "Exit\n");
			close(c_sock);
			exit(0);
		}
		if (strncmp(buffer, "GET ", 4) == 0) {
			/* get file context */
			char buf[RECVBUFSIZE];
			while (strcmp(buffer, "-1") != 0){
				/* clear buffer */
				memset(buffer, 0, RECVBUFSIZE);
				msg_len = recv(c_sock, buffer, RECVBUFSIZE - 1, 0);
				if (msg_len < 0) 
					ERR_EXIT("ERROR reading from socket");
				// ACK
				msg_len = send(c_sock, "get context", 11, 0); 
				if (msg_len < 0) 
					ERR_EXIT("ERROR writing to socket");
				if (strcmp(buffer, "-1") == 0)
					break;
				else
					fprintf(stdout, "%s", buffer); 
			}
		} else {
			/* clear buffer */
			memset(buffer, 0, RECVBUFSIZE);
			msg_len = recv(c_sock, buffer, RECVBUFSIZE - 1, 0);
			if (msg_len < 0) 
				ERR_EXIT("ERROR reading from socket"); 
			fprintf(stdout, "%s\n", buffer); 
		}
	}
	close(c_sock);
	exit(0);
}