public class Main {
    public static void main(String[] args) {
        Funcionario f = new Funcionario(8000);
        
        System.out.println("Remuneração: " + f.calcRemum());
        Gerente g = new Gerente(8000,2000);

        System.out.println("Remuneração: " + g.calcRemum());
    }
}
