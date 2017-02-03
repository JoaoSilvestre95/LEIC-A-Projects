/*fps*/
var id;
var stats = new Stats();
stats.showPanel( 1 ); // 0: fps, 1: ms, 2: mb, 3+: custom
document.body.appendChild( stats.dom );
var paused = false;

var spotLightHelper;

var wireframeSet = false; //global wireframe settings

var fieldWidth = 160;
var fieldHeight = 80;


var aliensPositions = [[-8, 25, 0],[8, 25, 0],[24, 25, 0],[-8, 9, 0],[-24, 25, 0],
                  [8, 9, 0],[24, 9, 0],[-24, 9, 0]];
var aliens = [];
var bullets = [];
var ship;

var clockGame = new THREE.Clock(false);

var views = {viewGame:
				{
					left: 0,
					bottom: 0,
					width: 1.0,
					height: 1.0
				},viewLives:
        {
					left: 0.78,
					bottom: 0.8,
					width: 0.2,
					height: 0.2,
          eyeX: 155,
          eyeY: 0,
          eyeZ: 20
				},viewPause:
        {
					left: 0.25,
					bottom: 0.3,
					width: 0.5,
					height: 0.5,
          eyeX: -200,
          eyeY: 0,
          eyeZ: 20
				},viewEnd:
        {
					left: 0.25,
					bottom: 0.3,
					width: 0.5,
					height: 0.5,
          eyeX: 0,
          eyeY: 500,
          eyeZ: 20
				}, viewWin:
        {
					left: 0.25,
					bottom: 0.3,
					width: 0.5,
					height: 0.5,
          eyeX: 0,
          eyeY: -500,
          eyeZ: 20
				}
      };
var camera_flag = 1;

var materiais = [];
//[aliens[[[body,eye,leg]],ship[],bullets[]]

var table;
function createGameArea( x , y , z){
    'use strict'
		table = new THREE.Object3D();

    var material = new THREE.MeshBasicMaterial({ map: new THREE.TextureLoader().load( "js/texture/background.jpg")});

    var geometry = new THREE.CubeGeometry(fieldWidth, fieldHeight, 0.5);
    var mesh = new THREE.Mesh(geometry, material);
    mesh.position.set(x, y, z);
    mesh.receiveShadow = true;
    mesh.castShadow = true;
    table.add(mesh);

    scene.add(table);

    table.position.x = x;
    table.position.y = y;
    table.position.z = z-5;
}

function createAliens(){
    var alien;
    var signal;
    for(var i=0; i<8; i++){
      alien = new Alien(aliensPositions[i][0],aliensPositions[i][1],aliensPositions[i][2]);
      angle = Math.random()*Math.PI*2;
      alien.set_speedY(alien.get_speedY()*Math.sin(angle));
      alien.set_speedX(alien.get_speedX()*Math.cos(angle));
      aliens.push(alien);
    }
}

function createScene() {
    'use strict';

    scene = new THREE.Scene();
    createGameArea(0, 0, 0);
    createAlienMateriais();
    createShipMaterial();
    createBulletsMaterial();

    createAliens();
    ship = new Ship(0, -35, 0);

    createLives();
    createPauseMenu(-200,0,10);
    createEndMenu(0, 500, 10);
    createWinMenu(0, -500, 10);
}

function render() {
    'use strict';
    renderView(views.viewGame);
    renderView(views.viewLives);
    if(paused)
      renderView(views.viewPause);
    if(lives.length == 0){
      renderView(views.viewEnd);
      clockGame.stop();
    }
    if(aliens.length == 0){
      renderView(views.viewWin);
      clockGame.stop();
    }
}
function renderView(view){
  var left   = Math.floor( window.innerWidth  * view.left );
	var bottom = Math.floor( window.innerHeight * view.bottom );
	var width  = Math.floor( window.innerWidth  * view.width );
	var height = Math.floor( window.innerHeight * view.height );
	renderer.setViewport( left, bottom, width, height );

  view.camera.updateProjectionMatrix();
	renderer.render( scene, view.camera );
}

function onKeyDown(e) {
    'use strict';

    switch (e.keyCode) {
        case 65: //A
        case 97: //a
            for(var i=0; i < materiais.length; i++){//iterates i type object
              if(i != 0){//Ship or bullets
                for(var j=0; j < materiais[i].length; j++)
                  materiais[i][j].wireframe = !materiais[i][j].wireframe;
              }
              else{//Aliens
                for(var j=0; j < materiais[i].length; j++){//
                  for(var k=0; k < materiais[j].length; k++)//iterates all body parts of j alien
                      materiais[i][j][k].wireframe = !materiais[i][j][k].wireframe;
                }
              }
            }
            break;
        case 83:
        case 115:
          if(paused){
            paused = false;
            clockGame.start();
          }
          else{
            paused = true;
            clockGame.stop();
          }
          break;
        case 37: //  <-
          if(!paused)
              ship.set_accelarationX(-ship.get_AC());
          break;

        case 39: // ->
          if(!paused)
              ship.set_accelarationX(ship.get_AC());
          break;

        case 49: // 1
            views.viewGame.camera = ortogonalcamera;
            camera_flag = 1;
            handleAliensRotation();
            break;
        case 50: // 2
            views.viewGame.camera = thirdpersoncamera;
            camera_flag = 2;
            handleAliensRotation();
            break;
        case 51: // 3
            views.viewGame.camera = perspectivecamera;
            camera_flag = 3;
            handleAliensRotation();
            break;
        case 78: // N
        case 110: // n
            manageStats('n');
            break;
        case 76: // L
        case 108: // l
            manageStats('l');
            break;
        case 71: // g
        case 103: // G
            manageStats('g');
            break;
        case 67: // c
        case 99: // C
            manageStats('c');
            break;
        case 72: // h
        case 104: // H
            manageStats('h');
            break;
        case 82: //r
        case 114: //R
          if(lives.length == 0 || aliens.length == 0)
            resetGame();
          break;
    }

}

function onKeyUp(e){
  'use strict';

  switch (e.keyCode) {
    case 37:
        if(ship.get_speedX() < 0)
          ship.set_accelarationX(ship.get_AC());
        break;
    case 39:
        if(ship.get_speedX() > 0)
          ship.set_accelarationX(-ship.get_AC());
        break;
    case 66: //B
    case 98: //b
        var bullet = new Bullet(ship.position.x, ship.position.y + 7, 0); //distance: 6.5, but 7 to get a distance
        bullets.push(bullet);
        break;
  }
}

function resetGame(){
  for(var i = 0; i < aliens.length; i++)
    scene.remove(aliens[i]);
  aliens.splice(0, aliens.length);
  for(var i = 0; i < bullets.length; i++)
    scene.remove(bullets[i]);
  bullets.splice(0, bullets.length);
  scene.remove(ship);
  for(var i = 0; i < lives.length; i++)
    scene.remove(lives[i]);
  lives.splice(0, lives.length);


  createAliens();
  ship = new Ship(0, -35, 0);
  ship.add(thirdpersoncamera);
  ship.add(spotLight);
  createLives();
  camera_flag = 1;
  views.viewGame.camera = ortogonalcamera;
  clockGame.start();

}


function init() {
    'use strict';

    renderer = new THREE.WebGLRenderer();
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.autoClear = false;
    document.body.appendChild(renderer.domElement);

    createScene();
    createThirdpersonCamera();
    createOrtogonalCamera();
    createPerspectiveCamera();
    createLivesCamera(views.viewLives.eyeX, views.viewLives.eyeY, views.viewLives.eyeZ);
    createPauseCamera(views.viewPause.eyeX, views.viewPause.eyeY, views.viewPause.eyeZ);
    createEndMenuCamera(views.viewEnd.eyeX, views.viewEnd.eyeY, views.viewEnd.eyeZ);
    createWinMenuCamera(views.viewWin.eyeX, views.viewWin.eyeY, views.viewWin.eyeZ);
    createAmbientLight();
    createSpotLight();
    createStars();

    //spotLightHelper = new THREE.SpotLightHelper( spotLight );
    //scene.add( spotLightHelper );

    ship.add(thirdpersoncamera);
    ship.add(spotLight);

    camera_flag = 1;
    views.viewGame.camera = ortogonalcamera;
    views.viewLives.camera = livesCamera;
    views.viewPause.camera = pauseCamera;
    views.viewEnd.camera = endMenuCamera;
    views.viewWin.camera = winMenuCamera;
    clockGame.start();
    animate();

    window.addEventListener("resize", onResize);
    window.addEventListener("keydown", onKeyDown);
    window.addEventListener("keyup", onKeyUp);

}

function simulateNextFrame(colisionTest, delta){
  for(var i = 0; i < colisionTest.length; i++)
    colisionTest[i].movement_Equation(delta);
}

function update(delta){
  var colisionTest = [];
  colisionTest = colisionTest.concat([ship], aliens, bullets);
  simulateNextFrame(colisionTest, delta);

  for(var i = 0; i < colisionTest.length; i++){
    for( var j=i+1; j < colisionTest.length; j ++){
      if(colisionTest[i].detect_colision(colisionTest[j])){
        colisionTest[i].colisionAction(colisionTest[j]);
        colisionTest[j].colisionAction(colisionTest[i]);
        break;
      }
    }
  }
  for(var z = 0; z < colisionTest.length; z++){
    colisionTest[z].checkIfStuck();
    colisionTest[z].position.x = colisionTest[z].nextPosition.x;
    colisionTest[z].position.y = colisionTest[z].nextPosition.y;
    colisionTest[z].position.z = colisionTest[z].nextPosition.z;
  }
}

function animate() {
    'use strict';
    stats.begin();

    var deltaT = clockGame.getDelta();

    update(deltaT);

    spotLight.target.position.set(ship.position.x, ship.up.y, ship.up.z);
    spotLight.target.updateMatrixWorld();
    //spotLightHelper.update();

    render();

    stats.end();
    requestAnimationFrame(animate);
}

function createBulletsMaterial(){
  var bulletBasicMaterial = new THREE.MeshBasicMaterial({ color: 0xfa6400});
  var bulletPhongMaterial = new THREE.MeshPhongMaterial({ color: 0xfa64ff});
  var bulletLambertMaterial = new THREE.MeshLambertMaterial({color: 0x7cdbd5});
  var bulletMaterials = [bulletBasicMaterial, bulletPhongMaterial, bulletLambertMaterial];
  materiais.push(bulletMaterials);
}

function createShipMaterial(){
  var shipBasicMaterial = new THREE.MeshBasicMaterial({ color: 0xfa040f});
  shipBasicMaterial.side = THREE.DoubleSide;
  var shipPhongMaterial = new THREE.MeshPhongMaterial({ color: 0xFF0F2B, specular: 0xFF5E5E, shininess: 40});
  shipPhongMaterial.side = THREE.DoubleSide;
  var shipLambertMaterial = new THREE.MeshLambertMaterial({color: 0x006a51});
  shipLambertMaterial.side = THREE.DoubleSide;
  var shipMaterials = [shipBasicMaterial, shipPhongMaterial, shipLambertMaterial];
  materiais.push(shipMaterials);
}

function createAlienMateriais(){
  var alienMateriais = [];

  var alienBasicBody = new THREE.MeshBasicMaterial({ color: 0x1ec876});

  var alienPhongBody = new THREE.MeshPhongMaterial({ color: 0x69ED66, specular: 0x549156, shininess: 40});

  var alienLambertBody = new THREE.MeshLambertMaterial({color: 0x7cdbd5});

  var alienbodymaterials = [alienBasicBody,alienPhongBody,alienLambertBody];

  alienMateriais.push(alienbodymaterials);


  var alienBasicEye = new THREE.MeshBasicMaterial({ color: 0xff4c4c});

  var alienPhongEye = new THREE.MeshPhongMaterial({ color: 0xFF2100, specular: 0xFF9000, shininess: 40});

  var alienLambertEye = new THREE.MeshLambertMaterial({color: 0xf9be02});

  var alieneyematerials = [alienBasicEye,alienPhongEye,alienLambertEye];

  alienMateriais.push(alieneyematerials);

  var alienBasicLeg = new THREE.MeshBasicMaterial({ color: 0x7777ff});

  var alienPhongLeg = new THREE.MeshPhongMaterial({ color: 0x4596FF, specular: 0xA6D4FF, shininess: 40});

  var alienLambertLeg = new THREE.MeshLambertMaterial({color:0x7e5f00});

  var alienLegMaterials = [alienBasicLeg,alienPhongLeg,alienLambertLeg];

  alienMateriais.push(alienLegMaterials);
  materiais.push(alienMateriais);
}
