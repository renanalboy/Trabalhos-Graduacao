

package ProgConcorrente;

import java.io.IOException;
import java.util.Scanner;

/**
 *
 * @author Renan Alboy
 */
public class Main {
    
    private int thread;
    private int linhas;
    private int colunas;
        
    public static void main(String[] args) throws IOException{
        
        int i;
        
        Scanner scan = new Scanner(System.in);
        
        Threads T = new Threads();
        
        Thread t1 = new Thread(T);
        Thread t2 = new Thread(T);
        Thread t3 = new Thread(T);
        Thread t4 = new Thread(T);
        Thread t5 = new Thread(T);
        Thread t6 = new Thread(T);
        Thread t7 = new Thread(T);
        Thread t8 = new Thread(T);
        Thread t9 = new Thread(T);
        Thread t10 = new Thread(T);
        Thread t11 = new Thread(T);
        Thread t12 = new Thread(T);
        Thread t13 = new Thread(T);
        Thread t14 = new Thread(T);
        Thread t15 = new Thread(T);
        Thread t16 = new Thread(T);
            
        System.out.println("Número de linhas:");
        int linhas = scan.nextInt();
        System.out.println("Número de colunas:");
        int colunas = scan.nextInt();
        System.out.println("Número de Threads que irão executar:");
        int thread = scan.nextInt();
        
        //Inicia matriz que recebera a funçao de gerar randomico
        int m[][] = new int[linhas][colunas];
         System.out.println("\n");
        System.out.println("Matriz Gerada:");
        
        Gera_Randomico gerado = new Gera_Randomico(linhas, colunas);
        m = gerado.GeraMatriz();
        gerado.PontoDeCela(m, linhas,colunas);
        
      
    }
                    
}
                