/*
 * Date: 15. 05. 25
 * By Hyun-Tae Kim
 */

package test;

import java.util.Scanner;


public class QuadTree {
    static int MAX_SIZE;
    public static boolean  areFriends[][];
    public static String quad;
    public static int curIdx;

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int size = scan.nextInt();
        scan.nextLine();
        while(size>0){
            quad = scan.nextLine();
            curIdx=0;
            System.out.println(reverse());
            size--;
        }

    }
    static String reverse(){
        char head = quad.charAt(curIdx);
        curIdx++;
        if(head == 'b' || head == 'w')
            return Character.toString(head); 
        StringBuilder upsb = new StringBuilder();
        StringBuilder lowersb = new StringBuilder();
        for(int i=0; i<2;i++)
            upsb.append(reverse());
        lowersb.append('x');
        for(int i=0; i<2;i++)
            lowersb.append(reverse());
        lowersb.append(upsb);
        return lowersb.toString();
        /*
        String upLeft = reverse();
        String upRight = reverse();
        String lowerLeft = reverse();
        String lowerRight = reverse();
        return "x" + lowerLeft + lowerRight + upLeft + upRight;
        */
    }
}
