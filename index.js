/*const express = require('express')
const app = express();
const nodemailer = require('nodemailer')

app.listen(3000, () => {
    console.log('Node app is runnind on port 3000')
})

app.post('/sendemail', (req,res) => {
    const transport = nodemailer.createTransport({
        service: 'gmail',
        auth: {
            user: 'tapatauto9898@gmail.com',
            pass: 'loveauto2022'
        }
    })

    const option = {
        from: 'tapatauto9898@gmail.com',
        to: 'toungsakul2@gmail.com',
        subject: 'auto',
        html: `
            <p>Hello world I'm from nodemailer</p>
        `
    }
    transporter.sendMail(option, (err, info) => {
        if(err) {
            console.log('err', err)
            return res.status(200).json({
                RespCode: 400,
                RespMessage: 'bad',
                RespError: err
            })
        }
        else {
            console.log('Send: ' + info.response)
            return res.status(200).json({
                RespCode: 200,
                RespMessage: 'good',
            })
        }
    })
})

module.express = app;*/
const nodemailer = require("nodemailer");

const transporter = nodemailer.createTransport({
  host: "smtp.ethereal.email",
  port: 587,
  secure: false, // Use `true` for port 465, `false` for all other ports
  auth: {
    user: "joel68@ethereal.email",
    pass: "EM2AakCcDVvJc4rXSf",
  },
});

// async..await is not allowed in global scope, must use a wrapper
async function main() {
  // send mail with defined transport object
  const info = await transporter.sendMail({
    from: 'joel68@ethereal.email', // sender address
    to: "toungsakul2@gmail.com", // list of receivers
    subject: "Hello ✔", // Subject line
    text: "Hello world?", // plain text body
    html: "<b>Hello world?</b>", // html body
  });

  console.log("Message sent: %s", info.messageId);
  // Message sent: <d786aa62-4e0a-070a-47ed-0b0666549519@ethereal.email>
}

main().catch(console.error);