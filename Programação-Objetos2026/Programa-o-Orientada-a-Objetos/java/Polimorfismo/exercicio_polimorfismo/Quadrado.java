class Quadrado extends Forma {
    // Atributos
    private double lado;

    public Quadrado(double lado) {
        setLado(lado);
    }

    public double getLado() {
        return lado;
    }

    public void setLado(double lado) {
        this.lado = lado;
    }

    // Metodos
    public double calculaArea() {
        return this.lado * this.lado;
    }
}

