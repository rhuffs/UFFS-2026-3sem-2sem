class Circulo extends Forma {
    // Atributos
    private double raio;

    public Circulo(double raio) {
        setRaio(raio);
    }

    public double getRaio() {
        return raio;
    }

    public void setRaio(double raio) {
        this.raio = raio;
    }

    // Metodos
    public double calculaArea() {
        return 3.1415 * this.raio * this.raio;
    }
}

