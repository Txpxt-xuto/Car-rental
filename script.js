/*navbar*/
const bar = document.getElementById('bar')
const nav = document.getElementById('navbar')
const close = document.getElementById('close')


const BASE = "http://localhost:5000";

document.getElementById("form").addEventListener("submit", async (e) => {
    e.preventDefault();
    const msg = document.getElementById("msg");

    const data = {
        firstname: document.getElementById("Name").value,
        lastname:  document.getElementById("SurName").value,
        phone:     document.getElementById("Tel").value,
        email:     document.getElementById("Email").value,
        start:     document.getElementById("Start").value,
        end:       document.getElementById("End").value,
        delivery:  document.getElementById("checkyes").checked ? "ใช่" : "ไม่",
    };

    try {
        const res = await fetch(`${BASE}/save`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(data),
        });
        const result = await res.json();
        if (result.success) {
            msg.style.color = "green";
            msg.textContent = "บันทึกสำเร็จ!";
            document.getElementById("form").reset();
        } else {
            throw new Error(result.error);
        }
    } catch (err) {
        msg.style.color = "red";
        msg.textContent = "เกิดข้อผิดพลาด: " + err.message;
    }
});

function exportCSV() {
    window.open(`${BASE}/export`, "_blank");
}







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





/* Endless Scrolling Cards */
let holder = document.querySelectorAll('.containerofslide')[0],
  cards = document.querySelectorAll('.cardofslide');

let preActiveCard = cards[1];
let nextActiveCard = cards[2];

function scrollLeft() {
  holder.classList.remove('nextofslide');
  holder.classList.remove('resetofslide');
  holder.classList.add('nextofslide');
  
  preActiveCard.classList.remove('activeofslide');
  nextActiveCard.classList.add('activeofslide');
  setTimeout(reset, 600);
}

function reset() {
  holder.classList.remove('nextofslide');
  holder.classList.add('resetofslide');
  preActiveCard.classList.add('activeofslide');
  nextActiveCard.classList.remove('activeofslide');
}

setInterval(scrollLeft, 1500);
