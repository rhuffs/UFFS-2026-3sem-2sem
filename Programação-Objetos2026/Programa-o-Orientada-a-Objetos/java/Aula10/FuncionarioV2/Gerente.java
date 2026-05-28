public class Gerente extends Funcionario {
    
    private double bonus;

    public Gerente(double salario, double bonus){//PARA FAZER O CONSTRUTOR DO GERENTE TER SALARIO, TEMOS QUE PEGAR DA SUPER CLASSE FUNCIONARIO
        super(salario);//SUPER É USADOO PARA ACESSAR METODOS VINDOS DA HERANÇA // É NECESSARIO O SUPER SER A PRIMEIRA COISA CHAMADA
        this.bonus = bonus;
    }
    
    
    @Override
    public double calcRemum(){
        return super.calcRemum() + this.bonus; //super serve para acessar os metodos da super classe
    }
}
