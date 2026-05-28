class Triangulo extends Forma {
    // Atributos
    private double base;
    private double altura;

    public Triangulo(double base, double altura) {
        setBase(base);
        setAltura(altura);
    }

    public double getBase() {
        return base;
    }

    public void setBase(double base) {
        this.base = base;
    }

    public double getAltura() {
        return altura;
    }

    public void setAltura(double altura) {
        this.altura = altura;
    }

    // Metodos
    public double calculaArea() {
        return this.base * this.altura / 2;
    }
}

