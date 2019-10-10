# Simple-Chat-Program-Coded-in-C++
The program is invoked as follows:
Server side:
$./chat
Client side:
$./chat -p 3790 -s 192.168.47.232
Where the -p flag indicates the port to connect to and the -s flag indicates the IP address of your friend.
$./chat -h
Should produce a help message and exit.
Without any arguments, the chat program acts as a server, prints out the port it is listening on and waits for
a connection.
With arguments, the program acts as a client connects to a waiting server using the information provided.
With one argument, the program prints the help message and exits.
