function sendMail() {
    var params = {
        Name: document.getElementById("Name").value,
        SurName: document.getElementById("SurName").value,
        Email: document.getElementById("Email").value,
        Tel: document.getElementById("Tel").value,
        Start: document.getElementById("Start").value,
        End: document.getElementById("End").value,
    };

    const serviceID = "YOUR_SERVICE_ID";
    const templateID = "YOUR_TEMPLETE_ID";

    emailjs.send(serviceID, templateID, params)
    .then(res=>{
        document.getElementById("Name").value = "";
        document.getElementById("SurName").value = "";
        document.getElementById("Email").value = "";
        document.getElementById("Tel").value = "";
        document.getElementById("Start").value = "";
        document.getElementById("End").value = "";
        console.log(res);
        alert("Your message sent successfully!!")
    })
    .catch(err=>console.log(err));
}