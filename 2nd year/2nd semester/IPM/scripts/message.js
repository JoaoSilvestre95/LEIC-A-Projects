/*Script de mensagens apenas aqui!!!!!!!*/
var superMartelo = 2;

$(document).ready(function() {
  document.getElementsByClassName('message')[0].style.display = "block";
  $(".sideMessage")[0].style.backgroundColor = "#2D80C4";
  for(var i = 0; i < $(".writeInput").length; i++){
    hideKeyboardMessage(i);
  }
});

$(document).ready(function() {
  $('#tempInput').keydown(function(e) {
    if(e.keyCode === 13) {
      callsendTempMessage();
    }
  });
});

$(document).ready(function() {
  $('input').keydown(function(e) {
    if(e.keyCode === 13) {
      for(var i = 0; i < $(".writeInput").length; i++){
        if($(".writeInput")[i] === event.target){
          sendMessage(i);
        }
      }
    }
  });
});

function selectConversation(){

  for(var i = 0; i < $(".sideMessage").length; i++){
    $(".sideMessage")[i].style.backgroundColor = "#A5D4FA";
    if($(".sideMessage")[i] === event.target || $(".sideMessage")[i] === event.target.parentNode){
      $(".sideMessage")[i].style.backgroundColor = "#2D80C4";
      var w = document.getElementsByClassName('message')[i];
      var x = document.getElementsByClassName('message');
      for (var j = 0; j < x.length; j++) {
        x[j].style.display = 'none';
      }
      w.style.display='block';

    }
  }
}
function callAddNewConversation(){
    $('.selectNewTableMessage')[0].style.display = "block";
    $('.messageContent')[0].style.pointerEvents = "none";
    $('.messageContent')[0].style.filter = "blur(5px)";
    $('.messageContent')[0].style.webkitFilter = "blur(5px)";
}
function exitSelectNewTableMessage(){
  $('.selectNewTableMessage')[0].style.display = "none";
  $('.messageContent')[0].style.pointerEvents = "auto";
  $('.messageContent')[0].style.filter = "blur(0px)";
  $('.messageContent')[0].style.webkitFilter = "blur(0px)";
}

function confirmSel(nome) {
  document.getElementsByClassName("spanWarningMessage")[0].innerHTML = "Tem a certeza que deseja iniciar uma conversa com o utilizador desta mesa?";
  document.getElementsByClassName("warningMessageWindow")[0].style.display = "block";
  document.getElementsByClassName("leftM")[0].innerHTML = "Não";
  document.getElementsByClassName("leftM")[0].onclick = function(){
    document.getElementsByClassName("warningMessageWindow")[0].style.display = "none";
  };
  document.getElementsByClassName("rightM")[0].innerHTML = "Sim";
  document.getElementsByClassName("rightM")[0].onclick = function(){
    addNewConversation(nome);
    document.getElementsByClassName("warningMessageWindow")[0].style.display = "none";
    exitSelectNewTableMessage()
  };
}

function addNewConversation(nome){
    var check = $('.sideMessage');
    for(var x = 0; x < check.length; x++){
      if(check[x].children[1].innerHTML === nome){
        $(".sideMessage")[x].click();
        return;
      }
    }
    //parte da esquerda
    var sideMessage = document.createElement('div');
    sideMessage.className = "sideMessage";
    sideMessage.onclick = function() { selectConversation(); };

    var messageImg = document.createElement('img');
    messageImg.className = "messageImg";
    messageImg.src = "imgs/user.png";/*<--Se fizermos eliminar isto esta mal*/

    var name = document.createElement('span');
    name.innerHTML = nome;                                         //FIXME

    var h5 = document.createElement('h5');                                //FIXME

    sideMessage.appendChild(messageImg);
    sideMessage.appendChild(name);
    sideMessage.appendChild(h5);
    $(".sideListMessage")[0].insertBefore(sideMessage, $(".sideListMessage")[0].children[0]);

    // parte da direira
    var message = document.createElement('div');
    message.className = "message";

    var conversation = document.createElement('div');
    conversation.className = "conversation";

    var inputMessage = document.createElement('div');
    inputMessage.className = "inputMessage";

    var writeInput = document.createElement('input');
    writeInput.className = "writeInput";
    writeInput.type = "text";
    writeInput.onclick = function() { callshowKeyboardMessage(); };
    writeInput.placeholder="Escreva uma mensagem...";

    var sendPicture = document.createElement('img');
    sendPicture.className = "sendPicture";
    sendPicture.src = "imgs/takePicture.png";
    sendPicture.onclick = function() { callSendPictureMode(); };

    var sendImg = document.createElement('img');
    sendImg.className = "sendImg";
    sendImg.src = "imgs/send.png";
    sendImg.onclick = function() { callSendMessage(); };

    var keyboardMessage = document.createElement('img');
    keyboardMessage.className = "keyboardMessage";
    keyboardMessage.src = "imgs/keyboard.png";
    keyboardMessage.onclick = function() { callhideKeyboardMessage();} ;

    inputMessage.appendChild(writeInput);
    inputMessage.appendChild(sendPicture);
    inputMessage.appendChild(sendImg);
    inputMessage.appendChild(keyboardMessage);
    message.appendChild(conversation);
    message.appendChild(inputMessage);
    $(".messageContent")[0].insertBefore(message, $(".messageContent")[0].children[1]);

    $('input').keydown(function(e) {
      if(e.keyCode === 13) {
        for(var i = 0; i < $(".writeInput").length; i++){
          if($(".writeInput")[i] === event.target){
            sendMessage(i);
          }
        }
      }
    });

    hideKeyboardMessage(0);
    $(".sideMessage")[0].click();
    superMartelo++;
    $(".myPopup")[0].style.display = "block";
    var oi = setInterval(function(){
      $(".myPopup")[0].style.display = "none";
      clearInterval(oi);
    }, 2000);

}

function showKeyboardMessage(i) {
    $(".keyboardMessage")[i].style.visibility = "visible";
    $(".writeInput")[i].style.top = '0px';
    $(".sendImg")[i].style.top = '10px';
    $(".sendPicture")[i].style.top = '10px';
    $(".conversation")[i].style.height = '252px';
    $(".inputMessage")[i].style.height = '292px';
    var conversation = document.getElementsByClassName('conversation')[i];
    conversation.scrollTop = conversation.scrollHeight;
}

function callshowKeyboardMessage() {
  for(var i = 0; i <= $(".writeInput").length; i++){
    if($(".writeInput")[i] === event.target){
      showKeyboardMessage(i);
    }
  }
}

function hideKeyboardMessage(i) {
    $(".keyboardMessage")[i].style.visibility = "hidden";
    $(".writeInput")[i].style.top = '241px';
    $(".sendImg")[i].style.top = '255px';
    $(".sendPicture")[i].style.top = '255px';
    $(".conversation")[i].style.height = '500px';
    $(".inputMessage")[i].style.height = '0px';
}

function callhideKeyboardMessage() {
  for(var i = 0; i <= $(".keyboardMessage").length; i++){
    if($(".keyboardMessage")[i] === event.target){
      hideKeyboardMessage(i);
    }
  }
}

function callSendMessage() {
  for(var i = 0; i <= $(".sendImg").length; i++){
    if($(".sendImg")[i] === event.target){
      sendMessage(i);
    }
  }
}

function callsendTempMessage() {
  sendTempMessage(superMartelo);
}

function sendMessage(index){
  var conversation = document.getElementsByClassName('conversation')[index];
  var message = document.getElementsByClassName('writeInput')[index].value;
  var newDiv = document.createElement('div');
  if(message !== ""){

    newDiv.className = 'bubble bubble-right';

    var newP = document.createElement('p');
    newP.innerHTML = message;

    var time = document.createElement('h6');
    time.innerHTML = document.getElementById('clock').innerHTML;

    if(message.length > 20){
      var res = message.substring(0, 20);
      document.getElementsByClassName('sideMessage')[index].children[2].innerHTML = "Tu: " + res + "...";
    }
    else{
      document.getElementsByClassName('sideMessage')[index].children[2].innerHTML = "Tu: " + message;
    }

    document.getElementsByClassName('writeInput')[index].value="";

    newDiv.appendChild(newP);
    newDiv.appendChild(time);
    conversation.appendChild(newDiv);

    conversation.scrollTop = conversation.scrollHeight;//Scroll to the ballon
    var oi = setInterval(function(){
      messageBot(index);
      clearInterval(oi);
    }, 2000);
  }
}

function messageBot(index){
  var conversation = document.getElementsByClassName('conversation')[index];
  var newDiv = document.createElement('div');
  newDiv.className = 'bubble';

  var newP = document.createElement('p');
  newP.innerHTML = "Hey Babe";

  var time = document.createElement('h6');
  time.innerHTML = document.getElementById('clock').innerHTML;

  document.getElementsByClassName('sideMessage')[index].children[2].innerHTML = "Hey Babe";


  newDiv.appendChild(newP);
  newDiv.appendChild(time);
  conversation.appendChild(newDiv);

  conversation.scrollTop = conversation.scrollHeight;//Scroll to the ballon
  if(document.getElementById('mensagensWindow').style.visibility == "hidden"){
    for(var i = 0; i < $('.popUpMessage').length; i++){
      if($('.popUpMessage')[i].children[0].innerHTML[6] == document.getElementsByClassName('sideMessage')[index].children[1].innerHTML[5]){
        $('.popUpMessage')[i].style.display = "block";
      }
    }

  }
}

function replyPopUpMessage(text, lel){
  if(document.getElementById('mensagensWindow').style.visibility != "hidden"){
    for(var i = 0; i<document.getElementsByClassName('sideMessage').length; i++){
      if(document.getElementsByClassName('sideMessage')[i].children[1].innerHTML == text){
        document.getElementsByClassName('sideMessage')[i].click();
      }
    }
    lel.style.display="none";
    return;
  }

  lel.style.display="none";
  document.getElementsByClassName('dockItem')[2].children[0].click();
  for(var i = 0; i<document.getElementsByClassName('sideMessage').length; i++){
    if(document.getElementsByClassName('sideMessage')[i].children[1].innerHTML == text){
      document.getElementsByClassName('sideMessage')[i].click();
    }
  }

}

function searchMessage(box) {
  var p = $(".sideMessage");

  for(var i = 0; i < p.length; i++)
    p[i].style.display = "block";

  for(i = 0; i < p.length; i++){
    p[i].style.display = "auto";
    var str = p[i].children[1].innerHTML.toLowerCase();
    if(box.value !== "" && str.search(box.value.toLowerCase()) == -1){
      p[i].style.display = "none";
    }
  }
}

function closeWindowMe(id){
  var w = document.getElementById(id);
  document.getElementsByClassName("spanWarning")[4].innerHTML = "Tem a certeza que deseja fechar a janela?  \
    \n Ao fechar, as mensagens não serão perdidas e poderá vê-las novamente ao abrir a janela";
  document.getElementsByClassName("warningWindow")[4].style.display = "block";
  document.getElementsByClassName("right")[3].innerHTML = "Não";
  document.getElementsByClassName("left")[3].innerHTML = "Sim";
  document.getElementsByClassName("left")[3].onclick = function(){
    document.getElementById('mensSel').style.visibility = 'hidden';
    w.style.visibility= 'hidden';
    w.style.opacity=0;
    w.style.pointerEvents = 'none';
    document.getElementsByClassName("warningWindow")[4].style.display = "none";
    hideKeyboard();
  };
  document.getElementsByClassName("right")[3].onclick = function(){ cancelMe(); };
}

function cancelMe(){
    document.getElementsByClassName("warningWindow")[4].style.display = "none";
}

function sendTempMessage(index){
  var conversation = document.getElementsByClassName('conversation')[index];
  var message = document.getElementsByClassName('writeInput')[index].value;
  var newDiv = document.createElement('div');
  if(message !== ""){

    newDiv.className = 'bubble bubble-right';

    var newP = document.createElement('p');
    newP.innerHTML = message;

    var time = document.createElement('h6');
    time.innerHTML = document.getElementById('clock').innerHTML;

    if(message.length > 20){
      var res = message.substring(0, 20);

    }
    else{

    }

    document.getElementsByClassName('writeInput')[index].value="";

    newDiv.appendChild(newP);
    newDiv.appendChild(time);
    conversation.appendChild(newDiv);

    conversation.scrollTop = conversation.scrollHeight;//Scroll to the ballon
  }
}



// function showTempKeyboardMessage() {
//     $(".keyboardMessage")[superMartelo].style.visibility = "visible";
//     $(".writeInput")[superMartelo].style.top = '0px';
//     $(".sendImg")[superMartelo].style.top = '10px';
//     $(".conversation")[superMartelo].style.height = '242px';
//     $(".inputMessage")[superMartelo].style.height = '272px';
//     var conversation = document.getElementsByClassName('conversation')[superMartelo];
//     conversation.scrollTop = conversation.scrollHeight;
// }
