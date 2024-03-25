#! /usr/bin/python
# a simple tcp client
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('127.0.0.1', 6969))
# sock.send('Test\n')
# sock.send(raw_input("Please input : "))

gameName = "NewGame"
for i in range(248):
    gameName +=('\0')

# Query for game
vb = bytes(gameName,  'ascii')
s = sock.send(vb)

# Start
r = sock.recv(1)

if int.from_bytes(r, "big") != 1:
    sock.close()
    exit()

# Game Command
r = sock.recv(1)
print('Recieved Game command')
print(r)

sock.close()
