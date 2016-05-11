

package ProgConcorrente;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

/**
 *
 * @author Renan Alboy
 */
public class Gera_Randomico{
    
    int numColuna;
    int numLinha;
    
    //construtor da classe, atribui valores passados pelo usuário para a matriz 
    public Gera_Randomico(int linhas, int colunas){
        numLinha=linhas;
        numColuna=colunas;
    }
    
   //Gera a matriz de números ramdomicos
    public int[][] GeraMatriz() throws IOException{
        int i,j;
        int[][] m = new int[numLinha][numColuna];
        FileWriter arq = new FileWriter("pressão.txt");
        PrintWriter grava = new PrintWriter(arq);
        for(i=0;i<numLinha;i++){
            for(j=0;j<numColuna;j++){
                Random gerador = new Random();
                m[i][j] = gerador.nextInt(1101);
                //Grava a matriz no arquivo pressão.txt
                grava.printf("%d  " , m[i][j]);
                //Imprime na tela a matriz
                System.out.printf("%d   ",m[i][j]);
            }
            grava.printf("%n");
            System.out.printf("%n");
        }
        arq.close();
        
        
        return m;
    }
        
    public void PontoDeCela(int m[][], int linhas,int colunas){
        
        int max, min;
        int i=0,j=0, k=0, l=0;
        int total;
        //Definem asvariaveis de limite 
        int colunaSup, colunaInf, linhaDir, linhaEsq;
        
        min = 0;
        max = m[i][j];
        total=0;
        
        //procura menor elemento da linha
        for(i = 0; i < linhas; i++){
            min = m[i][j];
            
            //Inicializa variáveis para armazenar os limites
            colunaSup = 0;
            colunaInf = 0;
            linhaDir = 0;
            linhaEsq = 0;
            
            //Estabelece limites para frente e para trás das linhas
            if( i <= 6){
                linhaEsq = 0;
            }else{
                linhaEsq = i - 5;
            }
            if(linhas - i < 5){
               linhaDir = linhas;
            }else{
               linhaDir = linhaDir + 5;
            }
            
            for(j = linhaEsq; j < linhaDir;j++){
                if(min > m[i][j]){
                    min = m[i][j];
                    //Armazena valor de j em l, para ser usado no pr[oximo for
                    l = j;
                }        
            }
            //System usado para testes
           /* System.out.printf("i:%d l: %d, j:%d, linhaEsq:%d, linhaDir:%d \n",i,l,j,linhaEsq,linhaDir);*/
            
            //reinicializa j para não perder o valor
            j=0;
            max = m[0][l];
            
            //Estabelece limites para cima e para baixo da coluna
            //cujo valor foi dado como mínimo na linha
            if( l <= 6){
                colunaInf = 0;
            }else{
                colunaInf = l - 5;
            }
            if(colunas - l < 5){
               colunaSup = colunas;
            }else{
                colunaSup = colunaSup + 5;
            }
            //procura7 maior elemento da coluna
            for( k = colunaInf;k < colunaSup; k++){
                if(max < m[k][l]){
                    max = m[k][l];
                }
            }
             if(min == max){
                total = total+1;
                System.out.printf("%d é ponto de cela, na linha: %d e coluna: %d \n",m[i][l],i,l);
             }
        }        
        if(total > 0){
            System.out.printf("%d pontos de cela encontardos", total);
        }else{
            System.out.printf("Não foram encontrados pontos de cela");
        }
    }    
    
}
