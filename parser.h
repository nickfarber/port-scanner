typedef struct {
	char *ip;
	int min_port;
	int max_port;
	char *file;
} Argument;

void *parse_arguments(int argc, char *argv[]);
