import socket

class Client():
    #Configure client connection
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    hostname = socket.gethostname()
    local_ip = socket.gethostbyname(hostname)
    client.connect((local_ip, 8080))

    #Envia a requisição
    client.sendall(b"GET/0000")

    #Recebe resposta do servidor
    resposta = client.recv(1000)
    print("Resposta do servidor:", resposta.decode())

    #Close the connection.
    client.close()