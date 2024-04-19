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
const root = document.documentElement;
const marqueeElementsDisplayed = getComputedStyle(root).getPropertyValue("--marquee-elements-displayed");
const marqueeContent = document.querySelector("ul.marquee-content");
root.style.setProperty("--marquee-elements", marqueeContent.children.length);
for(let i=0; i<marqueeElementsDisplayed; i++) {
    marqueeContent.appendChild(marqueeContent.children[i].cloneNode(true));
}