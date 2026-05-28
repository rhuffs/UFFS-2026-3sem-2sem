public class ExemploArrays2 {
    public static void main(String[] args) {
        // em c
        //int vet[15];

        //em java
        int[] vet = new int [15];

        int[] vet2;
        vet2 = new int[20];

        vet2[2] = 27;

        System.out.println(vet[0]);
        
        for (int i = 0; i < vet2.length; i++){
            System.out.println("vet2[" + i + "]:" + vet2[i]);
        }
        
        for (int v : vet2) {
            System.out.println("vet2[]:" + v);
        }
    }
}
