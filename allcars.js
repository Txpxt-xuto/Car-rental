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