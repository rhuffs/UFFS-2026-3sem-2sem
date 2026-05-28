class Circulo extends Forma {
    private int raio;


    public void imprimePontoMaisADireita(){
        System.err.println("ponto mais a direita :");
        System.err.println(this.x + this.raio);//Só funciona se for protected os atributos da classe pai
        System.err.println(this.y);
    }

}