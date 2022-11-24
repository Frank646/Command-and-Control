import socket
# Socket Library

import threading
# Threading Library

PORT = 4444
# Free Port

server = socket.gethostbyname(socket.gethostname())
# Obtains IP address for the server
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# creates a new socket
address = (server, PORT)
server.bind(address)


FORMAT ="utf-8"

clients, names = [], []
# Will list all clients connected


def ChatS():
# starts connection to server

    server.listen()

    while True:

        conn, addr = server.accept()
        conn.send("NAME".encode(FORMAT))
    # accepts connections and bounds addresses

        name = conn.recv("2048").decode("FORMAT")
        # represents the max amount of data received

        names.append(name)
        clients.append(conn)

        print(f"Name is :{name}")

        broadcastMessage(f"{name} has joined the chat!".encode(format))

        conn.send('connection successful').encode(format))

        thread = threading.Thread(target = handle, args = (conn, addr))
        # Thread Handling
        thread.start()


        print(f"activate connections {threading.activeCount()-1}")

def handle(conn, addr);

    print(f"new connection {addr}")
    conneected = True

    while connected:

        message = conn.recv(2048)
        # recieve message
        broadcastMessage(message)
        # broadcast message
    conn.close()
    # closes connection


def broadcastMessage(message):
    for client in clients:
        client.send(message)


















