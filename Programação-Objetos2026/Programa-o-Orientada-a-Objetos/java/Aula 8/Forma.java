public class Forma {
    protected int x;
    protected int y;

    public int getX(){
        return this.x;
    }

    public void setX(){
        this.x = x;
    }

    public int getY(){
        return this.y;
    }

    public void setY(){
        this.y = y;
    }


    private void imprimePosicao() {
        System.out.println(this.x);
        System.out.println(this.y);
    }
}
