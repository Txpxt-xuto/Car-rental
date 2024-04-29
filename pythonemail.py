import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

from_addr='auto'
to_addr=['nnrpwg10@gmail.com']
msg=MIMEMultipart()

msg['From']=from_addr
msg['To']=" ,".join(to_addr)
msg['subject']='just to check'

body='love u so much'

msg.attach(MIMEText(body,'plain'))

email='toungsakul2@gmail.com'
password='dhry quxy wcys ande'

mail=smtplib.SMTP('smtp.gmail.com',587)
mail.ehlo()
mail.starttls()
mail.login(email,password)
text=msg.as_string()
mail.sendmail(from_addr,to_addr,text)
mail.quit()