var lives = [];
var pause, endMenu, winMenu;
function createLives(){
  lives[0] = new Ship(140, 0, 0);
  lives[0].changeMaterialToBasic();
  lives[1] = new Ship(155, 0, 0);
  lives[1].changeMaterialToBasic();
  lives[2] = new Ship(170, 0, 0);
  lives[2].changeMaterialToBasic();
  scene.add(lives[0]);
  scene.add(lives[1]);
  scene.add(lives[2]);
}

function createPauseMenu(x, y, z){
  'use strict'
  pause = new THREE.Object3D();

  var material = new THREE.MeshBasicMaterial({ map: new THREE.TextureLoader().load( "js/texture/paused.jpg")});

  var geometry = new THREE.CubeGeometry(80, 16, 0.5);
  var mesh = new THREE.Mesh(geometry, material);
  mesh.position.set(0, 0, 0);
  //mesh.receiveShadow = true;
  //mesh.castShadow = true;
  pause.add(mesh);

  scene.add(pause);

  pause.position.x = x;
  pause.position.y = y;
  pause.position.z = z;
}

function createEndMenu(x, y, z){
  'use strict'
  endMenu = new THREE.Object3D();

  var material = new THREE.MeshBasicMaterial({ map: new THREE.TextureLoader().load( "js/texture/gameover.png")});

  var geometry = new THREE.CubeGeometry(80, 53.4, 0.5);
  var mesh = new THREE.Mesh(geometry, material);
  mesh.position.set(0, 0, 0);
  //mesh.receiveShadow = true;
  //mesh.castShadow = true;
  endMenu.add(mesh);

  scene.add(endMenu);

  endMenu.position.x = x;
  endMenu.position.y = y;
  endMenu.position.z = z;
}

function createWinMenu(x, y, z){
  'use strict'
  winMenu = new THREE.Object3D();

  var material = new THREE.MeshBasicMaterial({ map: new THREE.TextureLoader().load( "js/texture/youwin.png")});

  var geometry = new THREE.CubeGeometry(80, 60, 0.5);
  var mesh = new THREE.Mesh(geometry, material);
  mesh.position.set(0, 0, 0);
  //mesh.receiveShadow = true;
  //mesh.castShadow = true;
  winMenu.add(mesh);

  scene.add(winMenu);

  winMenu.position.x = x;
  winMenu.position.y = y;
  winMenu.position.z = z;
}
