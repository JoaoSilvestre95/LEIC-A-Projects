var varTotal = 0;
var naLista = false; //Se está alguma coisa na lista de reprodução
var listRepro = [];
var pos, posRemove;
var martelo = 0;
function hideKeyboard() {
    $(".keyboard")[0].style.visibility = "hidden";
    $(".hideKeyboard")[0].style.pointerEvents = 'none';
}

function showKeyboard() {
    $(".keyboard")[0].style.visibility = "visible";
    $(".hideKeyboard")[0].style.pointerEvents = 'auto';
}

$(function() {
  $(".hideKeyboard").on("click", function(e){
      e.preventDefault();
      hideKeyboard();
  });
});

function addProduct(name, price){
  toogleShopOption(true);
  var alt = false;
  var quant;
  for(var i = 0; i < arrCurrentTotal.length; i++){
    if(name == arrCurrentTotal[i][0]){
      var listDiv = document.getElementById("listShop").children;
      quant = ++arrCurrentTotal[i][2];
      listDiv[i].getElementsByClassName("quant")[0].innerHTML = quant;
      listDiv[i].getElementsByClassName("price")[0].innerHTML = price*quant + "€";
      alt = true;
      break;
    }
  }
  /*New Product*/
  if (!alt) {
    var newDiv = document.createElement("div");
    newDiv.className = "comprado";

    var lixo = document.createElement("img");
    lixo.src="scripts/delete.png";
    lixo.className = "lixo";
    lixo.onclick = function(){erase(name);};

    var newP = document.createElement("span");
    newP.className = "name";
    newP.appendChild(document.createTextNode(name));

    var menos = document.createElement("img");
    menos.src="scripts/minus.png";
    menos.className = "menos";
    menos.onclick = function(){decrease(name, price);};

    var quantidade = document.createElement("span");
    quantidade.className = "quant";
    quantidade.appendChild(document.createTextNode("1"));

    var mais = document.createElement("img");
    mais.src="scripts/plus.png";
    mais.className = "mais";
    mais.onclick = function(){addProduct(name, price);};

    var newPrice = document.createElement("span");
    newPrice.className = "price";
    newPrice.appendChild(document.createTextNode(price + "€"));

    newDiv.appendChild(lixo);
    newDiv.appendChild(newP);
    newDiv.appendChild(menos);
    newDiv.appendChild(quantidade);
    newDiv.appendChild(mais);
    newDiv.appendChild(newPrice);

    var product = [name, price, 1];
    arrCurrentTotal.push(product);

    $( "#listShop" ).append( newDiv );
  }
  getTotal();
}


function decrease(name, price){
  for(var i = 0; i < arrCurrentTotal.length; i++){
    if(name == arrCurrentTotal[i][0]){
      var listDiv = document.getElementById("listShop").children;
      var quant = --arrCurrentTotal[i][2];
      if(quant <= 0){
        //faz cenas eliminar
        arrCurrentTotal[i][2]=1;
        erase(name);
        break;
      }else{
        listDiv[i].getElementsByClassName("quant")[0].innerHTML = quant;
        listDiv[i].getElementsByClassName("price")[0].innerHTML = price*quant + "€";
        break;
      }
    }

  }
  getTotal();
}

function togglepayment(){
        document.getElementsByClassName("spanWarning1")[0].innerHTML = "Pagamento efectuado com sucesso";
        document.getElementsByClassName("warningWindow1")[0].style.display = "block";
        document.getElementsByClassName("ok")[0].innerHTML = "Ok";
        document.getElementsByClassName("ok")[0].onclick = function(){
            document.getElementById('paymentWindow').style.display = 'none';
            document.getElementsByClassName("warningWindow1")[0].style.display = "none";
            $(".TotalPagar")[0].innerHTML = "Total a Pagar: 0 €";
            $(".TotalPagar")[1].innerHTML = "Total a Pagar: 0 €";
            $(".listContent")[1].innerHTML = "Sem produtos Comprados";
        };
}

function cancel(){
    document.getElementsByClassName("warningWindow")[0].style.display = "none";
}

function warningPopUp(text){
    if(text == "clean"){
        document.getElementsByClassName("spanWarning")[0].innerHTML = "Tem a certeza que deseja limpar a lista?";
        document.getElementsByClassName("warningWindow")[0].style.display = "block";
        document.getElementsByClassName("right")[0].innerHTML = "Não";
        document.getElementsByClassName("left")[0].innerHTML = "Sim";
        document.getElementsByClassName("left")[0].onclick = function(){ repor(); };
        document.getElementsByClassName("right")[0].onclick = function(){ cancel(); };
    }
    else{
        document.getElementsByClassName("spanWarning")[0].innerHTML = "Tem a certeza que deseja efetuar este pedido?";
        document.getElementsByClassName("warningWindow")[0].style.display = "block";
        document.getElementsByClassName("right")[0].innerHTML = "Sim";
        document.getElementsByClassName("left")[0].innerHTML = "Não";
        document.getElementsByClassName("right")[0].onclick = function(){ confirm(); };
        document.getElementsByClassName("left")[0].onclick = function(){ cancel(); };
    }
}

function confirm() {
  if(arrCurrentTotal.length !== 0){
    var x = document.getElementById("listShop");
    while(x.firstChild)
        x.removeChild(x.firstChild);
  }
    var addedToAcc, addedToPend;
    for(var i = 0; i < arrCurrentTotal.length; i++){
      addedToAcc = false;
      addedToPend = false;
      for(var j = 0; j < arrFinalTotal.length; j++){
        if(arrFinalTotal[j][0] == arrCurrentTotal[i][0]){
          arrFinalTotal[j][2] += arrCurrentTotal[i][2];
          addedToPend = true;
        }
      }
      for(j = 0; j < arrTotalAccount.length; j++){
        if(arrTotalAccount[j][0] == arrCurrentTotal[i][0]){
          arrTotalAccount[j][2] += arrCurrentTotal[i][2];
          addedToAcc = true;
        }
      }

      var product1 = [arrCurrentTotal[i][0], arrCurrentTotal[i][1], arrCurrentTotal[i][2]];
      var product2 = [arrCurrentTotal[i][0], arrCurrentTotal[i][1], arrCurrentTotal[i][2]];
      if(!addedToPend) arrFinalTotal.push(product1);
      if(!addedToAcc) arrTotalAccount.push(product2);

    }
    addItemToTotal();
    if(arrFinalTotal.length != 0)
      addPendentItem();
    document.getElementsByClassName("TotalPagar")[0].innerHTML = "Total a Pagar: " + getFinalTotal() +" €";
    document.getElementsByClassName("TotalPagar")[1].innerHTML = "Total a Pagar: " + getFinalTotal() +" €"

    document.getElementsByClassName("warningWindow")[0].style.display = "none";
    arrCurrentTotal.splice(0, arrCurrentTotal.length);
    toogleShopOption(false);
    getTotal();
}

function productTimeOut(i) {
  arrFinalTotal.splice(i, 1); ///////remove dos pendentes
  addPendentItem();
}

function getFinalTotal() {
  var total = 0;
  for(var i =0; i < arrTotalAccount.length; i++)
    total += arrTotalAccount[i][1] * arrTotalAccount[i][2];
  return total;
}

function repor() {
  if(arrCurrentTotal.length !== 0){
      arrCurrentTotal.splice(0, arrCurrentTotal.length);

      var x = document.getElementById("listShop");
      while(x.firstChild){
          x.removeChild(x.firstChild);
      }
      document.getElementsByClassName("warningWindow")[0].style.display = "none";
      toogleShopOption(false);
      getTotal();
  }
}

function erase(name){

  var childs = document.getElementById("listShop").children;
  var listCurrShop = document.getElementById("listShop");
  for(var i = 0; i < childs.length; i++){
    if(childs[i].getElementsByClassName("name")[0].innerHTML == name)
      break;
  }
  listCurrShop.removeChild(childs[i]);
  for(i = 0; i < arrCurrentTotal.length; i++){
     if(name == arrCurrentTotal[i][0]){
       arrCurrentTotal.splice(i, 1);
     }
  }
  if(arrCurrentTotal.length==0){
    toogleShopOption(false);
  }
  getTotal();
}

function getTotal(){
  var total = 0;

  for(var i = 0; i < arrCurrentTotal.length; i++){
    total += arrCurrentTotal[i][1]*arrCurrentTotal[i][2];

  }
  document.getElementById("total").innerHTML = "Total: " + total + " €";
}


function search(box) {
  var p = $(".product");

  for(var i = 0; i < p.length; i++)
    p[i].style.display = "flex";

  for(i = 0; i < p.length; i++){
    p[i].style.display = "auto";
    var str = p[i].children[1].children[0].innerHTML.toLowerCase();
    var desc = p[i].children[1].children[1].innerHTML.toLowerCase();
    if(box.value !== "" && str.search(box.value.toLowerCase()) == -1 && desc.search(box.value.toLowerCase()) == -1){
      p[i].style.display = "none";
    }
  }
}

function clearSearch(box) {
  box.value = '';
  search(box);
}


function toogleShopOption(sig){
  if(sig == false){
    document.getElementsByClassName("repor")[0].style.backgroundColor = "grey";
    document.getElementsByClassName("repor")[0].style.pointerEvents = 'none';
    document.getElementsByClassName("confirmar")[0].style.backgroundColor = "grey";
    document.getElementsByClassName("confirmar")[0].style.pointerEvents = 'none';
  }
  else{
    document.getElementsByClassName("repor")[0].style.backgroundColor = "#b30000";
    document.getElementsByClassName("repor")[0].style.pointerEvents = 'auto';
    document.getElementsByClassName("confirmar")[0].style.backgroundColor = "#00b300";
    document.getElementsByClassName("confirmar")[0].style.pointerEvents = 'auto';
  }
}
