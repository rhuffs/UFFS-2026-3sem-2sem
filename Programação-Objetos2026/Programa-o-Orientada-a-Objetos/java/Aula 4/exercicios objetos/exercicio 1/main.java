import java.util.Scanner;

public class main {
    public static void main(String[] args) {
    
        Autor a;
        a = new Autor();


        Scanner sc = new Scanner(System.in);
        System.out.println("Digite o nome do autor: ");
        a.nome = sc.nextLine();
        System.out.println(a.nome);
        System.out.println("Digite o Id do autor: ");
        Scanner sc1 = new Scanner(System.in);
        a.id = sc1.nextInt();
        System.out.println(a.id);
        sc.close();
        sc1.close();
        
    }
}
