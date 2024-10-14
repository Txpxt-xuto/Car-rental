const express = require('express');
const app = express();
const nodemailer = require('nodemailer');

app.listen(3000, () => {
    console.log('Node app is running...');
})

app.post('/sendemail'), (req, res) =>{
    const transport = nodemailer.createTransport({
        service: 'gmail',
        auth:{
            user: '34850@sksc.ac.th',
            pass: "loveauto2022"
        }
    })
    const options = {
        form : '34850@sksc.ac.th',
        to : '34850@sksc.ac.th',
        subject : 'test',
        html: '<b>รักนะ</b>'
    };

    transporter.sendMail(options,function(err,info){
        if(err)
        {
            console.log('err',err);
            return res.status(200).json({
                RespCode: 400,
                RespMessage: 'bad',
                RespError: err
            })
        }else 
        {
            console.log('Send',+ info.response);
            return res.status(200).json({
                RespCode: 200,
                RespMessage: 'good',
                RespError: err
            })
        }
    });
}