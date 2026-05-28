
public class Quadrado extends Formas {
    private double lado;


    // public Quadrado(double lado){
    //     this.lado = lado;
    // }

    @Override
    public double CalculaArea(){
        System.out.println("Area do Quadrado\n");
        return  this.lado * this.lado;
    }

    @Override
    public double CalcularPerimetro(){
        System.out.println("Perimetro do Quadrado\n");
        return this.lado * 4;
    }
}
