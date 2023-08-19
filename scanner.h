typedef struct {
	int port; // The specific port to scan
	char *ip; // IP address to scan	
} Scan_info;

void thread_timeout(int signal); void *scanner(void *port_thread);
