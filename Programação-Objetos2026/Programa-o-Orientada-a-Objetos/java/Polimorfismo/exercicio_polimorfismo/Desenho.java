public class Desenho {
    private Forma[] formas = new Forma[10];
    int numFormas = 0;

    public void adicionaForma(Forma forma) {
        if (numFormas == 10) {
            System.out.println("Tamanho max atingido");
            return;
        }
        formas[this.numFormas] = forma;
        numFormas ++;
    }

    public double calculaAreaTotal() {
        double areaTotal = 0;
        for(int i = 0; i < this.formas.length; i++ ){
             if(formas[i] != null) {
                    areaTotal += formas[i].calculaArea();
            }
        }
        return areaTotal;
    }
}
