#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void main(int argc, char *argv[]) {
	int sockfd, client_sockfd, client_length, i, port_list[256], client_count = 0;
	char buffer[256], ip_list[256][16];
	struct sockaddr_in server_address, client_address;

	// Argument Check
	if (argc != 2) {
		printf("Invalid arguments!\n");
		return;
	}

	// Server Socket Address Initialization
	server_address.sin_family = AF_INET;             // IPv4
	server_address.sin_port = htons(atoi(argv[1]));  // Server Port
	server_address.sin_addr.s_addr = INADDR_ANY;     // Server IP Address

	// Server Socket Initialization
	sockfd = socket(AF_INET, SOCK_STREAM, 0);  // AF_INET: IPv4 - SOCK_STREAM: TCP
	if (sockfd < 0) {
		printf("Can't open socket!\n");
		return;
	}

	// Server Socket Binding
	if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
		printf("Can't bind socket!\n");
		return;
	}

	// Start listening to socket for clients.
	listen(sockfd, 5);
	client_length = sizeof(client_address);
	printf("\nServer Listening...\n");

	while (1) {
		// Accept pending connection from server socket queue.
		// New socket is made for the client, client info is stored in client_address.
		client_sockfd = accept(sockfd, (struct sockaddr *)&client_address, &client_length);
		if (client_sockfd < 0) {
			printf("Can't establish connection with client!\n");
			return;
		}
		printf("Incoming TCP connection.\n");

		// Clear buffer and read from the client socket to the buffer.
		bzero(buffer, 256);
		if (read(client_sockfd, buffer, 255) < 0) {
			printf("Can't read from client socket!\n");
			return;
		}
		
		// Identify command and do stuff.
		if (!strcmp(buffer, "addme")) {
			int found = 0;
			// Store client's IP address in dots/numbers format in buffer.
			inet_ntop(AF_INET, &client_address.sin_addr, buffer, 256);
			// Search client list for already existing clients.
			for (i = 0; i < client_count; i++)
			{
				// If client exists update ephemeral port.
				if (!strcmp(ip_list[i], buffer)) {
					port_list[i] = client_address.sin_port;
					found = 1;
					break;
				}
			}
			// If client doesn't exist add to list.
			if (!found) {
				bzero(ip_list[client_count], 16);
				inet_ntop(AF_INET, &client_address.sin_addr, ip_list[client_count], 16);
				port_list[client_count] = client_address.sin_port;
				client_count++;
			}
		}
		else if (!strcmp(buffer, "listclients")) {
			// Send every listed client to the client.
			for (i = 0; i < client_count; i++)
			{
				bzero(buffer, 256);
				sprintf(buffer, "   %d.   IP: %s Port: %d\n", i+1, ip_list[i], port_list[i]);
				if (write(client_sockfd, buffer, strlen(buffer)) < 0) {
					printf("Can't write to client socket!\n");
					return;
				}
			}
		}
		else if (!strcmp(buffer, "removeme")) {
			inet_ntop(AF_INET, &client_address.sin_addr, buffer, 256);
			// Search for the client in the list, swap with the last and decrease list size.
			for (i = 0; i < client_count; i++)
			{
				if (!strcmp(ip_list[i], buffer)) {
					strcpy(ip_list[i], ip_list[client_count - 1]);
					port_list[i] = port_list[client_count - 1];
					client_count--;
					break;
				}
			}
		}

		// Close client socket.
		close(client_sockfd);
	}

	return;
}