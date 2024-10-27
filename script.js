/*navbar*/
const bar = document.getElementById('bar')
const nav = document.getElementById('navbar')
const close = document.getElementById('close')

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