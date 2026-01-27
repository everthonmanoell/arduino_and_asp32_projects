import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart


#try:
msgTo = str(input("Informe o e-mail de destino: "))
smtpObj = smtplib.SMTP('smtp-mail.outlook.com', 587)
smtpObj.ehlo()
smtpObj.starttls()
msgFrom = 'email@dominio'
fromPass = 'senha'
#smtpObj.ehlo()
smtpObj.login(msgFrom, fromPass)
msg = MIMEMultipart("alternative")
msg["Subject"] = "Mais um teste"
msg["From"] = msgFrom
msg["To"] = msgTo
text = """ Finalmente enviando o corpo do email"""
part1 = MIMEText(text,"plain")
msg.attach(part1)
smtpObj.sendmail(msgFrom,msgTo,msg.as_string())
smtpObj.quit()
print("Email enviado com sucesso!")
#except:
		#print("Erro ao enviar e-mail")
