/*Musicas script*/
var musics=[["Turbinada - Ana Malhoa", "music/anaMalhoa.jpg", "music/turbinada.mp3"], ["Never gonna give you up - Rick Roll", "music/rickRoll.png", "music/rickRoll.mp3"], ["Bohemian rhapsody - Queen","music/queen.jpg", "music/Bohemian.mp3"], ["Eurovison - Epic Sax Guy","music/epic.jpg", "music/epic.mp3"],
            ["Tu é a mulher - C4Pedro", "music/kizomba.jpg", "music/kizomba.mp3"], ["Hey Now - Martin Solveign","music/martin.jpg", "music/martin.mp3"], ["Una Mattina - Ludovico Eunaudi", "music/ludovico.jpg", "music/ludovico.mp3"], ["Blue in Green - Miles Davis","music/miles.jpg", "music/miles.mp3"]];
var aReproduzir = 0;
var currentList =0;
var lists=[];//[[[turbina,jpg],...]]
var nomeList = [];
var listEditar = [[]];
var editMode = false;
var aSerMartelado;
var quem;

$(document).ready(function() {
    $("#volume").slider({
        range: "min",
        misn: 0,
        max: 100,
        value: 80,
        animate: true,
        slide: function(event, ui) {
            setVolume((ui.value) / 100);
         }
    });
    document.getElementById("nameMusic").innerHTML = "A reproduzir: " + musics[0][0];
    document.getElementById("nameMusicWid").innerHTML = "A reproduzir: " + musics[0][0];
});

function setVolume(myVolume) {
    var myMedia = document.getElementById('musicaa');
    myMedia.volume = myVolume;
}

function playMusic(){
  var player = document.getElementsByClassName('reproducer')[0].children[0];
  if(player.paused){
    player.play();
    document.getElementsByClassName("imgPlayer")[0].src = "imgs/pause.png";
    document.getElementsByClassName("imgPlayer")[1].src = "imgs/pause.png";
  }
  else{
    player.pause();
    document.getElementsByClassName("imgPlayer")[0].src = "imgs/play.png";
    document.getElementsByClassName("imgPlayer")[1].src = "imgs/play.png";
  }

}

function selectMusic(i, name){
  $(".musicChange")[0].onclick = function(){prevSong();};
  $(".musicChange")[1].onclick = function(){nextSong();};
  $(".musicChange")[2].onclick = function(){prevSong();};
  $(".musicChange")[3].onclick = function(){nextSong();};
  document.getElementById("musicSrc").src = "music/"+name+".mp3";
  var player = document.getElementsByClassName('reproducer')[0].children[0];
  player.load();
  playMusic();
  var nameMusic = document.getElementById("nameMusic");
  nameMusic.innerHTML = "A reproduzir: " + musics[i][0];
  document.getElementById("nameMusicWid").innerHTML = "A reproduzir: " + musics[i][0];
  aReproduzir = i;
}

function addPlayList(){
  document.getElementById("listHead").style.display = 'flex';
  document.getElementsByClassName("listMusicContent")[0].style.display = 'block';
}

function removeDaPlaylist(){
  event.target.parentNode.remove(event.target);
  if(editMode==true){
    for(var i = 0; i < listEditar.length; i++){
      if(event.target.parentNode.children[2].innerHTML === listEditar[i][0]){
        listEditar.splice(i, 1);
      }
    }
  }
  for(var i = 0; i < listRepro.length; i++){
    if(event.target.parentNode.children[2].innerHTML === musics[listRepro[i]][0]){
      listRepro.splice(i, 1);
    }
  }
}

function removeTodaPlay(){
  var x = document.getElementsByClassName("listMusicContent")[1];
  while(x.firstChild){
      x.removeChild(x.firstChild);
  }
  listRepro.splice(0, listRepro.length);
  document.getElementsByClassName("warningWindow")[1].style.display = "none";
}

function cancelTodaPlay(){
  document.getElementsByClassName("warningWindow")[1].style.display = "none";
  var k = document.getElementsByClassName("listMusicContent")[1];
  while(k.firstChild){
      k.removeChild(k.firstChild);
  }
  $('#inputList').val("");
  var z = document.getElementById("addPlaylist");
  z.children[0].style.display = 'flex';
  z.children[1].style.display = 'flex';
  document.getElementsByClassName("saveCancelList")[0].style.display = 'none';
  document.getElementsByClassName("saveCancelList")[1].style.display = 'none';
  listEditar.splice(0, listEditar.length);

  document.getElementsByClassName('listMusicContent')[1].style.display = "none";
  document.getElementsByClassName('listMusicContent')[0].style.display = "none";
  editMode = false;
}

function changeToConfirm(){
  var x = document.getElementById("addPlaylist");
  x.children[0].style.display = 'none';
  x.children[1].style.display = 'none';
  document.getElementsByClassName("saveCancelList")[0].style.display = 'flex';
}

function closeWindowM(id){
  var w = document.getElementById(id);
  document.getElementsByClassName("spanWarning")[1].innerHTML = "Tem a certeza que deseja fechar a janela?  \
    \n Ao fechar, a reprodução da musica será interrompida";
  document.getElementsByClassName("warningWindow")[1].style.display = "block";
  document.getElementsByClassName("right")[1].innerHTML = "Não";
  document.getElementsByClassName("left")[1].innerHTML = "Sim";
  document.getElementsByClassName("left")[1].onclick = function(){
    document.getElementById('musicaSel').style.visibility = 'hidden';
    w.style.visibility= 'hidden';
    w.style.opacity=0;
    w.style.pointerEvents = 'none';
    document.getElementsByClassName("warningWindow")[1].style.display = "none";
    hideKeyboard();
  };
  document.getElementsByClassName("right")[1].onclick = function(){ cancelM(); };
}

function cancelM(){
    document.getElementsByClassName("warningWindow")[1].style.display = "none";
}

function warningPopUpMusic(text){
    if(text == "clean"){
        document.getElementsByClassName("spanWarning")[1].innerHTML = "Tem a certeza que deseja limpar a lista de reprodução?";
        document.getElementsByClassName("warningWindow")[1].style.display = "block";
        document.getElementsByClassName("right")[1].innerHTML = "Não";
        document.getElementsByClassName("left")[1].innerHTML = "Sim";
        document.getElementsByClassName("left")[1].onclick = function(){removeTodaPlay(); };
        document.getElementsByClassName("right")[1].onclick = function(){ cancelList(); };
    }
    else if(text == "cancel"){
      document.getElementsByClassName("spanWarning")[1].innerHTML = "Tem a certeza que deseja cancelar as alterações da sua lista de reprodução?";
      document.getElementsByClassName("warningWindow")[1].style.display = "block";
      document.getElementsByClassName("right")[1].innerHTML = "Não";
      document.getElementsByClassName("left")[1].innerHTML = "Sim";
      document.getElementsByClassName("left")[1].onclick = function(){cancelTodaPlay(); };
      document.getElementsByClassName("right")[1].onclick = function(){ cancelList(); };
    }
    else if(text == "confirmExistingList"){
      document.getElementsByClassName("spanWarning")[1].innerHTML = "Tem a certeza que deseja guardar esta lista de reprodução?";
      document.getElementsByClassName("warningWindow")[1].style.display = "block";
      document.getElementsByClassName("right")[1].innerHTML = "Sim";
      document.getElementsByClassName("left")[1].innerHTML = "Não";
      document.getElementsByClassName("right")[1].onclick = function(){
        for(var i = 0; i < nomeList.length; i++){
          if(nomeList[i] == aSerMartelado){
            var martelo = [];
	    $(".infoList")[i].children[0].innerHTML = $('#inputList').val();
	    nomeList[i] = $('#inputList').val();
            for(cenas = 0; cenas < listEditar.length; cenas++){
              martelo.push(listEditar[cenas]);
            }
            lists[i]=martelo;
            console.log("WTF");
            console.log(listEditar);
            document.getElementsByClassName("infoList")[i].children[0].innerHTML = $('#inputList').val();
            document.getElementsByClassName("infoList")[i].children[1].innerHTML = listEditar.length + " Músicas";
            document.getElementsByClassName("warningWindow")[1].style.display = "none";
            var k = document.getElementsByClassName("listMusicContent")[1];
            while(k.firstChild){
                k.removeChild(k.firstChild);
            }
            $('#inputList').val("");
            var z = document.getElementById("addPlaylist");
            z.children[0].style.display = 'flex';
            z.children[1].style.display = 'flex';
            document.getElementsByClassName("saveCancelList")[0].style.display = 'none';
            document.getElementsByClassName("saveCancelList")[1].style.display = 'none';
            listEditar.splice(0, listEditar.length);

            document.getElementsByClassName('listMusicContent')[1].style.display = "none";
            document.getElementsByClassName('listMusicContent')[0].style.display = "none";
            editMode = false;
          }
	}

      };
      document.getElementsByClassName("left")[1].onclick = function(){cancelList();};
    }
    else{
        document.getElementsByClassName("spanWarning")[1].innerHTML = "Tem a certeza que deseja guardar esta lista de reprodução?";
        document.getElementsByClassName("warningWindow")[1].style.display = "block";
        document.getElementsByClassName("right")[1].innerHTML = "Sim";
        document.getElementsByClassName("left")[1].innerHTML = "Não";
        document.getElementsByClassName("right")[1].onclick = function(){
          var x = $('#inputList').val();
          if(listRepro.length == 0){
            document.getElementsByClassName("warningWindow")[1].style.display = "none";
            document.getElementsByClassName("spanWarning")[3].innerHTML = "Lista vazia!";
            document.getElementsByClassName("warningWindow")[3].style.display = "block";
            document.getElementsByClassName("rightOk")[0].innerHTML = "ok";
            document.getElementsByClassName("rightOk")[0].onclick = function(){
              document.getElementsByClassName("warningWindow")[3].style.display = "none";
            };
            return;
          }
          else if(x == ""){
            document.getElementsByClassName("warningWindow")[1].style.display = "none";
            document.getElementsByClassName("spanWarning")[3].innerHTML = "Lista sem nome!";
            document.getElementsByClassName("warningWindow")[3].style.display = "block";
            document.getElementsByClassName("rightOk")[0].innerHTML = "ok";
            document.getElementsByClassName("rightOk")[0].onclick = function(){
              document.getElementsByClassName("warningWindow")[3].style.display = "none";
            };
            return;
          }
          else{
            for(var i = 0; i < lists.length; i++){

              console.log("Hello");
              console.log(listRepro.length);

              if(nomeList[i] == x){
                document.getElementsByClassName("warningWindow")[1].style.display = "none";
                document.getElementsByClassName("spanWarning")[3].innerHTML = "Lista com nome pretendido já existente!";
                document.getElementsByClassName("warningWindow")[3].style.display = "block";
                document.getElementsByClassName("rightOk")[0].innerHTML = "ok";
                document.getElementsByClassName("rightOk")[0].onclick = function(){
                  document.getElementsByClassName("warningWindow")[3].style.display = "none";
                };
                return;
              }
            }
          }
          nomeList.push(x);
          var newlist = [];
          for(var y = 0; y < listRepro.length; y++){
            newlist.push(musics[listRepro[y]]);
          }
          lists.push(newlist);
          console.log(lists.length);
          saveList(lists.length-1, x);
          document.getElementsByClassName("warningWindow")[1].style.display = "none";
          var k = document.getElementsByClassName("listMusicContent")[1];
          while(k.firstChild){
              k.removeChild(k.firstChild);
          }
          $('#inputList').val("");
          var z = document.getElementById("addPlaylist");
          z.children[0].style.display = 'flex';
          z.children[1].style.display = 'flex';
          document.getElementsByClassName("saveCancelList")[0].style.display = 'none';
          document.getElementsByClassName("saveCancelList")[1].style.display = 'none';
          listRepro.splice(0, listRepro.length);

          document.getElementsByClassName('listMusicContent')[1].style.display = "none";
          document.getElementsByClassName('listMusicContent')[0].style.display = "none";

        };
        document.getElementsByClassName("left")[1].onclick = function(){cancelList();};
    }
}

function cancelList(){
  document.getElementsByClassName("warningWindow")[1].style.display = "none";
}

function delCustomList() {

  for(var i = 0; i < $(".lista").length; i++){
    if($(".lista")[i] === event.target.parentNode){
      lists.splice(i, 1);
      nomeList.splice(i, 1);
    }
  }
  event.target.parentNode.remove(event.target.parentNode);
}

function saveList(i, name){

  var newDiv = document.createElement("div");
  newDiv.className = "lista";

  var newImg = document.createElement("img");
  newImg.className = "listaImg";
  newImg.src = "imgs/newplay.png";
  newImg.ondragstart = function() {drag(i, newDiv);};
  newImg.onclick = function() {listWarning(i);};


  var newImgPlay = document.createElement("img");
  newImgPlay.className = "playMusic";
  newImgPlay.src = "imgs/playMusic.png";
  newImgPlay.onclick = function(){ playCustomList(i); };

  var newDelPlay = document.createElement("img");
  newDelPlay.className = "delPlay";
  newDelPlay.src = "imgs/newDelPlay.png";
  newDelPlay.onclick = function(){
    delCustomList();
  };

  newDiv2 = document.createElement("div");
  newDiv2.className = "infoList";

  var newSpan = document.createElement("h2");
  newSpan.appendChild(document.createTextNode(name));

  var newSpan2 = document.createElement("h3");
  newSpan2.appendChild(document.createTextNode(lists[i].length + " Músicas"));

  newDiv2.appendChild(newSpan);
  newDiv2.appendChild(newSpan2);

  newDiv.appendChild(newImg);
  newDiv.appendChild(newImgPlay);
  newDiv.appendChild(newDiv2);
  newDiv.appendChild(newDelPlay);

  $( "#listas" ).append( newDiv );
}

function nextSong(){
  aReproduzir++;
  if(aReproduzir == 8)
    aReproduzir = 0;
  var name = musics[aReproduzir][0];
  document.getElementById("musicSrc").src = musics[aReproduzir][2];
  var player = document.getElementsByClassName('reproducer')[0].children[0];
  var musicName = document.getElementById("nameMusic");
  musicName.innerHTML = "A reproduzir: " + musics[aReproduzir][0];
  document.getElementById("nameMusicWid").innerHTML = "A reproduzir: " + musics[aReproduzir][0];

  if(player.paused){
    player.load();
  }
  else{
    player.load();
    player.play();
  }
}
function playCustomList(i){
  aReproduzir = 0;
  currentList = i;
  $(".musicChange")[0].onclick = function(){prevSongList();};
  $(".musicChange")[1].onclick = function(){nextSongList();};
  $(".musicChange")[2].onclick = function(){prevSongList();};
  $(".musicChange")[3].onclick = function(){nextSongList();};
  var name = lists[currentList][aReproduzir][0];
  document.getElementById("musicSrc").src = lists[currentList][aReproduzir][2];
  var player = document.getElementsByClassName('reproducer')[0].children[0];
  var musicName = document.getElementById("nameMusic");
  musicName.innerHTML = "A reproduzir: " + lists[currentList][aReproduzir][0];
  document.getElementById("nameMusicWid").innerHTML = "A reproduzir: " + lists[currentList][aReproduzir][0];
  document.getElementsByClassName("imgPlayer")[0].src = "imgs/pause.png";
  document.getElementsByClassName("imgPlayer")[1].src = "imgs/pause.png";
  player.load();
  player.play();
}
function nextSongList(){
  aReproduzir++;
  if(aReproduzir == lists[currentList].length)
    aReproduzir = 0;
  var name = lists[currentList][aReproduzir][0];
  document.getElementById("musicSrc").src = lists[currentList][aReproduzir][2];
  var player = document.getElementsByClassName('reproducer')[0].children[0];
  var musicName = document.getElementById("nameMusic");
  musicName.innerHTML = "A reproduzir: " + lists[currentList][aReproduzir][0];
  document.getElementById("nameMusicWid").innerHTML = "A reproduzir: " + lists[currentList][aReproduzir][0];
  if(player.paused){
    player.load();
  }
  else{
    player.load();
    player.play();
  }
}

function prevSongList(){
  aReproduzir--;
  if(aReproduzir == -1)
    aReproduzir = lists[currentList].length - 1;
  var name = lists[currentList][aReproduzir][0];
  document.getElementById("musicSrc").src = lists[currentList][aReproduzir][2];
  var player = document.getElementsByClassName('reproducer')[0].children[0];
  var musicName = document.getElementById("nameMusic");
  musicName.innerHTML = "A reproduzir: " + lists[currentList][aReproduzir][0];
  document.getElementById("nameMusicWid").innerHTML = "A reproduzir: " + lists[currentList][aReproduzir][0];
  if(player.paused){
    player.load();
  }
  else{
    player.load();
    player.play();
  }
}

function prevSong(){
  aReproduzir--;
  if(aReproduzir == -1)
    aReproduzir = 7;
  var name = musics[aReproduzir][0];
  document.getElementById("musicSrc").src = musics[aReproduzir][2];
  var player = document.getElementsByClassName('reproducer')[0].children[0];
  var musicName = document.getElementById("nameMusic");
  musicName.innerHTML = "A reproduzir: " + musics[aReproduzir][0];
  document.getElementById("nameMusicWid").innerHTML = "A reproduzir: " + musics[aReproduzir][0];
  if(player.paused){
    player.load();
  }
  else{
    player.load();
    player.play();
  }
}


function displayList(i){
  editMode=true;
  aSerMartelado = nomeList[i];
  listEditar.splice(0, listEditar.length);
  while($( ".listMusicContent")[1].firstChild){
      $( ".listMusicContent")[1].removeChild($( ".listMusicContent")[1].firstChild);
  }

  $('#inputList').val(nomeList[i]);
  /*Se a lista tiver cenas, warnig*/
  for(var k = 0; k<lists[i].length; k++){
    listEditar.push(lists[i][k]);
  }

      for(var j = 0; j < lists[i].length; j++){
        console.log("Ele enotru aqui");
        var newDiv = document.createElement("div");
        newDiv.className = "itemListMusic";
        newDiv.draggable = "true";
        // newDiv.ondragstart = function(){ dragEraseList(); };

        var newDel = document.createElement("img");
        newDel.id = "removePlaylist";
        newDel.src =  "imgs/remove.png"
        newDel.onclick = function() {
          removeDaPlaylist();
        }

        var newImg = document.createElement("img");
        newImg.className = "imgPlaylist";
        newImg.src = lists[i][j][1];


        var newSpan = document.createElement("span");
        newSpan.appendChild(document.createTextNode(lists[i][j][0]));

        newDiv.appendChild(newDel);
        newDiv.appendChild(newImg);
        newDiv.appendChild(newSpan);

        document.getElementById("addPlaylist").children[0].style.display = "none";
        document.getElementById("addPlaylist").children[1].style.display = "none";
        $(".saveCancelList")[1].style.display = "flex";
        $( ".listMusicContent")[1].appendChild( newDiv );
        document.getElementsByClassName("listMusicContent")[1].style.display = "block";
      }


}
function allowDrop(event) {
    event.preventDefault();
}

function drag(i, who) {
    pos = i;
    quem=who;
}

function drop(event) {
    event.preventDefault();
    var id = event.dataTransfer.getData("text");
    if(quem.className == "lista"){
      console.log("LEL");
      listWarning(pos);
      editMode=true;
      return;
    }
    if(editMode===true){
      addEditPlaylist();
      return;
    }
    document.getElementById('addPlaylist').children[0].onclick();
    document.getElementsByClassName('listMusicContent')[0].style.display = "none";
    document.getElementsByClassName('listMusicContent')[1].style.display = "block";

    var itemNaLista = false;
    for(var i = 0; i < listRepro.length; i++){
      if(listRepro[i] == pos){
        itemNaLista = true;
      }
    }

    if(itemNaLista == false){
      listRepro.push(pos);
      var newDiv = document.createElement("div");
      newDiv.className = "itemListMusic";
      newDiv.draggable = "true";

      var newDel = document.createElement("img");
      newDel.id = "removePlaylist";
      newDel.src =  "imgs/remove.png"
      newDel.onclick = function() { removeDaPlaylist(); }

      var newImg = document.createElement("img");
      newImg.className = "imgPlaylist";
      newImg.src = musics[pos][1];


      var newSpan = document.createElement("span");
      newSpan.appendChild(document.createTextNode(musics[pos][0]));

      newDiv.appendChild(newDel);
      newDiv.appendChild(newImg);
      newDiv.appendChild(newSpan);


      $(".listMusicContent")[1].appendChild( newDiv );

    }
}

function addEditPlaylist(){
  for(var i = 0 ; i< listEditar.length; i++){
    if(musics[pos][0] == listEditar[i][0]){
      return;
    }
  }
    listEditar.push(musics[pos]);
    var newDiv = document.createElement("div");
    newDiv.className = "itemListMusic";
    newDiv.draggable = "true";
    newDiv.ondragstart = function(pos){ dragErase(pos, event); };

    var newDel = document.createElement("img");
    newDel.id = "removePlaylist";
    newDel.src =  "imgs/remove.png"
    newDel.onclick = function() { removeDaPlaylist(); }

    var newImg = document.createElement("img");
    newImg.className = "imgPlaylist";
    newImg.src = musics[pos][1];


    var newSpan = document.createElement("span");
    newSpan.appendChild(document.createTextNode(musics[pos][0]));

    newDiv.appendChild(newDel);
    newDiv.appendChild(newImg);
    newDiv.appendChild(newSpan);


    $(".listMusicContent")[1].appendChild( newDiv );

}

function listWarning(i) {
  if(editMode){
    document.getElementsByClassName("spanWarning")[2].innerHTML = "Se editar outra lista, todas as alterações não guardadas serão perdidas. Deseja continuar?";
    document.getElementsByClassName("warningWindow")[2].style.display = "block";
    document.getElementsByClassName("right")[2].innerHTML = "Cancelar";
    document.getElementsByClassName("left")[2].innerHTML = "Sim";
    document.getElementsByClassName("left")[2].onclick = function(){
      displayList(i);
      document.getElementsByClassName("warningWindow")[2].style.display = "none";
    };
    document.getElementsByClassName("right")[2].onclick = function(){
      document.getElementsByClassName("warningWindow")[2].style.display = "none";
    };
  } else displayList(i);
}

function showMusicKeyboard() {
    $(".keyboard")[1].style.visibility = "visible";
    $(".hideKeyboard")[1].style.pointerEvents = 'auto';
}
