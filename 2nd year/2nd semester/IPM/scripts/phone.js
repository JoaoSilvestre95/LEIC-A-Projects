/*Cenas do telefone*/
var connectPhones = 0;

function tooglePhone(y){
  var x = document.getElementsByClassName("phone");
  for(var i = 0; i < x.length; i++){
    x[i].style.backgroundColor = "white";
  }
  x[y].style.backgroundColor = "#A5D4FA";
  document.getElementsByClassName("confirmPhone")[0].style.backgroundColor= "#00b300";
  document.getElementsByClassName("confirmPhone")[0].style.pointerEvents = "auto";
}

function cancelPhone(){
  var x = document.getElementsByClassName("phone");
  for(var i = 0; i < x.length; i++){
    x[i].style.backgroundColor = "white";
  }
  document.getElementsByClassName("confirmPhone")[0].style.backgroundColor= "grey";
  document.getElementsByClassName("confirmPhone")[0].style.pointerEvents = "none";
  document.getElementsByClassName("dockItem")[3].children[0].click();
}

function connectPhone(){
  var x = document.getElementsByClassName("phone");
  var p = $(".phoneWidget");
  for(var i = 0; i < x.length; i++){
    if(x[i].style.backgroundColor == "rgb(165, 212, 250)"){
      $(".selectedPhone")[i].style.display = "block";
      $(".selectedPhoneHolder")[0].style.display = "none";
      for(var j = 2; j >= 0; j--){
        if(p[j].children[0].innerHTML == x[i].children[0].innerHTML){
          connectPhones++;
          p[j].style.display = "block";
        }
      }
      break;
    }
  }
  $(".clearPhoneNot")[0].style.display = "block";
   x = document.getElementsByClassName("phone");
  for(i = 0; i < x.length; i++){
    x[i].style.backgroundColor = "white";
  }
  document.getElementsByClassName("confirmPhone")[0].style.backgroundColor= "grey";
  document.getElementsByClassName("confirmPhone")[0].style.pointerEvents = "none";
}

function cleanNotif() {
  var n = $(".phoneWidget");
  for(var i = 0; i < n.length; i++){
    n[i].style.display = "none";
  }
  $(".clearPhoneNot")[0].style.display = "none";
  connectPhones = 0;
}

function closeNotif() {
  var n = $(".phoneWidget");
  for(var i = 0; i < n.length; i++){
    if(event.target.parentNode == n[i])
      n[i].style.display = "none";
  }

  connectPhones--;
  if(connectPhones === 0)
    $(".clearPhoneNot")[0].style.display = "none";

  event.stopPropagation();
}

function replyMessage(r) {
  var a = $(".messageWidget")[0].children[0].children[0].innerHTML;
  $(".messageWidget")[0].children[0].children[0].innerHTML = r;
  $(".messageWidget")[0].style.display = "block";
  var x = document.getElementsByClassName("window");
  var z = document.getElementsByClassName("selector");
  for (var i = 0; i < x.length; i++) {
      x[i].style.visibility = 'hidden';
      x[i].style.opacity = 0;
      x[i].style.pointerEvents = 'none';
  }
  for (i = 0; i < z.length; i++)
    z[i].style.visibility= 'hidden';

}

function closeWid() {
  $(".messageWidget")[0].style.display = "none";
}
