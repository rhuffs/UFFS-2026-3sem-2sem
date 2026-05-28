public class Retangulo extends Formas{
    private double base;
    private double altura;

    // public Retangulo(double base, double altura){
    //     this.base = base;
    //     this.altura = altura;
    // }

    @Override
    public double CalculaArea() {
        System.out.println("Area do Retangulo\n");
        return base *altura;
    }

    @Override
    public double CalcularPerimetro(){
        System.out.println("Perimetro do Retangulo\n");
        return 2*base + 2*altura;
    }


}
