import os
import socket
import sys
import time
from datetime import datetime

# Add parent directory to path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import json

from utils.constants import DEFAULT_PASSWORD, DEFAULT_RECIPIENT, DEFAULT_SENDER
from utils.send_email import SendEmail

#Access file with logins
with open("store/logins.json", "r") as file:
     users:dict = json.load(file)

#Configure server connection
mysock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)
print(local_ip)

try:
    mysock.bind((local_ip,8080)) #Associates a created socket with a specific IP address and port number on the local host
    
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
    
    #Captures information sent by the customercdc
    data = str(data,'UTF-8')
    
    if data.find("GET") != -1:
        indexOption = data.find("/") + 1
        
        user = users.get(data[indexOption:], "")
        
        if "error2times" != user and user != "":
            print("USUÁRIO AUTENTICADO") 
            print(user)
            message = user
        elif user == "error2times":
            print("ERRO 2 VEZES")
            now = datetime.now()
            hour_fomatted = now.strftime("%d/%m/%y às %H:%H:%S")
            SendEmail(
                remetente_email=DEFAULT_SENDER,
                remetente_senha=DEFAULT_PASSWORD,
                destinatario_email=DEFAULT_RECIPIENT,
                assunto="ALERTA DE LOGIN FALHO",
                corpo_mensagem= f"HOUVE 2 TENTATIVAS DE LOGIN FALHAS NO DIA E HORÁRIO: {hour_fomatted}")
            message = user
        else:
            print("USUÁRIO NÃO EXISTE")
            message = "USUÁRIO NÃO EXISTE OU SENHA INVÁLIDA"
          
    
    #Sends a response to the customer
    conn.sendall(bytes(message,"utf-8"))

    #Close the connection.    
    conn.close()

mysock.close()