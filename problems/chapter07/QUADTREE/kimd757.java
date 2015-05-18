import java.util.Scanner;

public class Main {
    static int curIdx = 0;
    public static void main(String args[]){

        Scanner sc = new Scanner(System.in);
        int cases = sc.nextInt();
        int size = cases;
        String[] result = new String[cases];
        while(cases -->0){
            String str = sc.next();
            String answer = reverse(str);
            curIdx = 0;
            result[size-1-cases] = answer;
        }
        for(int i=0; i<size; i++){
            System.out.println(result[i]);
        }
    }

    public static String reverse(String recvStr){
        char curChar = recvStr.charAt(curIdx);

        curIdx++;
        if(curChar == 'b' || curChar == 'w'){
            return recvStr.substring(curIdx-1, curIdx);
        }

        String upperLeft = reverse(recvStr);
        String upperRight = reverse(recvStr);
        String lowerLeft = reverse(recvStr);
        String lowerRight = reverse(recvStr);

        return "x" + lowerLeft + lowerRight + upperLeft + upperRight;
    }
}
