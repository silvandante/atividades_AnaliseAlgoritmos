/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package geradorvetoraleatoriosemrepeticao;

import java.util.HashSet;
import java.util.Random;
import java.util.Set;

/**
 *
 * @author wscar
 */


public class GeradorVetorAleatorioSemRepeticao {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        for (int i : printRandomNumbers(10000,10000)) {  
            System.out.print(i+",");  
        }  
         System.out.println();
    }
    
    
    public static final Random gen = new Random();  
    public static int[] printRandomNumbers(int n, int maxRange) {  
    assert n <= maxRange : "cannot get more unique numbers than the size of the range";  
      
    int[] result = new int[n];  
    Set<Integer> used = new HashSet<Integer>();  
      
    for (int i = 0; i < n; i++) {  
          
        int newRandom;  
        do {  
            newRandom = gen.nextInt(maxRange+1);  
        } while (used.contains(newRandom));  
        result[i] = newRandom;  
        used.add(newRandom);  
    }  
    return result;  
} 
}
