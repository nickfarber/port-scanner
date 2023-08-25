#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"

/* This function will parse the command line arguments for main()
 * and return an Argument struct containing the ip address, ports
 * to scan, and the output file if specified.
 */
void *parse_arguments(int argc, char *argv[]) {
	Argument *arguments = NULL;
		
	// Checking if no arguments were passed
	if (argc < 4) {
		printf("Parameters are:\n-i: IP address to scan \n-p: \"x:y\"port(s) to scan\n"); 
		printf("-o: file path to write to\n");
	}
	else {
		// IP address is necessary
		if (strcmp(argv[1], "-i") == 0) {
			arguments = malloc(sizeof(Argument));
			arguments->file = 0;
			arguments->ip = malloc(strlen(argv[2]) + 2);
			strcpy(arguments->ip, argv[2]); 
		}
		
		// Port range is necessary
		if (argc > 3 && strcmp(argv[3], "-p") == 0) {
			char *token = strtok(argv[4], ":");
			int port_min;
			int port_max;
			
			// Getting the integers for the range
			if (token) {
				port_min = atoi(token);
				token = strtok(NULL, ":");
				if (token) 
					port_max = atoi(token);
				else
					port_max = port_min;
			}
			
			arguments->min_port = port_min;
			arguments->max_port = port_max;
		}	

		// Checking if a file will be written to
		if (argc > 5 && strcmp(argv[5], "-o") == 0) {
			arguments->file = malloc(strlen(argv[6]) + 1);
			strcpy(arguments->file, argv[6]);
		}
	}
	
	return arguments;
}


