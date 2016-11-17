
function changeVideo(name){
  var src = "videos/"+name+".mp4";
  console.log(src);
  document.getElementById("playing").src = src;
  document.getElementById("videoPlayer").load();
  document.getElementById("videoPlayer").play();
}

$(function() {
  $('#orderMus').on('click', function () {
      var alphabeticallyOrderedDivs = $("div.music").sort(function (a, b) {
          return $(a).find("h1").text() > $(b).find("h1").text();
      });
      $(".musicas").html(alphabeticallyOrderedDivs);
  });

  $('#orderArt').on('click', function () {
      var alphabeticallyOrderedDivs = $("div.music").sort(function (a, b) {
          return $(a).find("h2").text() > $(b).find("h2").text();
      });
      $(".musicas").html(alphabeticallyOrderedDivs);
  });

  $('#orderAlb').on('click', function () {
      var alphabeticallyOrderedDivs = $("div.music").sort(function (a, b) {
          return $(a).find(".nomeAlbum").text() > $(b).find(".nomeAlbum").text();
      });
      $(".musicas").html(alphabeticallyOrderedDivs);
  });

  $('#orderGen').on('click', function () {
      var alphabeticallyOrderedDivs = $("div.music").sort(function (a, b) {
          return $(a).find(".nomeGenero").text() > $(b).find(".nomeGenero").text();
      });
      $(".musicas").html(alphabeticallyOrderedDivs);
  });
});

function musicSearch(box) {
  var p = $(".music");
  var found = true;

  for(var i = 0; i < p.length; i++)
    p[i].style.display = "flex";

  for(i = 0; i < p.length; i++){
    p[i].style.display = "auto";

      var str = p[i].children[2].children[0].innerHTML.toLowerCase();
      var str1 = p[i].children[2].children[1].innerHTML.toLowerCase();
      var str2 = p[i].children[2].children[2].innerHTML.toLowerCase();
      var str3 = p[i].children[2].children[3].innerHTML.toLowerCase();
      if(box.value !== "" && str.search(box.value.toLowerCase()) == -1 && str1.search(box.value.toLowerCase()) == -1  && str2.search(box.value.toLowerCase()) == -1 && str3.search(box.value.toLowerCase()) == -1)
        p[i].style.display = "none";
  }
}

function clearMusicSearch(box) {
  box.value = '';
  musicSearch(box);
}

function closeWindowTv(id){
  var w = document.getElementById(id);
  document.getElementsByClassName("spanTelevisionWarning")[0].innerHTML = "Tem a certeza que deseja fechar a janela?  \
    \n Ao fechar, a reprodução da televisão será interrompida";
  document.getElementsByClassName("warningTelevisionWindow")[0].style.display = "block";
  document.getElementsByClassName("rightTv")[0].innerHTML = "Não";
  document.getElementsByClassName("leftTv")[0].innerHTML = "Sim";
  document.getElementsByClassName("leftTv")[0].onclick = function(){
      document.getElementById("videoPlayer").load();
    document.getElementById('tvSel').style.visibility = 'hidden';
    w.style.visibility= 'hidden';
    w.style.opacity=0;
    w.style.pointerEvents = 'none';
    document.getElementsByClassName("warningTelevisionWindow")[0].style.display = "none";
    hideKeyboard();
  };
  document.getElementsByClassName("rightTv")[0].onclick = function(){ cancelTv(); };
}

function cancelTv(){
    document.getElementsByClassName("warningTelevisionWindow")[0].style.display = "none";
}

function selectVideo(current){
  for(var i = 0; i < $(".video").length; i++){
      $(".video")[i].style.backgroundColor = "#A5D4FA";
  }
  current.style.backgroundColor = "#2D80C4";
}
