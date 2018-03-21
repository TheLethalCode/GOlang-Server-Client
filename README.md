# GOlang-Server-Client
This repo contains a server-side script and a client side script.

The server side is written in GOlang and the client side is written in C++.

The client sends a CSV file to the server. The server processes the CSV and extracts all the emails in the file and sends it back to the client. 

## Executing the program

### Running the server

Install the go tools by `sudo apt install golang`

Then for compiling `go run server.go`

### Running the client

This program uses the libcurl library for C++ for networking.

So install it by `sudo apt get libcurl3`

Then, compile the program by linking the library `g++ client.cpp -lcurl -o client`

If everything went fine, you should now have an executable.

Give the URL has the first argument and the filename as the second.

`./client 127.0.0.1:8000 Data.csv`

NOTE :- If you are using a localhost, don't forget to bypass proxy temporarily by `export http_proxy=''

If the csv file has emails, the program will print it.
