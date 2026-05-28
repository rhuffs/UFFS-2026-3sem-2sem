import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Agenda agenda = new Agenda();
        Pessoa pessoa1 = new Pessoa();
        Scanner sc = new Scanner(System.in);
        

        System.out.println("Digite os dados da 1a. Pessoa:");
        System.out.println("Digite o nome:");
        pessoa1.nome = sc.nextLine();

        Data data1 = new Data();
        System.out.println("Digite o dia de nascimento");
        data1.dia = sc.nextInt();

        System.out.println("Digite o Mês de nascimento");
        data1.mes = sc.nextInt();

        System.out.println("Digite o Ano de nascimento");
        data1.ano = sc.nextInt();

        pessoa1.dataNasc = data1;


        Contato contato1 = new Contato();
        System.out.println("Digite os dados do primeiro contato");
        System.out.println("Digite o numero :");
        String str = sc.nextLine(); // ignora o enter do int acima
        contato1.numero = sc.nextLine();
        System.out.println(" É Whatsapp (1- Sim, 0- Não)");
        int res = sc.nextInt();
        if (res == 1){
            contato1.ehWhats = true;
        } else {
            contato1.ehWhats = false;
        }

        System.out.println(" É Telegram (1- Sim, 0- Não)");
        if (res == 0){
            contato1.ehTelegram = true;
        } else {
            contato1.ehTelegram = false;
        }

        pessoa1.cadastraContato(contato1);
        Contato contato2 = new Contato();
        contato2.numero = "(99)999999999";
        contato2.ehWhats = true;
        contato2.ehTelegram = false;

        pessoa1.listaContato(contato1);
        pess


        sc.close();
}   


}
