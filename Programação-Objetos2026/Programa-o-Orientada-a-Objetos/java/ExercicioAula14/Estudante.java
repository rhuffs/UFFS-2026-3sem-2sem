public class Estudante extends Pessoa {
    private String descricao;

    public Estudante(String nome, String descricao ){
        super(nome);
        this.descricao = descricao;
    }

    @Override
    public String getDescricao(){
        return "Curso: " + this.descricao;
    }
}
