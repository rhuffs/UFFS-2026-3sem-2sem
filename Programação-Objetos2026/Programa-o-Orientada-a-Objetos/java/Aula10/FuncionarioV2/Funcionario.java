public class Funcionario {
    private double salario;

    public Funcionario(double salario){
        this.salario = salario;
    }
    public double calcRemum() {
        return this.salario + 1000.0;
    }
}
