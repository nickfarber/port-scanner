#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

#include "scanner.h"
#include "parser.h"

/*
 * The main functionality of the scanner ran by the threads. They create a 
 * socket and try to connect that socket to the specified port. Returns 1 if
 * the port is open.
 */
void *scanner(void *port_thread) {
	Scan_info *scan_info = port_thread;
	int *outcome = malloc(sizeof(outcome));

	// Creating a socket
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	// Socket isn't created
	if (sock_fd == -1) {
		*outcome = -1;
	} 
	else {
		struct sockaddr_in address;
		memset(&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_port = htons(scan_info->port);
		address.sin_addr.s_addr = inet_addr(scan_info->ip);
	
		// Checking if the port is open
		if (connect(sock_fd, (struct sockaddr*)&address, sizeof(address)) == 0)
			*outcome = 1;
		
		else
			*outcome = 0;

    	close(sock_fd);
	}
	
	return outcome;
}

/*
 * Creates and runs the threads based on the arguments provided. Prints the 
 * results and frees memory at the end.
 *
 * Parameters are: 
 * -i: ip address to scan
 * -p: port range to scan
 * -o: path of file to write to 
 */
int main(int argc, char *argv[]) {
	Argument *args = parse_arguments(argc, argv); 	
	FILE *file = NULL;
	Scan_info *port_thread;
	// Checking if the arguments were acceptible
	if (args) {
		// Creating and running all threads
		for (int i = args->min_port; i <= args->max_port; i++) {
			pthread_t thread_id = i;
			port_thread = malloc(sizeof(Scan_info));
			port_thread->ip = malloc(strlen(args->ip) + 1);
			strcpy(port_thread->ip, args->ip);
			port_thread->port = i;
			pthread_create(&thread_id, NULL, scanner, port_thread);
		}
		
		if (args->file != NULL) 
			file = fopen(args->file, "w");
		
		// Closing all threads
		for (int i = args->min_port; i <= args->max_port; i++) {
			void *ret_val = 0;
			pthread_t thread_id = i;
			int *outcome = 0;
			pthread_join(thread_id, &ret_val);
			
			outcome = ret_val;
			
			// Checking if the port is open
			if (outcome && *outcome == 1) {
				if (file) 
					fprintf(file, "Port %d is open\n", i);
				else
					printf("Port %d is open\n", i);
			}
			if (outcome)
				free(outcome);
		}
		
		// Free all memory
		free(args->ip);
		if (file)
			free(args->file);
		free(args);
		free(port_thread->ip);
		free(port_thread);		
	}	

	return 0;	
}
