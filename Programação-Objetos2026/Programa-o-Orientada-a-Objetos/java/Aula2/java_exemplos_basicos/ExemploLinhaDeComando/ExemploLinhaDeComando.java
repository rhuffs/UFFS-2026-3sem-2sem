public class ExemploLinhaDeComando {
    public static void main(String[] args) {
        // Saida
        for (int i = 0; i < args.length; i++) {
            System.out.println("Parametro " + i + ": " + args[i]);
        }
    }
}

