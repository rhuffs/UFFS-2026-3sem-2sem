class Main {
    public static void main(String[] args) {
      //    Exercício:
      //   1. Crie dois objetos de três formas diferentes, dando valores aos seus
      //      atributos.
      //   2. Crie um objeto Desenho.
      //   3. Implemente o método adicionaForma da classe Desenho.
      //   4. Usando o método criado no item anterior, adicione os objetos dos
      //      dos tipos de forma à lista de formas do objeto Desenho.  
      //   5. Implemente o método calculaAreaToral da classe Desenho.
      //   6. Usando o método criado no item anterior, imprima a área total das
      //      formas contidas no objeto Desenho.


      Forma c1 = new Circulo(3);
      Forma c2 = new Circulo(4);
      Forma q1 = new Quadrado(5);
      Forma q2 = new Quadrado(10);
      Forma r1 = new Retangulo(5,10);
      Forma r2 = new Retangulo(2,4);

      Desenho d = new Desenho();
      d.adicionaForma(c1);
      d.adicionaForma(c2);
      d.adicionaForma(q1);
      d.adicionaForma(q2);
      d.adicionaForma(r1);
      d.adicionaForma(r2);

      System.out.println(d.calculaAreaTotal());

    }
}

