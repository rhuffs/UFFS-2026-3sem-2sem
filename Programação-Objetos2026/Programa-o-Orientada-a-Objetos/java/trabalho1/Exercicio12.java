import java.util.Random;
import java.util.Scanner;

public class Exercicio12 {
    public static void main(String[] args) {

        Random random = new Random();
        Scanner scanner = new Scanner(System.in);
        int n = random.nextInt(101);
        int chute = 0;

        while (chute != n) {
            System.out.print("Chute um numero de 1 a 100: ");
            chute = scanner.nextInt();

            if (chute > n) {
                System.out.println("Para baixo");
            } 
            else if (chute < n) {
                System.out.println("Para cima");
            } 
            else {
                System.out.println("Acertou!!!!!!!");
            }
        }

        scanner.close();
    }
}