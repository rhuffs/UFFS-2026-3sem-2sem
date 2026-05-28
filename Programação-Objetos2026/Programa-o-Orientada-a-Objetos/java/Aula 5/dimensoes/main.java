
public class main {
    public static void main(String[] args) {
        Triangulo t1 = new Triangulo();
        Triangulo t2 = new Triangulo();

        t1.base = 2;
        t1.altura = 3;
        t2.base = 9;
        t2.altura = 6;
        t1.temDimIguais(t2);

        System.out.println(t1.temDimIguais(t2));

        System.out.println(t1.base);
        System.out.println(t1.altura);
        t1.somaTriangulo(t1);
        System.out.println(t1.base);
        System.out.println(t1.altura);

        
        

    }

}
