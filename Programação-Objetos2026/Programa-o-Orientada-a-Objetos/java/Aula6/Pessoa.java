class Pessoa {
    int idade;
    String nome;
    static int numObjsPessoa = 0;

    public Pessoa() {
        this(0);
    }
    public Pessoa(int i) {
        Pessoa.numObjsPessoa++;
        this.idade = i;
        this.nome = new String("Alguém");
    }

    void imprime(){
        System.out.println("Idade :" + idade);
        System.out.println("Nome" + nome);

    }

    static void imprimeNumObjsPessoa(){
        System.err.println("Numero de Objetos Pessoa " + numObjsPessoa);
    }
}