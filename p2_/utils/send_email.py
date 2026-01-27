import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import getpass # Para ocultar a senha ao digitar no terminal
from constants import SMTP_SERVER, SMTP_PORT_TLS, DEFAULT_SENDER, DEFAULT_PASSWORD, DEFAULT_RECIPIENT

def enviar_email_generico(
    remetente_email: str,
    remetente_senha: str,
    destinatario_email: str,
    assunto: str,
    corpo_mensagem: str,
    smtp_server: str = 'smtp-mail.outlook.com',
    smtp_port: int = 587
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
        server.ehlo()
        
        # Criptografia TLS (Segurança)
        server.starttls()
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
    
    # Coleta de dados (pode vir de um banco de dados ou input)
    meu_email = input("Seu e-mail: ")
    # getpass esconde a senha enquanto você digita
    minha_senha = getpass.getpass("Sua senha (ou App Password): ") 
    email_destino = input("E-mail de destino: ")
    assunto_msg = "Teste de Refatoração"
    mensagem = "Olá, este é um e-mail enviado pelo código refatorado e genérico."

    # Chamada da função
    # Nota: Se for Gmail, mude o smtp_server para 'smtp.gmail.com'
    enviar_email_generico(
        remetente_email=meu_email,
        remetente_senha=minha_senha,
        destinatario_email=email_destino,
        assunto=assunto_msg,
        corpo_mensagem=mensagem
        # smtp_server e port usam o padrão do Outlook definido na função
    )