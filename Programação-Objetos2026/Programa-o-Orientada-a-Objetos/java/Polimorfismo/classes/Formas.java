abstract class Formas {
    private int x;
    private int y;

    public int getX(){
        return this.x;
    }
    
    public void setX(int x){
        this.x = x;
    }

    public int getY(){
        return this.y;
    }
    
    public void setY(int y){
        this.y = y;
    }
    
    abstract double CalculaArea();
    abstract double CalcularPerimetro();
}
