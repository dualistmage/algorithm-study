package test;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.Vector;

public class Picnic {
    static int MAX_SIZE;
    public static boolean  areFriends[][];
    public static String INPUT_FILE = "input_bicnic.txt";

    public static void main(String[] args) {

        BufferedReader reader = null;
        //      String path = Boggle.class.getResource("").getPath() + "/" + INPUT_FILE;
        String path = "D:\\test\\" +INPUT_FILE;
        try {
            reader = new BufferedReader(new FileReader(path));
            int total = Integer.parseInt(reader.readLine().trim());
            int count = total*2;
            System.out.println("total count:" + total);
            
            String line;
            MAX_SIZE=10;
            Vector<Integer> output = new Vector<Integer>(total);
            boolean people[] = new boolean[10];
            areFriends = new boolean[10][10];
            
            while(count -- > 0){
                line = reader.readLine();
                System.out.println(count+":"+line);
                StringTokenizer strToken = new StringTokenizer(line, " ");
                if(count%2 == 1){ // info
                    MAX_SIZE = Integer.parseInt(strToken.nextToken().trim());
                    areFriends = new boolean[MAX_SIZE][MAX_SIZE];
                    people = new boolean[MAX_SIZE];
                }
                else{
                    while(strToken.hasMoreTokens()){
                        String tokenA = strToken.nextToken().trim();
                        String tokenB = strToken.nextToken().trim();
                        //System.out.println(tokenA + "," + tokenB);
                        areFriends[Integer.parseInt(tokenA)][Integer.parseInt(tokenB)]=true;
                        areFriends[Integer.parseInt(tokenB)][Integer.parseInt(tokenA)]=true;
                    }
                    // 실행
                    output.addElement(countPairings(people));
                }
            }
            
            System.out.println("\noutput:-------------------");
            for(Integer i : output){
                System.out.println(i);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    static int countPairings(boolean[] taken){
        // 남은 학샐등 중 가장 번호가 빠른 학생을 찾는다.
        int firstFree = -1;
        for(int i=0; i<MAX_SIZE; ++i){
            if(!taken[i]){
                firstFree = i;
                break;
            }
        }
        // 기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
        if(firstFree == -1) return 1;
        
        int ret = 0;
        for(int pairWith = firstFree+1; pairWith < MAX_SIZE; ++pairWith){
            if(!taken[pairWith] && areFriends[firstFree][pairWith]){
                taken[firstFree] = taken[pairWith] = true;
                ret += countPairings(taken);
                taken[firstFree] = taken[pairWith] = false;
            }
        }
        return ret;        
    } // end of countPairings
}
