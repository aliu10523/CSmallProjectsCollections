#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#define BUFFER_SIZE 4096
const char *msg = "Congratulations, you've successfully received a message from the server!\n";

int startServer(int port) {

	// create an address structure: IPv4 protocol, any IP address, on given port
	// note: htonl and htons are endian converters, essential for Internet communication
	struct sockaddr_in ipOfServer;
	memset(&ipOfServer, 0, sizeof(struct sockaddr_in));
	ipOfServer.sin_family = AF_INET;
	ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
	ipOfServer.sin_port = htons(port);

	// we'll have one socket that waits for other sockets to connect to it
	// those other sockets will be the ones we used to communicate
	int listener = socket(AF_INET, SOCK_STREAM, 0);

	// and we need to tell the OS that this socket will use the address created for it
	bind(listener, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));

	// wait for connections; if too many at once, suggest the OS queue up 20
	listen(listener , 20);

	printf("The server is now listening on port %d\n", port); // and listening port

	
	// get a connection socket (this call will wait for one to connect)
	int connection = accept(listener, (struct sockaddr*)NULL, NULL);
	

	// unreachable code, but still have polite code as good practice
	close(listener);

	return connection;
}

int startClient(char *IPAddress , int port){

        int sock;
        struct sockaddr_in server;
        char message[BUFFER_SIZE];

        /*
           Initalize struct sockaddr_in to contain IP address and port number of server.
           Remember to read values from argv. (You also need to convert it from
           a string to an int, so the atoi function is very helpful)
           */
        server.sin_addr.s_addr = inet_addr(IPAddress);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        //Create Socket  (Remember to check the return value to see if an error occured)
        sock = socket(AF_INET, SOCK_STREAM, 0);

        //Connect to Remote server
        int status = connect(sock, (struct sockaddr *)&server, sizeof(server));
        if (status == -1) {
                printf("Connection unsuccesful");
                return -1;
        }

        //Close socket and free anything you malloced
        return sock;
}

int chat(int sock) {
	struct pollfd fds[2];

	fds[0].fd = 0; //stdin
	fds[0].events = POLLIN;

	fds[1].fd = sock;
	fds[1].events = POLLIN;
	
	char buffer[BUFFER_SIZE];
	while (1) {
		int ret = poll(fds, 2, 60000); // minute timeout
		if (ret > 0 ) {
			// check for standard input
			if (fds[0].revents & POLLIN) {
				memset(buffer, 0, BUFFER_SIZE);
				int temp = read(0, buffer, BUFFER_SIZE);
				if (temp != 0 && temp != -1) {
					write(sock, buffer, temp);
				}
			}

			// check for socket input
			if (fds[1].revents & POLLIN) {
				memset(buffer, 0, BUFFER_SIZE);
				int temp = read(sock, buffer,BUFFER_SIZE);
				if (temp != 0 && temp != -1) { 
					write(1, buffer, temp);
				}
			}

		}
	}
	return 0;
}


int main(int argc, char *argv[]) {
	int sock;
	if (argc < 3) {
		// call server
		if (argc == 2) {
			sock = startServer(atoi(argv[1]));
		}
		else {
			// start by getting a random port from the ephemeral port range
			srandom(getpid()); // random seed based on this process's OS-assigned ID
			int port = 0xc000 | (random()&0x3fff); // random element of 49152–65535
			sock = startServer(port);
		}
	}
	else {
		sock = startClient(argv[1], atoi(argv[2]));
	}	

	chat(sock);
	close(sock);
	return 0;
}
