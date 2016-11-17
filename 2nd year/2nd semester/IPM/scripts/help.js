var hC = -1;
var helpToggled = false;

function help() {
  // $("#clockWidget")[0].style.webkitFilter = "blur(10px)";
  // $(".musicWidget")[0].style.webkitFilter = "blur(10px)";
  // $(".sideList")[0].style.webkitFilter = "blur(10px)";
  // for(var i = 0; i < $(".window").length; i++){
  //   $(".window")[i].style.webkitFilter = "blur(10px)";
  // }
  // $(".helpDiv")[0].style.display = "block";
  if(helpToggled === false){
    for(var i = 0; i < $(".window").length; i++){
      $(".window")[i].style.visibility = "hidden";
    }
    nextHelp();
    helpToggled = true;
  }else {
    closeHelp();
    hC = -1;
  }
}

function closeHelp() {
  helpToggled = false;
  hC = -1;
  $("#clockWidget")[0].style.webkitFilter = "blur(0px)";
  $(".musicWidget")[0].style.webkitFilter = "blur(0px)";
  $(".sideList")[0].style.webkitFilter = "blur(0px)";
  $("FOOTER")[0].style.webkitFilter = "blur(0px)";
  for(var i = 0; i < $(".window").length; i++){
    $(".window")[i].style.visibility = "hidden";
    $(".window")[i].style.webkitFilter = "blur(0px)";
  }
  $(".helpDiv")[0].style.display = "none";
}

function nextHelp(){
  if(hC > 8) return;
  hC++;
  var help = $(".helpDiv")[0];
  var helpMessage = $(".helpMessage")[0].children[0];
  for(var i = 0; i < $(".window").length; i++){
    $(".window")[i].style.visibility = "hidden";
    $(".window")[i].style.webkitFilter = "blur(0px)";
  }
  if(hC === 0){
    help.style.left = "100px";
    help.style.top = "550px";
    $("#clockWidget")[0].style.webkitFilter = "blur(10px)";
    $(".musicWidget")[0].style.webkitFilter = "blur(10px)";
    $(".sideList")[0].style.webkitFilter = "blur(10px)";
    $("FOOTER")[0].style.webkitFilter = "blur(0px)";
    $(".helpDiv")[0].style.display = "block";
    helpMessage.innerHTML = "Estes icons permitem aceder às funcionalidades da mesa. Ao clicar em qualquer um destes, será aberta a janela com a funcionalidade correspondente à figura.";
  }else if (hC === 1) {
    help.style.left = "1200px";
    help.style.top = "230px";
    $("#clockWidget")[0].style.webkitFilter = "blur(10px)";
    $(".musicWidget")[0].style.webkitFilter = "blur(10px)";
    $(".sideList")[0].style.webkitFilter = "blur(0px)";
    $("FOOTER")[0].style.webkitFilter = "blur(10px)";
    helpMessage.innerHTML = "Aqui é possivel aceder aos seus pedidos, ver os seus pedidos pendentes e todos os produtos que ja comprou";

  }else if (hC === 2) {
    help.style.left = "780px";
    help.style.top = "370px";
    $("#clockWidget")[0].style.webkitFilter = "blur(10px)";
    $(".musicWidget")[0].style.webkitFilter = "blur(0px)";
    $(".sideList")[0].style.webkitFilter = "blur(10px)";
    $("FOOTER")[0].style.webkitFilter = "blur(10px)";
    helpMessage.innerHTML = "Neste separador encontra o seu reprodutor de música. Onde pode mudar, parar ou começar a música, sempre com a informação de que música está a tocar actualmente";

  }else if (hC === 3) {
    toggleWindow('comidaWindow', 'foodSel');
    help.style.left = "1400px";
    help.style.top = "450px";
    $("#clockWidget")[0].style.webkitFilter = "blur(10px)";
    $(".musicWidget")[0].style.webkitFilter = "blur(10px)";
    $(".sideList")[0].style.webkitFilter = "blur(10px)";
    $("FOOTER")[0].style.webkitFilter = "blur(0px)";
    helpMessage.innerHTML = "Esta janela é o seu menu, onde pede a comida/bebida ao clicar no item que deseja comprar, e também pesquisar por algo em específico e ter a informação do preço total";

  }else if (hC === 4) {
    toggleWindow('musicaWindow', 'musicaSel');
    help.style.left = "1400px";
    help.style.top = "450px";
    $("#clockWidget")[0].style.webkitFilter = "blur(10px)";
    $(".musicWidget")[0].style.webkitFilter = "blur(10px)";
    $(".sideList")[0].style.webkitFilter = "blur(10px)";

    $("FOOTER")[0].style.webkitFilter = "blur(0px)";
    helpMessage.innerHTML = "Nesta janela pode escolher as músicas que deseja ouvir, ou criar listas com as músicas existentes, podendo sempre editá-las postriormente";


  }else if (hC === 5) {
    toggleWindow('mensagensWindow', 'mensSel');
    help.style.left = "1400px";
    help.style.top = "450px";
    $("#clockWidget")[0].style.webkitFilter = "blur(10px)";
    $(".musicWidget")[0].style.webkitFilter = "blur(10px)";
    $(".sideList")[0].style.webkitFilter = "blur(10px)";

    $("FOOTER")[0].style.webkitFilter = "blur(0px)";


    helpMessage.innerHTML = "Nesta janela encontra o sistema de mensagens das mesas, onde pode comunicar com qualquer outra mesa e até enviar fotografias";


  }else if (hC === 6) {
    toggleWindow('telefoneWindow', 'telSel');
    help.style.left = "1400px";
    help.style.top = "450px";
    $("#clockWidget")[0].style.webkitFilter = "blur(10px)";
    $(".musicWidget")[0].style.webkitFilter = "blur(10px)";
    $(".sideList")[0].style.webkitFilter = "blur(10px)";

    $("FOOTER")[0].style.webkitFilter = "blur(0px)";
    helpMessage.innerHTML = "Aqui pode escolher qual o dispositivo electrónico que deseja emparelhar com a mesa, e ainda ter informação daqueles que já se encontram emparelhados";


  }else if (hC === 7) {
    toggleWindow('fotoWindow', 'fotoSel');
    help.style.left = "1400px";
    help.style.top = "450px";
    $("#clockWidget")[0].style.webkitFilter = "blur(10px)";
    $(".musicWidget")[0].style.webkitFilter = "blur(10px)";
    $(".sideList")[0].style.webkitFilter = "blur(10px)";

    $("FOOTER")[0].style.webkitFilter = "blur(0px)";

    helpMessage.innerHTML = "Esta janela é a camera fotográfica, onde tira fotografias e pode aceder à galeria de fotografias que tirou";


  }else if (hC === 8) {
    toggleWindow('tvWindow', 'tvSel');
    help.style.left = "1400px";
    help.style.top = "450px";
    $("#clockWidget")[0].style.webkitFilter = "blur(10px)";
    $(".musicWidget")[0].style.webkitFilter = "blur(10px)";
    $(".sideList")[0].style.webkitFilter = "blur(10px)";

    $("FOOTER")[0].style.webkitFilter = "blur(0px)";
    helpMessage.innerHTML = "Esta janela é a televisão, onde pode ver qualquer canal que deseja, infelizmente não temos cabo e só temos 2 videos, desculpe :D";

  }else{
    hC--;
    toggleWindow('tvWindow', 'tvSel');
  }

}

function prevHelp() {
  if(hC !== 0){
    hC -= 2;
    nextHelp();
  }
}
