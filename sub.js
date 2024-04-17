var acc = document.getElementsByClassName("accordion");
var i;

for (i = 0; i < acc.length; i++) {
    acc[i].addEventListener("click", function() {
    this.classList.toggle("active");
    var panel = this.nextElementSibling;
    if (panel.style.maxHeight) {
        panel.style.maxHeight = null;
    } else {
        panel.style.maxHeight = panel.scrollHeight + "px";
    } 
    });
}

/*=============== SHOW MENU ===============*/
const navMenu = document.getElementById('nav-menu'),
      navToggle = document.getElementById('nav-toggle'),
      navClose = document.getElementById('nav-close')

/* Menu show */
navToggle.addEventListener('click', () =>{
   navMenu.classList.add('show-menu')
})

/* Menu hidden */
navClose.addEventListener('click', () =>{
   navMenu.classList.remove('show-menu')
})

/*=============== SEARCH ===============*/
const search = document.getElementById('search'),
      searchBtn = document.getElementById('search-btn'),
      searchClose = document.getElementById('search-close')

/* Search show */
searchBtn.addEventListener('click', () =>{
   search.classList.add('show-search')
})

/* Search hidden */
searchClose.addEventListener('click', () =>{
   search.classList.remove('show-search')
})

/*=============== LOGIN ===============*/
const login = document.getElementById('login'),
      loginBtn = document.getElementById('login-btn'),
      loginClose = document.getElementById('login-close')

/* Login show */
loginBtn.addEventListener('click', () =>{
   login.classList.add('show-login')
})

/* Login hidden */
loginClose.addEventListener('click', () =>{
   login.classList.remove('show-login')
})


document.addEventListener("DOMContentLoaded", function() { 
  const carousel = document.querySelector(".carousel"); 
  const arrowBtns = document.querySelectorAll(".wrapper i"); 
  const wrapper = document.querySelector(".wrapper"); 

  const firstCard = carousel.querySelector(".card"); 
  const firstCardWidth = firstCard.offsetWidth; 

  let isDragging = false, 
      startX, 
      startScrollLeft, 
      timeoutId; 

  const dragStart = (e) => {  
      isDragging = true; 
      carousel.classList.add("dragging"); 
      startX = e.pageX; 
      startScrollLeft = carousel.scrollLeft; 
  }; 

  const dragging = (e) => { 
      if (!isDragging) return; 
    
      // Calculate the new scroll position 
      const newScrollLeft = startScrollLeft - (e.pageX - startX); 
    
      // Check if the new scroll position exceeds  
      // the carousel boundaries 
      if (newScrollLeft <= 0 || newScrollLeft >=  
          carousel.scrollWidth - carousel.offsetWidth) { 
            
          // If so, prevent further dragging 
          isDragging = false; 
          return; 
      } 
    
      // Otherwise, update the scroll position of the carousel 
      carousel.scrollLeft = newScrollLeft; 
  }; 

  const dragStop = () => { 
      isDragging = false;  
      carousel.classList.remove("dragging"); 
  }; 

  const autoPlay = () => { 
    
      // Return if window is smaller than 800 
      if (window.innerWidth < 800) return;  
        
      // Calculate the total width of all cards 
      const totalCardWidth = carousel.scrollWidth; 
        
      // Calculate the maximum scroll position 
      const maxScrollLeft = totalCardWidth - carousel.offsetWidth; 
        
      // If the carousel is at the end, stop autoplay 
      if (carousel.scrollLeft >= maxScrollLeft) return; 
        
      // Autoplay the carousel after every 2500ms 
      timeoutId = setTimeout(() =>  
          carousel.scrollLeft += firstCardWidth, 2500); 
  }; 

  carousel.addEventListener("mousedown", dragStart); 
  carousel.addEventListener("mousemove", dragging); 
  document.addEventListener("mouseup", dragStop); 
  wrapper.addEventListener("mouseenter", () =>  
      clearTimeout(timeoutId)); 
  wrapper.addEventListener("mouseleave", autoPlay); 

  // Add event listeners for the arrow buttons to  
  // scroll the carousel left and right 
  arrowBtns.forEach(btn => { 
      btn.addEventListener("click", () => { 
          carousel.scrollLeft += btn.id === "left" ?  
              -firstCardWidth : firstCardWidth; 
      }); 
  }); 
}); 





const scrollers = document.querySelectorAll(".scroller");

// If a user hasn't opted in for recuded motion, then we add the animation
if (!window.matchMedia("(prefers-reduced-motion: reduce)").matches) {
  addAnimation();
}

function addAnimation() {
  scrollers.forEach((scroller) => {
    // add data-animated="true" to every `.scroller` on the page
    scroller.setAttribute("data-animated", true);

    // Make an array from the elements within `.scroller-inner`
    const scrollerInner = scroller.querySelector(".scroller__inner");
    const scrollerContent = Array.from(scrollerInner.children);

    // For each item in the array, clone it
    // add aria-hidden to it
    // add it into the `.scroller-inner`
    scrollerContent.forEach((item) => {
      const duplicatedItem = item.cloneNode(true);
      duplicatedItem.setAttribute("aria-hidden", true);
      scrollerInner.appendChild(duplicatedItem);
    });
  });
}
