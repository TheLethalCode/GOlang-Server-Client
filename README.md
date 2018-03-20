# GOlang-Server-Client
This repo contains a server-side script and a client side script.

The server side is written in GOlang and the client side is written in C++.

The client sends a CSV file to the server. The server processes the CSV and extracts all the emails in the file and sends it back to the client. 

The client program accepts two arguments. The server URL and the file name. 

You have to link the libcurl library while compiling.
