import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

from_addr='Sentfrom' # ชื่อที่ส่งไปหาผู้รับ
to_addr=['Sendto@gmail.com'] # email ผู้รับ
msg=MIMEMultipart()

msg['From']=from_addr
msg['To']=" ,".join(to_addr)
msg['subject']='header' # หัวข้อเรื่อง

body='content' # เนื้อหาภายใน

msg.attach(MIMEText(body,'plain'))

email='example@gmail.com' # email ผู้ส่ง
password='examplepassword' 
# password สามารถไปสร้างได้ที่ google account --> รหัสผ่านสำหรับแอป
# ตัวอย่างรหัส dhry quxy wcys ande

mail=smtplib.SMTP('smtp.gmail.com',587)
mail.ehlo()
mail.starttls()
mail.login(email,password)
text=msg.as_string()
mail.sendmail(from_addr,to_addr,text)
mail.quit()