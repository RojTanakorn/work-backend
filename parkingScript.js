function handleParking(cond) {
  var reloadCurrentPosition = setInterval(function() {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);

        var botimg = document.getElementById("botPark");
        var midimg = document.getElementById("midPark");
        var topimg = document.getElementById("topPark");

        //status1 -> 2nd, status2 -> 6th, status3 -> 7th
        if (cond == 1) {
          // 2th is available
          if (myObj.d_status1 == 1) {
            botimg.src = "Pic/2aval_2.jpg";
            if (myObj.d_status2 == 1) {
              midimg.src = "Pic/6aval_1.jpg";
            } else {
              midimg.src = "Pic/6not_1.jpg";
            }

            if (myObj.d_status3 == 1) {
              topimg.src = "Pic/7aval_1.jpg";
            } else {
              topimg.src = "Pic/7not_1.jpg";
            }
          }

          // 2nd is not available
          else {
            botimg.src = "Pic/2not_2.jpg";
            // 6th is available
            if (myObj.d_status2 == 1) {
              midimg.src = "Pic/6aval_2.jpg";
              if (myObj.d_status3 == 1) {
                topimg.src = "Pic/7aval_1.jpg";
              } else {
                topimg.src = "Pic/7not_1.jpg";
              }
            }
            // 6th is not available
            else {
              midimg.src = "Pic/6not_2.jpg";
              if (myObj.d_status3 == 1) {
                topimg.src = "Pic/7aval_2.jpg";
              } else {
                topimg.src = "Pic/7not_2.jpg";
              }
            }
          }
        }
        // for cond = 2
        else {
          if (myObj.d_status1 == 1) {
            botimg.src = "Pic/2aval_1.jpg";
          } else {
            botimg.src = "Pic/2not_1.jpg";
          }
          if (myObj.d_status2 == 1) {
            midimg.src = "Pic/6aval_1.jpg";
          } else {
            midimg.src = "Pic/6not_1.jpg";
          }
          if (myObj.d_status3 == 1) {
            topimg.src = "Pic/7aval_1.jpg";
          } else {
            topimg.src = "Pic/7not_1.jpg";
          }
          clearInterval(reloadCurrentPosition);
        }
      }
    };
    xmlhttp.open("GET", "display_test.php", true);
    xmlhttp.send();
  }, 2000);
}
