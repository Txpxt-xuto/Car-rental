document.addEventListener("DOMContentLoaded", function () {
    const container = document.querySelector(".card-container");
    const cards = document.querySelectorAll(".card");

    // Clone cards for a smooth infinite loop
    cards.forEach((card) => {
        const clone = card.cloneNode(true);
        container.appendChild(clone);
    });
});
