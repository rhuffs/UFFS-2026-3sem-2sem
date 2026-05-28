
public class Main {
    public static void main(String[] args) {
        Pessoa e = new Estudante("Rhuan", "Ciencias da Computacao");
        System.out.println(e.getNome());
        System.out.println(e.getDescricao());
        Pessoa f = new Empregado("Rhamon", "Costureiro");
        System.out.println(f.getNome());
        System.out.println(f.getDescricao());
        }
}
