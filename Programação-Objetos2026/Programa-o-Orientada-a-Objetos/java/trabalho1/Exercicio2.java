import java.util.Scanner;

public class Exercicio2 {

    public static void main(String[] args) {
        int N; 
        int novo  ;  
        int antigo = 0; 
        int atual = 1;
        Scanner sc = new Scanner(System.in);

        System.out.println("Digite um numero:");
        N = sc.nextInt();
        int i;

        for (i = 0; i <= N; i++){
            System.out.println(antigo);
            novo = antigo + atual;
            antigo = atual;
            atual = novo;
        }
        sc.close();

    }

}