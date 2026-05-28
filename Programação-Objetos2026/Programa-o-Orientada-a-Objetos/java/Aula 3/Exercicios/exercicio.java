import java.util.Scanner;

public class exercicio {
    public static void main(String [] args ){
       int n1;
       System.out.println("digite um numero");
       
       Scanner sc = new Scanner(System.in);

       n1 = sc.nextInt();
       int i = 0;
       while (i <= n1){
        System.out.println(i);
        i++;
       }
       sc.close();
    }
}
