var modal = document.getElementById("myModal");
var toppic = document.getElementById("topPark");
var midpic = document.getElementById("midPark");
var botpic = document.getElementById("botPark");
var chooseCond = 0;
var setPos = 0;

// Get the <span> element that closes the modal
var span = document.getElementsByClassName("close")[0];

// When the user clicks the button, open the modal
toppic.onclick = function() {
  modal.style.display = "block";
  document.getElementById("modaltext").innerText =
    "Are you sure for marking 7th position?";
  chooseCond = 7;
};

midpic.onclick = function() {
  modal.style.display = "block";
  document.getElementById("modaltext").innerText =
    "Are you sure for marking 6th position?";
  chooseCond = 6;
};

botpic.onclick = function() {
  modal.style.display = "block";
  document.getElementById("modaltext").innerText =
    "Are you sure for marking 2nd position?";
  chooseCond = 2;
};

// When the user clicks on <span> (x), close the modal
span.onclick = function() {
  modal.style.display = "none";
};

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event) {
  if (event.target == modal) {
    modal.style.display = "none";
  }
};

function handleMark(a) {
  if (setPos == 0) {
    if (a == 1) {
      switch (chooseCond) {
        case 2:
          botpic.src = "Pic/2set.jpg";
          break;

        case 6:
          midpic.src = "Pic/6set.jpg";
          break;

        case 7:
          toppic.src = "Pic/7set.jpg";
          break;

        default:
          alert("cant do");
          break;
      }
      setPos = 1;
    }
  } else {
    if (a == 1) {
      alert("You have already set your car' position.");
    }
  }
  modal.style.display = "none";
}

function resetPosition() {
  location.reload();
}
