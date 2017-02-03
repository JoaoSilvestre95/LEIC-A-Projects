var AmbientLight, directionalLight, spotLight;
var lightsOn = true;
var spotOn = false;
var lightingEnable = true;
var phongLambert_flag = true; //Phong-true/Lambert-false
var stars_flag = true;
var stars = [];
function createAmbientLight(){
    directionalLight = new THREE.DirectionalLight( 0xD3D3D3, 1 );
		directionalLight.position.set(0,-40, 20);
		directionalLight.position.normalize();
		scene.add( directionalLight );
}

function createSpotLight(){
  spotLight = new THREE.SpotLight(0xffffff, 1, fieldHeight/2, Math.PI/4);
  spotLight.intensity = 0;
}

function manageStats(leter){
    switch (leter) {
      case 'n':
          changeDayNightMode();
          break;
      case 'l':
          enableDisableLighting();
          break;
      case 'g':
          changeLambertPhong();
          break;
      case 'c':
          handleStars();
          break;
      case 'h':
          switchSpotLight();
          break;
    }
}

function changeDayNightMode(){
    if(lightsOn){
        directionalLight.intensity = 0;
        lightsOn = false;
    }
    else{
        directionalLight.intensity = 1;
        lightsOn = true;
    }
}

function switchSpotLight(){
  if(spotOn){
      spotLight.intensity = 0;
      spotOn = false;
  }
  else{
      spotLight.intensity = 1;
      spotOn = true;
  }  
}

function activePhongMaterial(){
  for(var i = 0; i < aliens.length; i++)
    aliens[i].changeMaterialToPhong();

  for(var i = 0; i < bullets.length; i++)
    bullets[i].changeMaterialToPhong();

  ship.changeMaterialToPhong();
}

function activeLambertMaterial(){
  for(var i = 0; i < aliens.length; i++)
    aliens[i].changeMaterialToLambert();

  for(var i = 0; i < bullets.length; i++)
    bullets[i].changeMaterialToLambert();

  ship.changeMaterialToLambert();
}

function activeBasicMaterial(){
  for(var i = 0; i < aliens.length; i++)
    aliens[i].changeMaterialToBasic();

  for(var i = 0; i < bullets.length; i++)
    bullets[i].changeMaterialToBasic();

  ship.changeMaterialToBasic();
}

function enableDisableLighting(){
    if(lightingEnable){
        activeBasicMaterial()
        lightingEnable = false;
    }
    else{
      if(phongLambert_flag)
        activePhongMaterial();
      else
        activeLambertMaterial();
      lightingEnable = true;
    }
}

function changeLambertPhong() {
    if(phongLambert_flag){
      activeLambertMaterial();
      phongLambert_flag = false;
    }
    else{
      activePhongMaterial();
      phongLambert_flag = true;
    }
    lightingEnable = true;
}

function handleStars(){
    if(stars_flag){
      for(var i = 0; i < stars.length; i++)
        stars[i].intensity = 0;
      stars_flag = false;
    }
    else{
      for(var i = 0; i < stars.length; i++)
        stars[i].intensity = 0.5;
      stars_flag = true;
    }
}

function createStars(){
  var light = new THREE.PointLight( 0xffffff, 0.5, 50, 1 );
  light.position.set( -60, 20, 20 );
  scene.add( light );
  stars.push(light);
  var light = new THREE.PointLight( 0xffffff, 0.5, 50, 1 );
  light.position.set( 0, 20, 20 );
  scene.add( light );
  stars.push(light);
  var light = new THREE.PointLight( 0xffffff, 0.5, 50, 1 );
  light.position.set( 60, 20, 20 );
  scene.add( light );
  stars.push(light);
  var light = new THREE.PointLight( 0xffffff, 0.5, 50, 1 );
  light.position.set( -60, -20, 20 );
  scene.add( light );
  stars.push(light);
  var light = new THREE.PointLight( 0xffffff, 0.5, 50, 1 );
  light.position.set( 0, -20, 20 );
  scene.add( light );
  stars.push(light);
  var light = new THREE.PointLight( 0xffffff, 0.5, 50, 1 );
  light.position.set( 60, -20, 20 );
  scene.add( light );
  stars.push(light);
}
