public class Circulo extends Formas {
    private double raio;

    // public Circulo (double raio){
    //     this.raio = raio;
    // }

    @Override
    public double CalculaArea(){
        System.out.println("Area do circulo\n");
        return 3.14 * raio * raio;
    }

    @Override
    public double CalcularPerimetro(){
        System.out.println("Cirfunferencia do Circulo\n");
        return 3.14 * (raio * 2);
    }

}
