import java.util.Scanner;

public class Exercicio10 {
    public static void main(String[] args) {
        int n;
        System.err.println("Digite um numero: ");
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();

        int nota100 = n / 100;
        n = n % 100;

        int nota50 = n / 50;
        n = n % 50;

        int nota20 = n / 20;
        n = n % 20;

        int nota10 = n / 10;
        n = n % 10;

        int nota5 = n / 5;
        n = n % 5;

        int nota2 = n / 2;
        n = n % 2;

        int nota1 = n;

        System.out.println("\n notas de 100: " + nota100 + 
        "\n notas de 50: " + nota50 +
        "\n notas de 20: " + nota20 + 
        "\n notas de 10: " + nota10 +
        "\n notas de 5: " + nota5 +
        "\n notas de 2: " + nota2 +
        "\n notas de 1: " + nota1);
        sc.close();
    }
}
