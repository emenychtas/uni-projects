#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void main(int argc, char *argv[]) {
	int sockfd;
	char buffer[1024];
	struct sockaddr_in server_address;

	// Argument Check
	if (argc != 3) {
		printf("Invalid arguments!\n");
		return;
	}

	// Server Socket Address Initialization
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[2]));
	server_address.sin_addr.s_addr = inet_addr(argv[1]);

	// Command Input Loop
	while (1) {
		printf("\nGive command: ");
		bzero(buffer, 1024);
		fgets(buffer, 1023, stdin);
		buffer[strcspn(buffer, "\n")] = 0;

		if (!strcmp(buffer, "exit")) {
			return;
		}
		else if (strcmp(buffer, "addme") && strcmp(buffer, "listclients") && strcmp(buffer, "removeme")) {
			printf("Invalid command!\n");
		}
		else {
			// Create a socket.
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
			if (sockfd < 0) {
				printf("Can't open socket!\n");
				return;
			}

			// Establish a connection with the server.
			if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
				printf("Can't connect to server!\n");
				return;
			}

			// Send command to server.
			if (write(sockfd, buffer, strlen(buffer)) < 0) {
				printf("Can't write to socket!\n");
				return;
			}

			// Print server's response if needed.
			if (!strcmp(buffer, "listclients")) {
				bzero(buffer, 1024);
				read(sockfd, buffer, 1023);
				printf("%s", buffer);
			}

			// Close socket.
			close(sockfd);
		}
	}

	return;
}