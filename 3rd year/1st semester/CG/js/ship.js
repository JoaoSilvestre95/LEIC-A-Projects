class Ship extends Element {
    constructor(x, y, z) {
        super();
        this.AC = 50;
        this.MAX_SPEED = 50;
        this.createShip(x, y, z);
        this.colisionRadius = 5.5;
        this.nextPosition.set(this.position.x, this.position.y, this.position.z);
    }
    movement_Equation(delta){
      if(Math.abs(this.get_speedX()) > this.get_MAX_SPEED())
        this.set_speedX(Math.sign(this.get_speedX()) * this.get_MAX_SPEED()); //sign returns signal from speed (1 or -1)
      else if(Math.abs(this.get_speedX()) > 0 && Math.sign(this.get_speedX()) != Math.sign(this.get_speedX() + this.get_accelarationX() * delta)){ //stops if the current speed signal is different from the next one
        this.set_accelarationX(0);
        this.set_speedX(0);
      }
      this.set_speedX(this.get_speedX() + this.get_accelarationX() * delta);
      this.set_speedY(this.get_speedY() + this.get_accelarationY() * delta);
      this.nextPosition.x += this.get_speedX() * delta;
      this.nextPosition.y += this.get_speedY() * delta;

    }

    checkIfStuck() {
      if (Math.abs(this.nextPosition.x) > fieldWidth / 2 - this.colisionRadius) {
          this.nextPosition.set(Math.sign(this.position.x)*(fieldWidth / 2 - this.colisionRadius), this.position.y, this.position.z);
          this.set_speedX(0);
          this.set_accelarationX(0);
      }
    }

    colisionAction(obj){
      if(obj instanceof Alien){
        scene.remove(lives[0]);
        lives.splice(0,1);
        this.nextPosition.x = 0;
        this.set_speedX(0);
        this.set_accelarationX(0);
      }
    }
    get_AC() {
        return this.AC;
    }
    get_MAX_SPEED() {
        return this.MAX_SPEED;
    }

    createShip(x, y, z) {
        'use strict';

        var geometry = new THREE.Geometry();

        geometry.vertices.push(
          //body
          new THREE.Vector3(- 5,  1.5,  - 1.5), new THREE.Vector3(- 5,  1.5,  1.5),
          new THREE.Vector3(- 5, - 1.5, - 1.5), new THREE.Vector3(- 5,  -1.5,  1.5),
          new THREE.Vector3( 5,  - 1.5,  - 1.5), new THREE.Vector3( 5,  -1.5,  1.5),
          new THREE.Vector3( 5,  1.5,  - 1.5), new THREE.Vector3( 5,  1.5,  1.5),
          //cockpit
          new THREE.Vector3( 3.5,  1.5,  1), new THREE.Vector3( 3.5,  1.5, - 1),
          new THREE.Vector3( 3.5,  2.5,  1), new THREE.Vector3( 3.5,  2.5, - 1),
          new THREE.Vector3(- 3.5,  1.5,  1), new THREE.Vector3(- 3.5,  2.5,  1),
          new THREE.Vector3(- 3.5,  1.5, - 1), new THREE.Vector3(- 3.5,  2.5, - 1),
          //Ammo
          new THREE.Vector3( 0.75,  2.5,  1), new THREE.Vector3( 0.75,  4.5,  1),
          new THREE.Vector3( 0.75,  2.5, - 1), new THREE.Vector3( 0.75,  4.5, - 1),
          new THREE.Vector3(- 0.75,  2.5,  1), new THREE.Vector3(- 0.75,  2.5, - 1),
          new THREE.Vector3(- 0.75,  4.5,  1), new THREE.Vector3(- 0.75,  4.5, - 1),
          //ShipJet1
          new THREE.Vector3(- 4, - 1.5,  1), new THREE.Vector3(- 4, - 2,  1),
          new THREE.Vector3(- 4, - 2, - 1), new THREE.Vector3(- 4, - 1.5, - 1),
          new THREE.Vector3(- 2, - 1.5,  1), new THREE.Vector3(- 2, - 1.5, - 1),
          new THREE.Vector3(- 2, - 2,  1), new THREE.Vector3(- 2, - 2, - 1),
          //ShipJet2
          new THREE.Vector3( 4, - 1.5,  1), new THREE.Vector3( 4, - 2,  1),
          new THREE.Vector3( 4, - 2, - 1), new THREE.Vector3( 4, - 1.5, - 1),
          new THREE.Vector3( 2, - 1.5,  1), new THREE.Vector3( 2, - 1.5, - 1),
          new THREE.Vector3( 2, - 2,  1), new THREE.Vector3( 2, - 2, - 1),
          //ShipFire1
          new THREE.Vector3(- 4, - 2, - 1), new THREE.Vector3(- 4, - 2,  1),
          new THREE.Vector3(- 2, - 2,  1), new THREE.Vector3(- 2, - 2, - 1),
          new THREE.Vector3(- 3, - 4, z),
          //ShipFire2
          new THREE.Vector3( 4, - 2, - 1), new THREE.Vector3( 4, - 2,  1),
          new THREE.Vector3( 2, - 2,  1), new THREE.Vector3( 2, - 2, - 1),
          new THREE.Vector3( 3, - 4, z)
        );

        geometry.faces.push(
          //Body
          new THREE.Face3( 3, 2, 0 ), new THREE.Face3( 3, 0, 1),
          new THREE.Face3( 7, 1, 3), new THREE.Face3( 7, 3, 5),
          new THREE.Face3( 4, 5, 3 ), new THREE.Face3( 4, 3, 2),
          new THREE.Face3( 2, 4, 6 ), new THREE.Face3( 2, 6, 0),
          new THREE.Face3( 1, 0, 6 ), new THREE.Face3( 1, 6, 7),
          new THREE.Face3( 6, 4, 5 ), new THREE.Face3( 6, 5, 7),
          //Cockpit
          new THREE.Face3( 14, 12, 13 ), new THREE.Face3( 13, 15, 14 ),
          new THREE.Face3( 8, 9, 11 ), new THREE.Face3( 11, 10, 8 ),
          new THREE.Face3( 12, 8, 10 ), new THREE.Face3( 10, 13, 12),
          new THREE.Face3( 15, 14, 9 ), new THREE.Face3( 9, 11, 15),
          new THREE.Face3( 8, 12, 14 ), new THREE.Face3( 14, 9, 8),
          new THREE.Face3( 13, 15, 11 ), new THREE.Face3( 11, 10, 13),
          //Ammo
          new THREE.Face3( 20, 22, 23 ), new THREE.Face3( 23, 21, 20 ),
          new THREE.Face3( 17, 19, 18 ), new THREE.Face3( 18, 16, 17 ),
          new THREE.Face3( 22, 20, 16 ), new THREE.Face3( 16, 17, 22),
          new THREE.Face3( 19, 23, 21 ), new THREE.Face3( 21, 18, 19),
          new THREE.Face3( 17, 19, 23), new THREE.Face3( 23, 22, 17 ),
          new THREE.Face3( 20, 16, 18 ), new THREE.Face3( 18, 21, 20),
          //ShipJet1
          new THREE.Face3( 24, 27, 26 ), new THREE.Face3( 26, 25, 24 ),
          new THREE.Face3( 29, 31, 30 ), new THREE.Face3( 30, 28, 29 ),
          new THREE.Face3( 24, 25, 30 ), new THREE.Face3( 30, 28, 24),
          new THREE.Face3( 26, 31, 29 ), new THREE.Face3( 29, 27, 26),
          new THREE.Face3( 26, 25, 30 ), new THREE.Face3( 30, 31, 26),
          new THREE.Face3( 24, 27, 29 ), new THREE.Face3( 29, 28, 24),
          //ShipJet2
          new THREE.Face3( 36, 38, 39 ), new THREE.Face3( 39, 37, 36 ),
          new THREE.Face3( 33, 34, 35 ), new THREE.Face3( 35, 32, 33 ),
          new THREE.Face3( 36, 38, 33 ), new THREE.Face3( 33, 32, 36),
          new THREE.Face3( 37, 35, 39 ), new THREE.Face3( 39, 34, 37),
          new THREE.Face3( 39, 38, 33 ), new THREE.Face3( 33, 34, 39),
          new THREE.Face3( 36, 37, 35 ), new THREE.Face3( 35, 32, 36),

          //ShipFire1
          new THREE.Face3( 40, 41, 42 ), new THREE.Face3( 42, 43, 40 ),
          new THREE.Face3( 41, 42, 44 ), new THREE.Face3( 44, 40, 41 ),
          new THREE.Face3( 43, 40, 44 ), new THREE.Face3( 44, 42, 43),
          //ShipFire2
          new THREE.Face3( 48, 47, 46 ), new THREE.Face3( 46, 45, 48),
          new THREE.Face3( 47, 46, 49 ), new THREE.Face3( 49, 48, 47),
          new THREE.Face3( 45, 48, 49 ), new THREE.Face3( 49, 46, 45)
        );
        geometry.computeFaceNormals();

        var material = materiais[1][1];
        material.side = THREE.DoubleSide;
        var mesh = new THREE.Mesh(geometry, material);
        mesh.position.set(0,0,0);
        this.add(mesh);

        this.position.x = x;
        this.position.y = y;
        this.position.z = z;

        scene.add(this);

        /*this.addShipBody(material, 0, 0, 0);
        this.addShipJet(material, 3, 0, 0);
        this.addShipJet(material, -3, 0, 0);
        this.addJetFire(material, 3, 0, 0);
        this.addJetFire(material, -3, 0, 0);
        this.addShipCockPit(material, 0, 0, 0);
        this.addShipAmmo(material, 0, 0, 0);*/
    }

    addShipBody(material, x, y, z) {
        'use strict';

        var geometry = new THREE.CubeGeometry(10, 3, 3);
        var mesh = new THREE.Mesh(geometry, material);
        mesh.position.set(x, y, z);

        this.add(mesh);
    }

    addShipJet(material, x, y, z) {
        'use strict';
        var geometry = new THREE.CylinderGeometry(1, 1, 0.5, 16);

        var mesh = new THREE.Mesh(geometry, material);
        mesh.position.set(x, y - 1.75, z);

        this.add(mesh);

    }

    addJetFire(material, x, y, z) {
        'use strict';

        var geometry = new THREE.ConeBufferGeometry(0.75, 2, 8);
        geometry.rotateX(Math.PI);
        var mesh = new THREE.Mesh(geometry, material);
        mesh.position.set(x, y -3, z);

        this.add(mesh);

    }

    addShipCockPit(material, x, y, z) {
        'use strict';
        var geometry = new THREE.CubeGeometry(7, 1, 2);


        var mesh = new THREE.Mesh(geometry, material);
        mesh.position.set(x, y + 2, z);

        this.add(mesh);
    }

    addShipAmmo(material, x, y, z) {
        'use strict';

        var geometry = new THREE.CubeGeometry(1.5, 2, 2);
        var mesh = new THREE.Mesh(geometry, material);
        mesh.position.set(x, y + 3.5, z);

        this.add(mesh);

    }

    changeMaterialToBasic(){
        this.children[0].material = materiais[1][0];
    }
    changeMaterialToPhong(){
        this.children[0].material = materiais[1][1];

    }
    changeMaterialToLambert(){
        this.children[0].material = materiais[1][2];

    }
}
