public class Programa {
    public static void main(String[] args) {
        int a;
        a = 5;
        Circulo c;
        
        c = new Circulo();
        c.raio = 3.0;
        System.out.println("raio" + c.raio);
        System.out.println("àrea: " + c.calculaArea());
        Circulo c2;
        c2 = c;
        c2.raio = 6.0;
        System.out.println("raio" + c.raio);
        c.imprimeArea();

        
    }    
}
