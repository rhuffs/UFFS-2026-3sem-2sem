public class Circulo { 
    double raio;

    double calculaArea() {
        double area = 3.14 * this.raio * this.raio;
        return area;
    }
    
    void imprimeArea(){
        double area = calculaArea();
        System.out.println("Área : "+ area);
    }
        

    
}
