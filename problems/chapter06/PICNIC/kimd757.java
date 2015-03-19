import java.util.Arrays;
import java.util.Scanner;

/**
 * Created by KDH on 2015-03-19.
 */
public class Picnic {
    public static void main(String[] args){
        int maxTestCase, curTestCaseNum = 0;
        boolean isPairLine = false;

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        maxTestCase = scanner.nextInt();
        scanner.nextLine();

        int peopleCnt=0, pairCnt=0, validCase=0;
        while( (curTestCaseNum/2) < maxTestCase ){
            String readLine = scanner.nextLine();

            String[] readLineAry = readLine.split(" ");
            int readLineAryLength = readLineAry.length;

            int[] pairAry = new int[readLineAryLength];

            if( isPairLine ){
                if( (readLineAryLength/2) != pairCnt ){
                    break;
                }else{
                    validCase = 0;

                    for(int idx = 0; idx < readLineAryLength; idx++ ){
                        pairAry[idx] = Integer.parseInt(readLineAry[idx]);
                    }

                    Combination combi = new Combination( (readLineAryLength/2) , (peopleCnt/2) );

                    while(combi.hasNext()){
                        int[] pair = combi.next();
                        System.out.println(Arrays.toString(pair));
                        int total = 0;
                        int[] peopleValidationAry = new int[peopleCnt];

                        for(int idx=0; idx<pair.length; idx++){
                            peopleValidationAry[pairAry[pair[idx]*2]]= 1;
                            peopleValidationAry[pairAry[pair[idx]*2+1]] = 1;
                        }

                        boolean isValidCase = true;
                        for(int idx=0; idx<peopleValidationAry.length; idx++){
                            if(peopleValidationAry[idx] == 0){
                                isValidCase = false;
                                break;
                            }
                        }

                        if(isValidCase)
                            validCase++;
                    }
                    System.out.println("Valid Case : "  + validCase );
                }
                isPairLine = false;
            }else{
                if ( readLineAry.length != 2 ){
                    break;
                }else{
                    peopleCnt = Integer.parseInt(readLineAry[0]);
                    pairCnt = Integer.parseInt(readLineAry[1]);
                }
                isPairLine = true;
            }
            curTestCaseNum ++;
        }
    }
}


class Combination {
    private int n, r;
    private int[] index;
    private boolean hasNext = true;

    public Combination(int n, int r) {
        this.n = n;
        this.r = r;
        index = new int[r];
        for(int idx=0; idx<r; idx++){
            index[idx] = idx;
        }
    }

    public boolean hasNext() {
        return hasNext;
    }

    private void moveToNextIndex() {
        int changeIndex = -1;

        for( int i = r-1; i>=0; i-- ){
            if( index[i] < n-r+i ){
                changeIndex = i;
                break;
            }
        }

        if( changeIndex >= 0 ) {
            index[changeIndex] = index[changeIndex]+1;
            for (int j = changeIndex+1; j<r; j++)
                index[j] = index[j-1] + 1;
        }else{
            hasNext = false;
        }
    }

    public int[] next() {
        if( !hasNext ){
            return null;
        }
        int[] result = new int[r];
        for(int i=0; i<r; i++){
            result[i] = index[i];
        }
        moveToNextIndex();
        return result;
    }
}
