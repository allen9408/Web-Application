#include <stdio.h>/* perror(), fprintf(), sprintf() */
#include <stdlib.h>/* for atoi() */
#include <string.h>/* for memset() */
// #include <string>
#include <sys/socket.h> /* socket(), bind(), listen(), accept(),
                           recv(), send(), htonl(), htons() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <unistd.h>     /* for close() */
#define MAXPENDING 5    /* Max outstanding connection requests */
#define RCVBUFSIZE 256  /* Size of receive buffer */
#include <netdb.h>      /* for hostent, gethostbyname() */
#define ERR_EXIT(msg) { perror(msg); exit(1); }

int main(int argc, char *argv[]) {
	int rv_sock, s_sock, port_num, msg_len, tmp;
	int cut = 0;
	char buffer[RCVBUFSIZE];
	struct sockaddr_in serv_addr;
	unsigned h;
    if (argc != 2) {  /* Test for correct number of arguments */
        char msg[64];  
        memset((char *) &msg, 0, 64);
        sprintf(msg, "Usage: %s server_port\n", argv[0]);
        ERR_EXIT(msg);
	}

	rv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (rv_sock < 0) ERR_EXIT("ERROR opening socket"); 
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	port_num = atoi(argv[1]); /* First arg: server port num. */ 
	serv_addr.sin_family = AF_INET;
	// serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(port_num);
	if (bind(rv_sock,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		ERR_EXIT("ERROR on binding"); 
	if (listen(rv_sock, MAXPENDING) < 0)
	    ERR_EXIT("ERROR on listen");
	
	while ( 1 ) { /* Server runs forever */ 
		fprintf(stdout, "\nWaiting for client to connect...\n"); 
		s_sock = accept(rv_sock, NULL, NULL);
		if (s_sock < 0) ERR_EXIT("ERROR on accept new client"); 
		while (cut == 0) {
			memset(buffer, 0, RCVBUFSIZE);
			msg_len = recv(s_sock, buffer, RCVBUFSIZE - 1, 0); 
			if (msg_len < 0)
		        ERR_EXIT("ERROR reading from socket");
		    fprintf(stdout, "Client's message: %s\n", buffer);
		    // fprintf(stdout, "Message Length: %d\n", msg_len);

		    if (strncmp(buffer, "BOUNCE ", 7) == 0) {
		    	/* Received BOUNCE */
		    	char buf[RCVBUFSIZE];
		    	for (int i = 7; i < RCVBUFSIZE; i++) {
		    		buf[i-7] = buffer[i];
		    	}
		    	msg_len = send(s_sock, buf, strlen(buf), 0);
		    	if (msg_len < 0)
		    		ERR_EXIT("ERROR writing to socket");
		    } else if (strncmp(buffer, "EXIT ", 5) == 0) {
		    	/* Received exit with code */
		    	char buf[RCVBUFSIZE];
		    	for (int i = 5; i < RCVBUFSIZE; i++) {
		    		buf[i-5] = buffer[i];
		    	}
		    	fprintf(stdout, "Client exit with code %s\n", buf);
		    	close(s_sock);
		    	exit(0);
		    } else if (strcmp(buffer, "EXIT\n") == 0) {
		    	/* received exit */
		    	fprintf(stdout, "Client exit\n");
		    	close(s_sock);
		    	exit(0);
		    } else if (strncmp(buffer, "GET ",4) == 0) {
		    	/* Get file */
		    	char filename[RCVBUFSIZE];
		    	char buf[RCVBUFSIZE];
		    	for (int i = 4; i < msg_len - 1; i++) {
		    		filename[i-4] = buffer[i];
		    	}
		    	FILE* file;
				fprintf(stdout, "Finding %s\n", filename);		    	
		    	file = fopen(filename, "rt");
				fprintf(stdout, "File opened %s\n", filename);		    			    	
		    	if (!file) {
		    		/* file not accessable */
		    		fprintf(stdout, "file error %s\n", filename);

			    	msg_len = send(s_sock, "ERROR: file not exists", 22, 0);
			    	if (msg_len < 0)
			    		ERR_EXIT("ERROR writing to socket");
			    	msg_len = recv(s_sock, buf, RCVBUFSIZE - 1, 0);
			    	if (msg_len < 0)
			    		ERR_EXIT("ERROR reading from socket");

			    	msg_len = send(s_sock, "-1", 2, 0);
		    		if (msg_len < 0)
		    			ERR_EXIT("ERROR writing to socket");
			    	msg_len = recv(s_sock, buf, RCVBUFSIZE - 1, 0);
			    	if (msg_len < 0)
			    		ERR_EXIT("ERROR reading from socket");
		    	} else {
		    		fprintf(stdout, "Start to transmit %s\n", filename);
		    		/* Start to transmit file */
		    		while(fgets(buf, RCVBUFSIZE, file)) {
		    			msg_len = send(s_sock, buf, strlen(buf), 0);
		    			if (msg_len < 0)
		    				ERR_EXIT("ERROR writing to socket");
				    	msg_len = recv(s_sock, buf, RCVBUFSIZE - 1, 0);
				    	if (msg_len < 0)
				    		ERR_EXIT("ERROR writing to socket");
		    		} 
		    		/* End of transmit */
			    	msg_len = send(s_sock, "-1", 2, 0);
		    		if (msg_len < 0)
		    			ERR_EXIT("ERROR writing to socket");		    		
			    	msg_len = recv(s_sock, buf, RCVBUFSIZE - 1, 0);
			    	if (msg_len < 0)
			    		ERR_EXIT("ERROR writing to socket");
		    	}
		    } else {
		    	msg_len = send(s_sock, "ERROR: unrecognized command", 26, 0);
		    	if (msg_len < 0)
		    		ERR_EXIT("ERROR writing to socket");
		    }
		    // msg_len = send(s_sock, "I got your message", 18, 0); 
		    // if (msg_len < 0) 
		    // 	ERR_EXIT("ERROR writing to socket"); 
		}
	    close(s_sock);
	}
    /* NOT REACHED, because the server runs forever */
}