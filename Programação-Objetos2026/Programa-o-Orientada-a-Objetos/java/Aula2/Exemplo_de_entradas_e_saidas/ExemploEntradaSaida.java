import java.util.Scanner;

public class ExemploEntradaSaida {
    public static void main(String[] args) {
        // Entrada 
        Scanner sc = new Scanner(System.in);

        System.out.println("Digite um numero inteiro: ");
        int a1 = sc.nextInt();

        System.out.println("a1: " + a1);

        sc.close();
    }
}
