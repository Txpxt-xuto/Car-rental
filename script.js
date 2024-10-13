/*navbar*/
const bar = document.getElementById('bar')
const nav = document.getElementById('navbar')
const close = document.getElementById('close')

const express = require('express')
const app = express();
const nodemailer = require('nodemailer')

app.listen(3000, () => {
    console.log('Node app is runnind on port 3000')
})

if(bar){
  bar.addEventListener('click',() => {
    nav.classList.add('active');
  })
}

if(close){
  close.addEventListener('click',() => {
    nav.classList.remove('active');
  })
}

const items = document.querySelectorAll(".accordion button");

function toggleAccordion() {
  const itemToggle = this.getAttribute('aria-expanded');
  
  for (i = 0; i < items.length; i++) {
    items[i].setAttribute('aria-expanded', 'false');
  }
  
  if (itemToggle == 'false') {
    this.setAttribute('aria-expanded', 'true');
  }
}

items.forEach(item => item.addEventListener('click', toggleAccordion));