class Element extends THREE.Object3D{
    constructor() {
      super();
      this.speed = [0, 0];
      this.accelaration = [0, 0];
      this.colisionRadius;
      this.nextPosition = new THREE.Vector3;

    }


    movement_Equation(delta){
      this.set_speedX(this.get_speedX() + this.get_accelarationX() * delta);
      this.set_speedY(this.get_speedY() + this.get_accelarationY() * delta);
      this.nextPosition.x += this.get_speedX() * delta;
      this.nextPosition.y += this.get_speedY() * delta;
    }

    detect_colision(object){
      if(this.colisionRadius + object.get_colisionRadius() >= this.nextPosition.distanceTo(object.get_colisionNextPosition()))
        return true;
      return false;
    }

    colisionAction(){}
    checkIfStuck(){}

    get_colisionRadius(){
      return this.colisionRadius;
    }
    set_colisionRadius(radius){
      this.colisionRadius = radius;
    }

    get_colisionNextPosition(){
      return this.nextPosition;
    }
    set_colisionNextPosition(center){
      this.nextPosition = center;
    }
    get_speedX(){
      return this.speed[0];
    }
    get_speedY(){
      return this.speed[1];
    }

    set_speedX(speed){
      this.speed[0] = speed;
    }
    set_speedY(speed){
      this.speed[1] = speed;
    }

    get_accelarationX(){
      return this.accelaration[0];
    }
    get_accelarationY(){
      return this.accelaration[1];
    }

    set_accelarationX(accelaration){
      this.accelaration[0] = accelaration;
    }
    set_accelarationY(accelaration){
      this.accelaration[1] = accelaration;
    }
    changeMaterialToBasic(){}
    changeMaterialToPhong(){}
};
