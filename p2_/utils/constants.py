import os
from dotenv import load_dotenv

load_dotenv()


SMTP_SERVER_GMAIL = 'smtp.gmail.com'
SMTP_PORT_TLS_GMAIL = 587
SMTP_PORT_SSL = 465
DEFAULT_SENDER = os.getenv("DEFAULT_SENDER")
DEFAULT_PASSWORD = os.getenv("DEFAULT_PASSWORD")
DEFAULT_RECIPIENT = "emsi@softex.cin.ufpe.br"
DEFAULT_RECIPIENT_2 = ""

if not DEFAULT_PASSWORD:
    raise ValueError("A senha não foi encontrada no arquivo .env!")