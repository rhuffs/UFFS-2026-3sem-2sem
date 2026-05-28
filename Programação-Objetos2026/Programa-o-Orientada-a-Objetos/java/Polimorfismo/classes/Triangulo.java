
public class Triangulo extends Formas {
    private double base;
    private double altura;

    // public Triangulo (double base, double altura){
    //     this.base = base; 
    //     this.altura = altura;
    // }

    @Override
    public double CalculaArea(){
        System.out.println("Area do triangulo\n");
        return (base * altura) / 2;
    }

    @Override
    public double CalcularPerimetro(){
        System.out.println("Perimetro do triangulo\n");
        return 0.0;
    }
}
