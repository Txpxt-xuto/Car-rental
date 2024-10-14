import yagmail
yag = yagmail.SMTP(user="34850@sksc.ac.th",password="loveauto2022")

recipients = '34850@sksc.ac.th'
name = 'ซิปป้า'
subject = 'อีเมล์ตอบกลับอัตโนมัติด้วย Python'
body = f'เรียน {name},\n\nอีเมล์นี้เป็นอีเมล์อัตโนมัติทีส่งจากระบบ Python\n\nด้วยความเคารพ,\nซิปป้า Ultimate Python'
yag.send(to=recipients,subject=subject,contents=body)
























"""
import smtplib
from email.message import EmailMessage

msg = EmailMessage()

msg['subject'] = 'Never gonna give you up'
msg['From'] = 'toungsakul2@gmail.com'
msg['To'] = 'toungsakul2@gmail.com'

msg.set_content('Never gonna let you down. Never gonna run around and desert you.')

with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp:
    smtp.login('toungsakul2@gmail.com', 'loveauto2022')
    smtp.send_message(msg)








import smtplib 
from email.mime.multipart import MIMEMultipart 
from email.mime.text import MIMEText 


def send_email(sender_email,sender_password,recipient_email,subject,message): 

    # บอกให้ปลายทาง เมลผู้รับ รู้ว่าเราจะส่งเมลรูปแบบไหนไป text , image 
    msg = MIMEMultipart()

    msg.attach(MIMEText(message,'plain'))

    msg['From'] = sender_email 
    msg['To'] = recipient_email 
    msg['Subject'] = subject 

    # เริ่มส่งเมล 
    server = smtplib.SMTP('smtp.gmail.com',587)
    server.starttls()


    server.login(sender_email,sender_password)

    server.sendmail(sender_email,recipient_email,msg.as_string())

    server.quit()


if __name__ == '__main__': 
    
    sender_email = "toungsakul2@gmail.com"

    # App Password คนละตัวกับ Password ปกติที่เราใช้เข้าเมล

    # https://myaccount.google.com/apppasswords
    sender_password = "yegflqjhaopmbduh"

    recipient_email = "tapatauto9898@gmail.com"
    message = "ทดสอบการส่ง Email ด้วย Python"
    subject ="Python Email EP 1"

    send_email(sender_email,sender_password,recipient_email,subject,message) """