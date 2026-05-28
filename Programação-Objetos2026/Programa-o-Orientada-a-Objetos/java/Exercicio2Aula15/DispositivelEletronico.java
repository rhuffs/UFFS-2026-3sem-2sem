public abstract class DispositivelEletronico{
    private String marca;
    private String modelo;


    public DispositivelEletronico(String marca, String modelo){
        this.marca = marca;
        this.modelo = modelo;
    }

    public void liga(){
        System.out.println("LiGOOOOUUU");
    }

    public abstract void ExibeInformacoes();
}