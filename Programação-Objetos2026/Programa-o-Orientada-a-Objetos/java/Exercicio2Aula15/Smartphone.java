public class Smartphone extends DispositivelEletronico implements Conectavel{
    
    private String operadora;
    
    public Smartphone(String marca, String modelo ){
        super(marca, modelo);
    }

    public void setOperadora(String Operadora){
        this.operadora = Operadora;
    }

    public String getOperadora(){
        return this.operadora;
    }

    @Override
    public void conecta(){
        System.out.println("Conectado");
    }

    @Override
    public void ExibeInformacoes(){
        System.out.println("Hora: 16:00\nOperadora : " + this.operadora);
    }
}
