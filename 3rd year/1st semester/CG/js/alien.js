class Alien extends Element{
    constructor(x,y,z) {
      super();
      this.createAlien(x,y,z); //height: 10 and width: 12.5
      this.speed = [20, 20];
      this.colisionRadius = 6.5;
      this.nextPosition.set(this.position.x, this.position.y, this.position.z);
    }

    checkIfStuck() {
      if (Math.abs(this.nextPosition.x) > fieldWidth / 2 - this.colisionRadius) {
          this.nextPosition.set(this.position.x, this.position.y, this.position.z);
          this.set_speedX(-1*this.get_speedX());
      }
      if (Math.abs(this.nextPosition.y) > fieldHeight / 2 - this.colisionRadius) {
          this.nextPosition.set(this.position.x, this.position.y, this.position.z);
          this.set_speedY(-1*this.get_speedY());
      }
    }

    deleteFromArray(){
      for(var i = 0; i < aliens.length; i++){
        if(this == aliens[i])
          aliens.splice(i, 1);
      }
    }

    colisionAction(obj){
      if(obj instanceof Alien){
        this.set_speedY(-1*this.get_speedY());
        this.set_speedX(-1*this.get_speedX());
        this.nextPosition.set(this.position.x, this.position.y, this.position.z);
      }
      else if(obj instanceof Bullet){
        this.deleteFromArray();
        scene.remove(this);
      }
      else if(obj instanceof Ship){
        this.set_speedY(-1*this.get_speedY());
        this.set_speedX(-1*this.get_speedX());
        this.nextPosition.set(this.position.x, this.position.y, this.position.z);
      }
    }



    createAlien(x, y, z) {
        'use strict';


        this.createAlienHead(0, 0, 0);
        this.createAlienHair(0, 0, 0);
        this.addAlienLeg(-3, 0, 0);
        this.addAlienLeg(0, 0, 0);
        this.addAlienLeg(3, 0, 0);
        this.addAlienArm(0, 0, 0, -1);
        this.addAlienArm(0, 0, 0, 1);
        this.createAlienEyes(0, 0, 0);
        /*this.createSphere(0, 0, 0);*/
        scene.add(this);

        this.position.x = x;
        this.position.y = y;
        this.position.z = z;
    }

    createAlienHead(x, y, z) {
        'use strict';
        var geometry = new THREE.CubeGeometry(7.5, 7.5, 3.25);

        var material = materiais[0][0][1];

        var mesh = new THREE.Mesh(geometry, material);
        mesh.position.set(x, y, z);
        this.add(mesh);
    }
    createAlienHair(x, y, z) {
      var material = materiais[0][0][1];
      var geometry = new THREE.CubeGeometry(4.5, 1.25, 3.25);
      var mesh = new THREE.Mesh(geometry, material);
      mesh.position.set(x, y + 4.375, z);
      this.add(mesh);
    }

    createAlienEyes(x, y, z){

        var geometry = new THREE.CubeGeometry(1.5, 1.5, 0.5);
        var material = materiais[0][1][1];
        var mesh = new THREE.Mesh(geometry, material);
        mesh.position.set(x + 1.5, y +0.75, z + 2.25);

        this.add(mesh);

        var geometry = new THREE.CubeGeometry(1.5, 1.5, 0.5);
        var mesh = new THREE.Mesh(geometry, material);
        mesh.position.set( x - 1.5, y +0.75, z + 2.25);
        this.add(mesh);
      }

    addAlienLeg(x, y, z) {
        'use strict';

        var material = materiais[0][2][1];

        var geometry = new THREE.CubeGeometry(1.5, 1.25, 3.25);
        var mesh = new THREE.Mesh(geometry, material);
        mesh.position.set(x, y - 4.375, z);
        this.add(mesh);
      }

    addAlienArm(x, y, z, side) {
        'use strict';
        var geometry = new THREE.CubeGeometry(1.25, 1.25, 3.25);
        var material = materiais[0][0][1];
        var mesh = new THREE.Mesh(geometry, material);
        if (side == 1) {
            mesh.position.set(x + 4.375, y, z);
        }
        if (side == -1) {
            mesh.position.set(x - 4.375, y, z);
        }
        this.add(mesh);

        var geometry = new THREE.CubeGeometry(1.25, 2.5, 3.25);
        var mesh = new THREE.Mesh(geometry, material);
        if (side == 1) {
            mesh.position.set(x + 5.625, y + 0.625, z);
        }
        if (side == -1) {
            mesh.position.set(x - 5.625, y + 0.625, z);
        }
        this.add(mesh);
    }

    createSphere(x, y, z) {
       'use strict'

       var geometry = new THREE.SphereGeometry(6.5, 8, 8);
       var material = new THREE.MeshNormalMaterial({
           color: 0x000000,
           wireframe: true
       });
       var sphere = new THREE.Mesh(geometry, material);
       scene.add(sphere);


       this.position.x = x;
       this.position.y = y;
       this.position.z = z;

       this.add(sphere);

     }


    changeMaterialToBasic(){
        this.children[0].material = materiais[0][0][0];
        this.children[1].material = materiais[0][0][0];
        this.children[2].material = materiais[0][2][0];
        this.children[3].material = materiais[0][2][0];
        this.children[4].material = materiais[0][2][0];
        this.children[5].material = materiais[0][0][0];
        this.children[6].material = materiais[0][0][0];
        this.children[7].material = materiais[0][0][0];
        this.children[8].material = materiais[0][0][0];
        this.children[9].material = materiais[0][1][0];
        this.children[10].material = materiais[0][1][0];
    }

    changeMaterialToPhong(){
        this.children[0].material = materiais[0][0][1];
        this.children[1].material = materiais[0][0][1];
        this.children[2].material = materiais[0][2][1];
        this.children[3].material = materiais[0][2][1];
        this.children[4].material = materiais[0][2][1];
        this.children[5].material = materiais[0][0][1];
        this.children[6].material = materiais[0][0][1];
        this.children[7].material = materiais[0][0][1];
        this.children[8].material = materiais[0][0][1];
        this.children[9].material = materiais[0][1][1];
        this.children[10].material = materiais[0][1][1];
    }

    changeMaterialToLambert(){
        this.children[0].material = materiais[0][0][2];
        this.children[1].material = materiais[0][0][2];
        this.children[2].material = materiais[0][2][2];
        this.children[3].material = materiais[0][2][2];
        this.children[4].material = materiais[0][2][2];
        this.children[5].material = materiais[0][0][2];
        this.children[6].material = materiais[0][0][2];
        this.children[7].material = materiais[0][0][2];
        this.children[8].material = materiais[0][0][2];
        this.children[9].material = materiais[0][1][2];
        this.children[10].material = materiais[0][1][2];
    }
};
