public class Funcionario {
    private double salario;



    public double getSalario(){
        return this.salario;
    }

    public void setSalario(double salario){
        this.salario = salario;
    }

    public double calcRemum() {
        return this.salario + 1000.0;
    }
}
