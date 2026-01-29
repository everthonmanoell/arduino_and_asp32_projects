import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from constants import DEFAULT_SENDER, DEFAULT_PASSWORD, DEFAULT_RECIPIENT, SMTP_PORT_TLS_GMAIL, SMTP_SERVER_GMAIL

def SendEmail(
    remetente_email: str,
    remetente_senha: str,
    destinatario_email: str,
    assunto: str,
    corpo_mensagem: str,
    smtp_server: str = SMTP_SERVER_GMAIL,
    smtp_port: int = SMTP_PORT_TLS_GMAIL
):
    """
    Função genérica para envio de e-mails via SMTP.
    """
    # Configuração da Mensagem (MIME)
    msg = MIMEMultipart()
    msg['From'] = remetente_email
    msg['To'] = destinatario_email
    msg['Subject'] = assunto

    # Anexa o corpo do e-mail (Texto Plano)
    msg.attach(MIMEText(corpo_mensagem, 'plain'))

    try:
        # Criação do objeto SMTP
        server = smtplib.SMTP(smtp_server, smtp_port)
        # Identificação do Servidor
        server.ehlo()
        
        # Criptografia TLS (Segurança)
        server.starttls()
        # Re-identificação do Servidor
        server.ehlo()

        # Login
        server.login(remetente_email, remetente_senha)

        # Envio
        text = msg.as_string()
        server.sendmail(remetente_email, destinatario_email, text)
        
        # Fechamento da conexão
        server.quit()
        print(f"✅ E-mail enviado com sucesso para: {destinatario_email}")
        return True

    except smtplib.SMTPAuthenticationError:
        print("❌ Erro de Autenticação: Verifique seu e-mail e senha (ou App Password).")
    except Exception as e:
        print(f"❌ Erro ao enviar e-mail: {e}")
    
    return False

# --- BLOCO DE EXECUÇÃO (EXEMPLO) ---
if __name__ == "__main__":
    print("--- Sistema de Envio de E-mail ---")
    
    
    meu_email = DEFAULT_SENDER
    minha_senha = DEFAULT_PASSWORD
    email_destino = DEFAULT_RECIPIENT
    assunto_msg = "Teste de Refatoração"
    mensagem = "Olá, este é um e-mail enviado pelo código refatorado e genérico."

    SendEmail(
        remetente_email=meu_email,
        remetente_senha=minha_senha,
        destinatario_email=email_destino,
        assunto=assunto_msg,
        corpo_mensagem=mensagem
        
    )