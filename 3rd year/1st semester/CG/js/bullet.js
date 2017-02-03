class Bullet extends Element{
    constructor(x, y, z) {
      super();
      this.createBullet(x, y, z);
      this.speed = [0, 20];
      this.colisionRadius = 1.4;
      this.nextPosition.set(this.position.x, this.position.y, this.position.z);
      this.radiusColision = 2;
    }

    checkIfStuck() {
      if (Math.abs(this.nextPosition.x) >= fieldWidth / 2 - this.radiusColision) {
          this.nextPosition.x = Math.sign(this.position.x)*(fieldWidth / 2 - this.radiusColision);
          this.set_speedX(0);
      }
      if (Math.abs(this.nextPosition.y) >= fieldHeight / 2 - this.radiusColision) {
          this.nextPosition.y = Math.sign(this.position.y)*(fieldHeight / 2 - this.radiusColision);
          this.set_speedY(0);
          this.deleteFromArray();
          scene.remove(this);
      }

    }

    deleteFromArray(){
      for(var i = 0; i < bullets.length; i++){
        if(this == bullets[i])
          bullets.splice(i, 1);
      }
    }

    colisionAction(obj){
      if(obj instanceof Alien){
        this.deleteFromArray();
        scene.remove(this);
      }
    }


    createBullet(x, y, z) {
       'use strict'

       var geometry = new THREE.SphereGeometry(1.4, 4, 4, 0, Math.PI * 2, 0, Math.PI * 2);
       var material;
       if(lightingEnable){
         material = materiais[2][1];
       }
       else if(!phong_flag){
         material = materiais[2][2];
       }
       else{
         material = materiais[2][0];
       }
       var bullet = new THREE.Mesh(geometry, material);
       scene.add(bullet);

       this.position.x = x;
       this.position.y = y;
       this.position.z = z;

       this.add(bullet);

       scene.add(this);
    }

    changeMaterialToBasic(){
        this.children[0].material = materiais[2][0];
    }
    changeMaterialToPhong(){
        this.children[0].material = materiais[2][1];

    }
    changeMaterialToLambert(){
        this.children[0].material = materiais[2][2];

    }
}
