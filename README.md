# turbo-spoon
C++ Server - Client based application

This is a simple C++ project demonstrating basic client-server communication over a TCP connection using sockets.

The Server listens for incoming connections, receives order data from clients, prints it to the console, and sends a confirmation message back.

The Client connects to the server, lets the user input order details (name, amount, and date), sends this information to the server, and displays the server's response.

# How to build: 

Run make command.

This will create 2 files.

# How to start:

Run ./tcp_client and ./tcp_server separately.

# How to improve: 

! Store received orders in a local file or database

! Replace console-based form with a simple GUI or web interface

Implement basic error handling and input validation
