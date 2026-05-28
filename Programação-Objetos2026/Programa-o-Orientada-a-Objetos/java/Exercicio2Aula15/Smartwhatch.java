
public class Smartwhatch extends DispositivelEletronico implements Conectavel {

    private int BPM;


    public Smartwhatch(String marca, String modelo){
        super(marca,modelo);
    }

    public void leBatimentos(int bpm){
        this.BPM = bpm;
    }

    @Override
    public void ExibeInformacoes(){
        System.out.println("Hora: 16:00\nBatimentos : " + this.BPM);
    }

    @Override
    public void conecta(){
        System.out.println("Conectado");
    }
}
