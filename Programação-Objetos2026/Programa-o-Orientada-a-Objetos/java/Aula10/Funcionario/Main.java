package java.Aula10.Funcionario;
public class Main {
    public static void main(String[] args) {
        Funcionario f = new Funcionario();
        f.setSalario(8000);
        System.out.println("Remuneração: " + f.calcRemum());
        Gerente g = new Gerente();
        g.setSalario(8000);
        g.setBonus(2000);
        System.out.println("Remuneração: " + g.calcRemum());
    }
}
