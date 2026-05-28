package java.Aula10.Funcionario;
public class Gerente extends Funcionario {
    
    private double bonus;

    public double getBonus(){
        return this.bonus;
    }

    public void setBonus(double bonus){
        this.bonus = bonus;
    }

    @Override
    public double calcRemum(){
        return super.calcRemum() + this.bonus; //super serve para acessar os metodos da super classe
    }
}
