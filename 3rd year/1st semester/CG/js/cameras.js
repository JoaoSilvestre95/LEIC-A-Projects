var livesCamera, pauseCamera, endMenuCamera, winMenuCamera;
var ortogonalcamera, thirdpersoncamera, perspectivecamera, scene, renderer

function createWinMenuCamera(eyeX, eyeY, eyeZ){
  'use strict';

  var aspectRatio = window.innerWidth / window.innerHeight;

  if(aspectRatio >= (80/60))
      winMenuCamera = new THREE.OrthographicCamera((-60*aspectRatio)/2, (60*aspectRatio)/2, 60/2, -60/2, -1, 50);
  else
      winMenuCamera = new THREE.OrthographicCamera((-80)/2, (80)/2, (80/aspectRatio)/2, (-80/aspectRatio)/2, -1, 50);
  winMenuCamera.position.x = eyeX;
  winMenuCamera.position.y = eyeY;
  winMenuCamera.position.z = eyeZ;
}

function createEndMenuCamera(eyeX, eyeY, eyeZ){
  'use strict';

  var aspectRatio = window.innerWidth / window.innerHeight;

  if(aspectRatio >= (80/53))
      endMenuCamera = new THREE.OrthographicCamera((-53*aspectRatio)/2, (53*aspectRatio)/2, 53/2, -53/2, -1, 50);
  else
      endMenuCamera = new THREE.OrthographicCamera((-80)/2, (80)/2, (80/aspectRatio)/2, (-80/aspectRatio)/2, -1, 50);
  endMenuCamera.position.x = eyeX;
  endMenuCamera.position.y = eyeY;
  endMenuCamera.position.z = eyeZ;
}
function createPauseCamera(eyeX, eyeY, eyeZ){
  'use strict';

  var aspectRatio = window.innerWidth / window.innerHeight;

  if(aspectRatio >= (80/16))
      pauseCamera = new THREE.OrthographicCamera((-16*aspectRatio)/2, (16*aspectRatio)/2, 16/2, -16/2, -1, 50);
  else
      pauseCamera = new THREE.OrthographicCamera((-80)/2, (80)/2, (80/aspectRatio)/2, (-80/aspectRatio)/2, -1, 50);
  pauseCamera.position.x = eyeX;
  pauseCamera.position.y = eyeY;
  pauseCamera.position.z = eyeZ;
}
function createLivesCamera(eyeX, eyeY, eyeZ){
  'use strict';

  var aspectRatio = window.innerWidth / window.innerHeight;

  if(aspectRatio >= (40/9.5))
      livesCamera = new THREE.OrthographicCamera((-9.5*aspectRatio)/2, (9.5*aspectRatio)/2, 9.5/2, -9.5/2, -1, 50);
  else
      livesCamera = new THREE.OrthographicCamera((-40)/2, (40)/2, (40/aspectRatio)/2, (-40/aspectRatio)/2, -1, 50);
  livesCamera.position.x = eyeX;
  livesCamera.position.y = eyeY;
  livesCamera.position.z = eyeZ;
}

function createOrtogonalCamera() {
    'use strict';

    var aspectRatio = window.innerWidth / window.innerHeight;

    if(aspectRatio >= (fieldWidth/fieldHeight))
        ortogonalcamera = new THREE.OrthographicCamera((-fieldHeight*aspectRatio)/2, (fieldHeight*aspectRatio)/2, fieldHeight/2, -fieldHeight/2, -1, 50);
    else
        ortogonalcamera = new THREE.OrthographicCamera((-fieldWidth)/2, (fieldWidth)/2, (fieldWidth/aspectRatio)/2, (-fieldWidth/aspectRatio)/2, -1, 50);
    ortogonalcamera.position.x = 0;
    ortogonalcamera.position.y = 0;
    ortogonalcamera.position.z = 20;
}

function createPerspectiveCamera(){
    'use strict';

    perspectivecamera = new THREE.PerspectiveCamera(90, window.innerWidth / window.innerHeight, 1, 1000);

    perspectivecamera.position.x = 0;
    perspectivecamera.position.y = -30;
    perspectivecamera.position.z = 55;
    perspectivecamera.lookAt(scene.position);
}


function createThirdpersonCamera(){
    'use strict';
    thirdpersoncamera = new THREE.PerspectiveCamera(90, window.innerWidth / window.innerHeight, 1, 1000);

    thirdpersoncamera.position.x = 0;
    thirdpersoncamera.position.y = -25;
    thirdpersoncamera.position.z = 10;
    thirdpersoncamera.lookAt(scene.position);
}


function onResize() {
    'use strict';

    renderer.setSize(window.innerWidth, window.innerHeight);
    var newAspectRatio = window.innerWidth / window.innerHeight;

    var camera = views.viewGame.camera;

    if(camera_flag == 1){
      if (newAspectRatio >= (fieldWidth/fieldHeight)) {
          camera.bottom = -fieldHeight/2;
          camera.top = fieldHeight/2;
          camera.right = (fieldHeight*newAspectRatio)/2;
          camera.left = (-fieldHeight*newAspectRatio)/2;
      }
      else{
          camera.bottom = (-fieldWidth/newAspectRatio)/2;
          camera.top = (fieldWidth/newAspectRatio)/2;
          camera.right = fieldWidth/2;
          camera.left = -fieldWidth/2;
      }
    }
    else{
        camera.aspect = newAspectRatio;
        camera.lookAt( scene.position );
    }
    camera.updateProjectionMatrix();
}


function handleAliensRotation(){
  if(aliens.length !=0){
    if ((camera_flag == 2 || camera_flag == 3 )&& aliens[1].rotation.x <= 0){
      for(var i = 0; i < aliens.length; i++){
        aliens[i].rotateX(Math.PI/2);
      }
    }
    if (camera_flag == 1 && aliens[1].rotation.x == 1.5707963267948963){
      for(var i = 0; i < aliens.length; i++){
        aliens[i].rotateX(-Math.PI/2);
      }
    }
  }
}
