# port-scanner

This is a basic port scanner implemented in C using library functions for the socket programming and threads to complete the scanning. 

It accepts 3 arguments:

-i: specifies the ipv4 address to scan (required)

-p: specifies the range of ports that should be scanned; formatted like "min_port:max_port" or just "port" 

-o: the path of the file to output to if not the terminal (optional - defaults to stdout)


