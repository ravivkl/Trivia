import socket

SERVER_IP = '127.0.0.1'
PORT = 8826
LOG_IN_CODE = "200"
EXIT_CODE = "208"

# Create socket
def openSock():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((SERVER_IP, PORT))

    size = '6'
    msg = LOG_IN_CODE + size + "hello!"
    sock.sendall(msg.encode())


    server_msg = sock.recv(1024)
    server_msg = server_msg.decode()

    size = '4'
    exmsg = EXIT_CODE + size + "bye!"
    sock.sendall(exmsg.encode())
    sock.close()

    print(server_msg)


openSock()




