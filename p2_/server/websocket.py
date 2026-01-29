import socket
import sys
import time

import json

with open("server/logins.json", "r") as file:
     users:dict = json.load(file)


mysock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
hostname = socket. gethostname()
local_ip = socket. gethostbyname(hostname)
print(local_ip)

try:
    mysock.bind(('',80))
    
except socket.error:
    print("Failed to bind")
    sys.exit()
    
mysock.listen()

while True:
    conn,addr = mysock.accept()
    data = conn.recv(1000)

    time.sleep(3)
    
    if not data:
        break
    
    print("Got a request!!!")
    data = str(data,'UTF-8')
    
    if data.find("GET") != -1:
        indexOption = data.find("/") + 1
        
        user = users.get(data[indexOption:], "")
        
        if user != "":
          print("USUÁRIO AUTENTICADO") 
          print(user)
        
          message = user
          
        else:
             print("USUÁRIO NÃO EXISTE")
             message = ""
          
    
    conn.sendall(bytes(message,"utf-8"))
    
conn.close()
mysock.close()