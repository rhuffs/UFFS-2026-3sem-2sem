import java.time.LocalDate;

class Data {

    int dia;
    int mes;
    int ano;


    public Data() {
        this.dia = LocalDate.now().getDayOfMonth();
        this.ano = LocalDate.now().getYear();
        this.mes = LocalDate.now().getMonthValue();
    }

    public Data(int dia, int mes, int ano){
        this.dia = dia;
        this.mes = mes;
        this.ano = ano;
    }

    void imprime(){
        System.out.println("Data:");
        System.out.println("Data:" + dia);
        System.out.println("Data:" + mes);
        System.out.println("Data:" + ano);



    }
    
}