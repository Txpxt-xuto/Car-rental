const buttonsLike = document.querySelectorAll(".button_like")
const buttonsLikeIcon = document.querySelectorAll(".button_like i")

buttonsLike.forEach((item, index) => {
    let buttonIcon = buttonsLikeIcon[index]
    item.onclick = () => 
    {
        if(buttonIcon.classList.contains("far")) {
            buttonIcon.classList.remove("far")
            buttonIcon.classList.add("fas", "like_icon")
        } else {
            buttonIcon.classList.add("far")
            buttonIcon.classList.remove("fas", "like_icon")
        }
    }
})

var menuItems=document.getElementById("MenuItems");
            
MenuItems.style.maxHeight="0px";
function menutoggle(){
    if(MenuItems.style.maxHeight == "0px"){
        MenuItems.style.maxHeight="200px";
    }
    else{
        MenuItems.style.maxHeight="0px";
    }
}

















































/*=============== SHOW MENU ===============*/
const navMenu = document.getElementById('nav-menu'),navToggle = document.getElementById('nav-toggle'),navClose = document.getElementById('nav-close')
/*===== MENU SHOW =====*/
/* Validate if constant exists */
if(navToggle){
    navToggle.addEventListener('click', () =>{
        navMenu.classList.add('show-menu')
    })
}
/*===== MENU HIDDEN =====*/
/* Validate if constant exists */
if(navClose){
    navClose.addEventListener('click', () =>{
        navMenu.classList.remove('show-menu')
    })
}
/*=============== REMOVE MENU MOBILE ===============*/
const navLink = document.querySelectorAll('.nav__link')
const linkAction = () =>{
    const navMenu = document.getElementById('nav-menu')
    // When we click on each nav__link, we remove the show-menu class
    navMenu.classList.remove('show-menu')
}
navLink.forEach(n => n.addEventListener('click', linkAction))
/*=========Swiper Projects=======*/
let swiperProjects = new Swiper(".projects__container", {
    loop: true,
        spaceBetween:24,
    navigation: {
        nextEl: ".swiper-button-next",
        prevEl: ".swiper-button-prev",
    },
    pagination: {
        el: ".swiper-pagination",
    },
    breakpoints: {
        1200: {
            slidesPerView: 2,
            spaceBetween: -56,
        },
        },
});
/*=============== CHANGE BACKGROUND HEADER ===============*/
const scrollHeader = () =>{
    const header = document.getElementById('header')
    // When the scroll is greater than 50 viewport height, add the scroll-header class to the header tag
    this.scrollY >= 50 ? header.classList.add('scroll-header') 
                        : header.classList.remove('scroll-header')
}
window.addEventListener('scroll', scrollHeader)
/*=============== TESTIMONIAL SWIPER ===============*/
let testimonialSwiper = new Swiper(".testimonial-swiper", {
    spaceBetween: 30,
    loop: 'true',
    navigation: {
        nextEl: ".swiper-button-next",
        prevEl: ".swiper-button-prev",
    },
});
/*=============== NEW SWIPER ===============*/
let newSwiper = new Swiper(".new-swiper", {
    spaceBetween: 24,
    loop: 'true',
    breakpoints: {
        576: {
            slidesPerView: 2,
        },
        768: {
            slidesPerView: 3,
        },
        1024: {
            slidesPerView: 4,
        },
    },
});
/*=============== SCROLL SECTIONS ACTIVE LINK ===============*/
const sections = document.querySelectorAll('section[id]')
const scrollActive = () =>{
    const scrollY = window.pageYOffset
	sections.forEach(current =>{
		const sectionHeight = current.offsetHeight,
		sectionTop = current.offsetTop - 58,
		sectionId = current.getAttribute('id'),
		sectionsClass = document.querySelector('.nav__menu a[href*=' + sectionId + ']')
		if(scrollY > sectionTop && scrollY <= sectionTop + sectionHeight){
			sectionsClass.classList.add('active-link')
		}else{
			sectionsClass.classList.remove('active-link')
		}                                                    
	})
}
window.addEventListener('scroll', scrollActive)
/*=============== SHOW SCROLL UP ===============*/ 
const scrollUp = () =>{
	const scrollUp = document.getElementById('scroll-up')
    // When the scroll is higher than 350 viewport height, add the show-scroll class to the a tag with the scrollup class
	this.scrollY >= 350 ? scrollUp.classList.add('show-scroll')
						: scrollUp.classList.remove('show-scroll')
}
window.addEventListener('scroll', scrollUp)
/*=============== SHOW CART ===============*/
const cart = document.getElementById('cart'),
        cartShop = document.getElementById('cart-shop'),
        cartClose = document.getElementById('cart-close')
/*===== CART SHOW =====*/
/* Validate if constant exists */
if(cartShop)
{
    cartShop.addEventListener('click', () =>{
        cart.classList.add('show-cart')
    })
}
/*===== CART HIDDEN =====*/
/* Validate if constant exists */
if(cartClose)
{
    cartClose.addEventListener('click', () =>{
        cart.classList.remove('show-cart')
    })
}
/*=============== DARK LIGHT THEME ===============*/
const lightIcon = document.getElementById("dark-icon");
const darkIcon = document.getElementById("light-icon");
const darkModeMediaQuery = window.matchMedia("(prefers-color-scheme: dark)");
let darkMode = darkModeMediaQuery.matches;
// Set dark-mode class on body if darkMode is true and pick icon
if (darkMode) 
{
    document.body.classList.add("dark-mode");
    darkIcon.setAttribute("display", "none");
} 
else 
{
    lightIcon.setAttribute("display", "none");
}
function toggleDarkMode() 
{
    // Toggle darkMode variable
    darkMode = !darkMode;
    // Toggle dark-mode class on body
    document.body.classList.toggle('dark-theme');
    // Toggle light and dark icons
    if (darkMode)
    {
        lightIcon.setAttribute("display", "block");
        darkIcon.setAttribute("display", "none");
    } 
    else 
    {
        lightIcon.setAttribute("display", "none");
        darkIcon.setAttribute("display", "block");
    }
}