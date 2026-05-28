public class ExemploOperadores {
    public static void main(String[] args) {
        // operadors aritimeticos
        // + - * / %
         double d1 = 9.0;
         double d2 =13.0;

         System.out.println(d1 - d2);

        //Operador de concatenacao 
        String str1 = "abra";
        String str2 = "cadabra";

        str1 = str1 + str2;
        System.out.println(str1);

        System.out.println("str1:" + str1);
        System.out.println("str2:" + str2);

        //Operadores relacionais
        // < > <= >= == !=

        d1 = 9.0;
        d2 = 13.0;

        System.out.println("d1 == d2 ?" + (d1 == d2));

        
    }
}
