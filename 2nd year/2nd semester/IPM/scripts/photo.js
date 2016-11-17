/*Photo script*/
var foto = 2;
sendMode = false;
var selectPhotos = [];
var message;

function changeSubMenuPhoto(current, id){
  var nums = document.getElementsByClassName(id)[0];
  var listItem = nums.getElementsByTagName("li");
  for (var i=0; i < listItem.length; i++) {
      if(listItem[i] == current){
        listItem[i].style.backgroundColor = "#07123A";
      }
      else{
        listItem[i].style.backgroundColor = "#1D6FA9";
      }
  }
}

function toggleSubMenuPhoto(id){
  var w = document.getElementsByClassName(id)[0];
  var x;
  if(id == 'photoContent')
    x = document.getElementsByClassName("savedPhoto");
  if(id == 'savedPhoto')
    x = document.getElementsByClassName("photoContent");
  for (var i = 0; i < x.length; i++) {
    x[i].style.display = 'none';
  }
  w.style.display='block';
}


function closeWindowPhoto(window){
  var w = document.getElementById(window);
  w.style.visibility= 'hidden';
  w.style.opacity=0;
  w.style.pointerEvents = 'none';
}

function takePhoto(){
  document.getElementsByClassName("photoSpan")[0].style.display="none";
  var countDown = document.getElementsByClassName("countDown")[0].children[0];
  countDown.innerHTML = "";
  document.getElementsByClassName("countDown")[0].style.display="block";
  var counter = 4;
  var interval = setInterval(function() {
      counter--;
      countDown.innerHTML = counter;
      if (counter === 0){
        countDown.innerHTML = "";
        document.getElementsByClassName("photoContent")[0].style.animation =  "blink 0.5s";
      	document.getElementsByClassName("photo")[foto].style.display = "block";

      	document.getElementsByClassName("countDown")[0].style.display="none";
        document.getElementsByClassName("photoButton")[0].style.display="none";

      }
      else if(counter===-1){
        clearInterval(interval);
        document.getElementsByClassName("photoSpan")[0].style.display="block";
        document.getElementsByClassName("photoButton")[0].style.display="block";
        document.getElementsByClassName("photoContent")[0].style.backgroundImage = "none";
        document.getElementsByClassName("photoContent")[0].style.animation =  "initial";
      }
  }, 1000);
  var displayPhoto = setInterval(function(){
    clearInterval(displayPhoto);
    if(foto===0)
      document.getElementsByClassName("photoContent")[0].style.backgroundImage = "url('imgs/person1.jpg')";
    else if(foto===1)
      document.getElementsByClassName("photoContent")[0].style.backgroundImage = "url('imgs/person2.jpg')";
    else if(foto===2)
      document.getElementsByClassName("photoContent")[0].style.backgroundImage = "url('imgs/person2.jpg')";
    foto--;
    countDown.innerHTML = "";
  }, 4250);

}

function callSendPictureMode(){
  for(var i = 0; i <= $(".sendPicture").length; i++){
    if($(".sendPicture")[i] === event.target){
      sendPictureMode(i);
    }
  }
}

function sendPictureMode(mess){
  message = mess;
  for(var i = 0; i < 3; i++){
    $(".photo")[i].children[0].style.display = "block";
    $(".selectedPhotos")[0].style.display = "flex";
  }
  sendMode=true;
  $(".dockItem")[4].children[0].click();
  $(".photosTab")[1].click();
}

function selectPhoto(selected){
  if(sendMode===true){
    for(var i = 0; i <= selectPhotos.length; i++){
      if(selectPhotos[i] === selected){
        selectPhotos.splice(i,1);
        selected.children[0].children[0].src = "imgs/notChecked.png";
        $(".selectedPhotos")[0].children[0].innerHTML = "Selecionados: " + selectPhotos.length;
        return;
      }
    }
    selected.children[0].children[0].src = "imgs/checked.png";
    selectPhotos.push(selected);
    $(".selectedPhotos")[0].children[0].innerHTML = "Selecionados: " + selectPhotos.length;
  }
}

function sendPicture(){
  console.log(message);
  var conversation = document.getElementsByClassName('conversation')[message];
  var newDiv = document.createElement('div');

  newDiv.className = 'bubble bubble-right';



  var time = document.createElement('h6');
  time.innerHTML = document.getElementById('clock').innerHTML;

  document.getElementsByClassName('sideMessage')[message].children[2].innerHTML = "Tu: Enviaste uma foto";


  for(var i = 0; i < selectPhotos.length; i++){
    var newF = document.createElement('img');
    newF.src = selectPhotos[i].children[1].src;
    newF.className = "sendedPicture";
    newDiv.appendChild(newF);
  }

  newDiv.appendChild(time);
  conversation.appendChild(newDiv);

  conversation.scrollTop = conversation.scrollHeight;//Scroll to the ballon

  selectPhotos = [];
  //reset
  for(var j = 0; j < 3; j++){
    $(".photo")[j].children[0].style.display = "none";
    $(".photo")[j].children[0].children[0].src = "imgs/notChecked.png";
  }
  sendMode=false;
  $(".selectedPhotos")[0].style.display = "none";
  $(".selectedPhotos")[0].children[0].innerHTML = "Selecionados: 0";
  $(".photosTab")[0].click();
  $(".dockItem")[2].children[0].click();


}
