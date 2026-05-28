

public class Pessoa {
    String nome;
    Data dataNasc;
    Contato[] contatos = new Contato[4];
    int numContatos = 0;


    void cadastraContato(Contato c){
        if (numContatos == 4){
            System.out.println("Número máximo de contatos atingido");
            return;
        }
        else{
            contatos[numContatos] = c;
            numContatos++;
        }
    }
    void listaContato(){
        for (int i = 0; i < numContatos; i++){
            contatos[i].imprime();
    }   
    }
}