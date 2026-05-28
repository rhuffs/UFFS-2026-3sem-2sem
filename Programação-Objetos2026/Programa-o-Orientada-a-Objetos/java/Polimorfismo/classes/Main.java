
public class Main {
    public static void main(String[] args) {
        // //Quadrado
        // Quadrado q = new Quadrado(5);
        // q.setX(0);
        // q.setY(10);
        // System.out.println("A area o quadrado q é " + q.CalculaArea());
        // System.out.println("O perimetro do quadrado q é " + q.CalcularPerimetro());
        // System.out.println("O quadrado q esta na posicao("+q.getX()+","+q.getY()+")\n");
        // //
        // //Circulo
        // Circulo c = new Circulo(7);
        // c.setX(3);
        // c.setY(4);
        // System.out.println("A area o circulo c é " + c.CalculaArea());
        // System.out.println("O perimetro do circulo c é " + c.CalcularPerimetro());
        // System.out.println("O circulo c esta na posicao("+c.getX()+","+c.getY()+")\n");
        // //
        // //Retangulo
        // Retangulo r = new Retangulo(3, 6);
        // r.setX(-5);
        // r.setY(10);
        // System.out.println("A area o retangulo r é " + r.CalculaArea());
        // System.out.println("O perimetro do retangulo r é " + r.CalcularPerimetro());
        // System.out.println("O retangulo r está na posicao("+r.getX()+","+r.getY()+")\n");
        // //
        // //Triangulo
        // Triangulo t = new Triangulo(5,8);
        // t.setX(3);
        // t.setY(-4);
        // System.out.println("A area o triangulo t é " + t.CalculaArea());
        // System.out.println("O triangulo t está na posicao("+t.getX()+","+t.getY()+")\n");
        // //
        // //
        
        
        //POLIMORFISMO

        //Não é possivel Forma f = new Forma();
        Formas[] formas = new Formas[10]; // Posssivel
        formas[0] = new Quadrado();
        formas[1] = new Quadrado(); 
        formas[2] = new Quadrado(); 
        formas[3] = new Circulo(); 
        formas[4] = new Circulo(); 
        formas[5] = new Circulo(); 
        formas[6] = new Triangulo(); 
        formas[7] = new Triangulo(); 
        formas[8] = new Triangulo();
        formas[9] = new Retangulo();  

        for (int i = 0; i <= formas.length; i++){
            System.out.println(formas[i].CalculaArea());
            System.out.println(formas[i].CalcularPerimetro());
            
            if (i == 5){ // jeito seguro de fazer o o DownCast usando o instanceof
                if (formas[i] instanceof Circulo){//
                     Circulo c = ((Circulo) formas[5]); // DownCast: Algo mais geral para algo maus especifico
                                                    // Perigoso: pois qualquer alteracao quebra o codigo
                    System.out.println("Circ " +c.CalcularPerimetro() );
                }
            }
        }

    }    
}
