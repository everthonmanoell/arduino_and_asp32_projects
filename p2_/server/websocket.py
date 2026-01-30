import socket
import sys
import time

import json

#Access file with logins
with open("server/logins.json", "r") as file:
     users:dict = json.load(file)

#Configure server connection
mysock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)
print(local_ip)

try:
    mysock.bind((local_ip,80)) #Associates a created socket with a specific IP address and port number on the local host
    
except socket.error:
    print("Failed to bind")
    sys.exit()
    
mysock.listen() #Listen to requests

while True:
    conn,addr = mysock.accept()
    data = conn.recv(1000) #Receive requests

    time.sleep(3)
    
    if not data:
        break
    
    print("Got a request!!!")
    
    #Captures information sent by the customer
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
          
    
    #Sends a response to the customer
    conn.sendall(bytes(message,"utf-8"))

#Close the connection.    
conn.close()
mysock.close()