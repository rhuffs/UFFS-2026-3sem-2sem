class Triangulo {
    double base;
    double altura;
    
    boolean temDimIguais(Triangulo t) {
        return (base == t.base && altura == t.altura);
    }

    void somaTriangulo(Triangulo t){
        base = base + t.base;
        altura = altura + t.altura;

    }

    void somaTriangulo2(Triangulo t){
        t.base = t.base + base;
        t.altura = t.altura + altura;
    }
}