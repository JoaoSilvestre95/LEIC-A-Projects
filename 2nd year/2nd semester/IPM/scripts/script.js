var locked = true;
var arrTotalAccount = [];
var arrFinalTotal = [];
var arrCurrentTotal = [];
var nPendent = 0;

function disablePointerEvents(id){
  var x = document.getElementsByClassName(id);
  for (var i = 0; i < x.length; i++) {
    x[i].style.pointerEvents = 'none';
  }
}

function enablePointerEvents(id){
  var x = document.getElementsByClassName(id);
  for (var i = 0; i < x.length; i++) {
    x[i].style.pointerEvents = 'auto';
  }
}

$(function() {
    document.getElementsByTagName("FOOTER")[0].style.pointerEvents = 'none';
    disablePointerEvents("window");
    var nums = document.getElementById("foodTab");
    var listItem = nums.getElementsByTagName("li");
    listItem[0].onclick();
    var musicStart = document.getElementById("musicTab");
    var listMusic = musicStart.getElementsByTagName("li");
    listMusic[0].onclick();
    document.getElementsByClassName('photosTab')[0].onclick();
    document.getElementsByClassName("repor")[0].style.backgroundColor = "grey";
    document.getElementsByClassName("repor")[0].style.pointerEvents = 'none';
    document.getElementsByClassName("confirmar")[0].style.backgroundColor = "grey";
    document.getElementsByClassName("confirmar")[0].style.pointerEvents = 'none';
    startTime();
    $( ".sideList").accordion({
      collapsible: true, active: false, heightStyle: "fill", header: "p", disabled: true
    });
    $(".sideList p.ui-accordion-header").click(function(){
      jQuery(this).next().slideToggle();
    });

    $(".video")[0].style.backgroundColor = "#2D80C4";

});

function unlock(){
  if(locked){
    document.getElementsByTagName("FOOTER")[0].style.filter= "blur(0px)";
    document.getElementsByTagName("FOOTER")[0].style.webkitFilter = "blur(0px)";
    document.getElementById("clockWidget").style.filter= "blur(0px)";
    document.getElementById("clockWidget").style.webkitFilter = "blur(0px)";
    document.getElementById("lockScreen").style.display = "none";
    document.getElementsByTagName("FOOTER")[0].style.pointerEvents = 'auto';
    document.getElementsByClassName("sideBar")[0].style.display = "block";
    $(".musicWidget")[0].style.display = "block";
    $(".help")[0].style.display = "block";
    locked = false;
  }
}

/*lock() = function(state){
    var containerElement = document.getElementById('FOOTER');
    var overlayEle = document.getElementsByClassName('warningButtons');

    if (state) {
        overlayEle.style.display = 'block';
        containerElement.setAttribute('class', 'blur');
    }
    else {
        overlayEle.style.display = 'none';
        containerElement.setAttribute('class', null);
    }

}*/

function changeSubMenu(current, id){
  var nums = document.getElementById(id);
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

function toggleSubMenu(id){
  var w = document.getElementById(id);
  var x = document.getElementsByClassName("products");
  for (var i = 0; i < x.length; i++) {
    x[i].style.visibility = 'hidden';
    x[i].style.opacity = 0;
  }
  w.style.visibility='visible';
  w.style.opacity=1;
}

function changeSubMenuMusic(current, id){
  var nums = document.getElementById(id);
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

function toggleSubMenuMusicas(id){
  var w = document.getElementById(id);
  if(id == 'musicas')
    var x = document.getElementsByClassName("listas");
  if(id == 'listas')
    var x = document.getElementsByClassName("musicas");
  for (var i = 0; i < x.length; i++) {
    x[i].style.visibility = 'hidden';
    x[i].style.opacity = 0;
  }
  w.style.visibility='visible';
  w.style.opacity=1;
}


function toggleWindow(id, idSelector){
  $(".messageWidget")[0].style.display = "none";
   var w = document.getElementById(id);
   var s = document.getElementById(idSelector);
   hideKeyboard();
   if(w.style.visibility == 'visible'){
    w.style.visibility= 'hidden';
    w.style.opacity=0;
    w.style.pointerEvents = 'none';
    s.style.visibility= 'hidden';
  }
  else{
    var x = document.getElementsByClassName("window");
    var z = document.getElementsByClassName("selector");
    for (var i = 0; i < x.length; i++) {
        x[i].style.visibility = 'hidden';
        x[i].style.opacity = 0;
        x[i].style.pointerEvents = 'none';
    }
    for (var i = 0; i < z.length; i++)
      z[i].style.visibility= 'hidden';

    w.style.pointerEvents = 'auto';
    w.style.visibility='visible';
    w.style.opacity=1;
    s.style.visibility= 'visible';
  }
}

function togglePaymentWindow(id){
  var x = document.getElementsByClassName("window");

  for (var i = 0; i < x.length; i++) {
      x[i].style.visibility = 'hidden';
      x[i].style.opacity = 0;
      x[i].style.pointerEvents = 'none';
  }
    $("#paymentWindow")[0].style.visibility = "visible";
    $("#paymentWindow")[0].style.opacity = 1;
    $("#paymentWindow")[0].style.pointerEvents = "auto";
    if( $("#paymentWindow")[0].style.display == "block"){
          $("#paymentWindow")[0].style.display = "none";
    }
    else
        $("#paymentWindow")[0].style.display = "block";
}

function closeWindow(id){
  var w = document.getElementById(id);
  document.getElementsByClassName("spanWarning")[0].innerHTML = "Tem a certeza que deseja fechar a janela?  \
    \n Ao fechar, todos os pedidos não confirmados irão ser removidos";
  document.getElementsByClassName("warningWindow")[0].style.display = "block";
  document.getElementsByClassName("right")[0].innerHTML = "Não";
  document.getElementsByClassName("left")[0].innerHTML = "Sim";
  document.getElementsByClassName("left")[0].onclick = function(){
    repor();
    document.getElementById('foodSel').style.visibility = 'hidden';
    w.style.visibility= 'hidden';
    w.style.opacity=0;
    w.style.pointerEvents = 'none';
    document.getElementsByClassName("warningWindow")[0].style.display = "none";
    hideKeyboard();
  };
  document.getElementsByClassName("right")[0].onclick = function(){ cancel(); };
}

function startTime() {
    var today = new Date();
    var h = today.getHours();
    var m = today.getMinutes();
    m = addZero(m);
    h = addZero(h);
    document.getElementById("clock").innerHTML = h + ":" + m;
    document.getElementById("lockclock").innerHTML = h + ":" + m;
    setTimeout(startTime, 500);
}

function addZero(i) {
    if (i < 10)
      i = "0" + i;   // add zero to the left
    return i;
}

function addPendentItem(){
  var nCircle = 0;
  if(document.getElementsByClassName("listContent")[0].children[0].innerHTML == "Sem pedidos pendentes"){
       var childs = document.getElementsByClassName("listContent")[0].children;
       var listCurrPend = document.getElementsByClassName("listContent")[0];
       listCurrPend.removeChild(childs[0]);
  }
  ++nPendent;
  console.log(arrFinalTotal);
  console.log(arrFinalTotal[0]);
  console.log(arrFinalTotal[1]);

  var newUpDiv = document.createElement("div");
  newUpDiv.className = "pendentRequest";

  var nPedido = document.createElement("span");
  nPedido.appendChild(document.createTextNode("Pedido nº: " + nPendent));

  newUpDiv.appendChild(nPedido);

  $(document.getElementsByClassName("listContent")[0]).append(newUpDiv);
  for(i = 0; i < arrFinalTotal.length; i++){
    var newDiv = document.createElement("div");
    newDiv.className = "pendentItem";

    var newS = document.createElement("span");
    newS.className = "numberItem";
    newS.style.width = "210px";
    newS.appendChild(document.createTextNode(arrFinalTotal[i][2] + "x " + arrFinalTotal[i][0]));

    var newC = document.createElement("div");
    newC.className = "circle" + nPendent + "n"+ nCircle;
    nCircle++;

    newDiv.appendChild(newS);
    newDiv.appendChild(newC);

    newUpDiv.appendChild(newDiv);

    $(document.getElementsByClassName("listContent")[0]).append(newUpDiv);
    console.log("."+newC.className);
    $("."+newC.className).circleProgress({
      value: 1,
      size: 20,
      thickness: 4,
      startAngle: Math.PI/2,
      animation: {duration: (Math.random()+1)*10000
      },
      fill: {
          color: "blue"
      }
    });
    $("."+newC.className).on('circle-animation-end', function(){
        this.closest(".pendentItem").remove();
        if(newUpDiv.children.length ==2)
          newUpDiv.remove();
        if(document.getElementsByClassName("listContent")[0].children.length == 0){
          var noP = document.createElement("span");
          noP.appendChild(document.createTextNode("Sem pedidos pendentes"));
          $(document.getElementsByClassName("listContent")[0]).append(noP);
        }
    });
  }

  var hr = document.createElement("hr");
  newUpDiv.appendChild(hr);
  arrFinalTotal.splice(0, arrFinalTotal.length);
}

function deletePendent(id){
  console.log("Já apagou");
  var del = document.getElementById(id);
  del.parentNode.removeChild(del);
}


function addItemToTotal(){
  var listCurr = document.getElementsByClassName("listContent")[1];
  while(listCurr.firstChild){
      listCurr.removeChild(listCurr.firstChild);
  }

  for(var i = 0; i < arrTotalAccount.length; i++){
    var newDiv = document.createElement("div");
    newDiv.className = "pendentItem";

    var newS = document.createElement("span");
    newS.className = "numberItem";
    newS.appendChild(document.createTextNode(arrTotalAccount[i][2] + "x " + arrTotalAccount[i][0] + " - " + arrTotalAccount[i][1] + " €"));

    newDiv.appendChild(newS);

    $(document.getElementsByClassName("listContent")[1] ).append( newDiv );
  }
}
