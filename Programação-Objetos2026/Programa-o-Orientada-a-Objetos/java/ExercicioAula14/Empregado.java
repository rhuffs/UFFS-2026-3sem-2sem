
public class Empregado extends Pessoa {
    private String descricao;

    public Empregado(String nome, String descricao ){
        super(nome);
        this.descricao = descricao;
    }

    @Override
    public String getDescricao(){
        return "Cargo: " + this.descricao;
    }
}

