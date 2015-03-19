package chapter06.PICNIC;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

class Reader {
    static BufferedReader reader;
    static StringTokenizer tokenizer;

    /** call this method to initialize reader for InputStream */
    static void init(InputStream input) {
        reader = new BufferedReader(
                new InputStreamReader(input) );
        tokenizer = new StringTokenizer("");
    }

    /** get next word */
    static String next() throws IOException {
        while ( ! tokenizer.hasMoreTokens() ) {
            //TODO add check for eof if necessary
            tokenizer = new StringTokenizer(
                    reader.readLine() );
        }
        return tokenizer.nextToken();
    }

    static int nextInt() throws IOException {
        return Integer.parseInt( next() );
    }

    static double nextDouble() throws IOException {
        return Double.parseDouble( next() );
    }
}
public class dualistmage {

    public static int STUDENT_MAXNO = 10;

    public static boolean[][] areTheyFriend = new boolean[STUDENT_MAXNO][STUDENT_MAXNO];
    public static boolean[] isThisStudentUsed = new boolean[STUDENT_MAXNO];

    public static void main(String[] args) {

        Reader.init(System.in);

        try {
            int count = Reader.nextInt();
            int studentNo = 0;
            int friendshipNo = 0;
            int first = 0;
            int second = 0;

            while( count-- > 0 ) {

                // read student number
                studentNo = Reader.nextInt();
                friendshipNo = Reader.nextInt();

                // initialize areTheyFriendMatrix
                for(int i = 0; i < studentNo; i++) {
                    for(int j = i + 1; j < studentNo; j++) {
                        areTheyFriend[i][j] = false;
                    }
                    isThisStudentUsed[i] = false;
                }

                // read friendship
                for(int i = 0; i < friendshipNo; i++) {
                    first = Reader.nextInt();
                    second = Reader.nextInt();
                    if( first > second ) {
                        areTheyFriend[second][first] = true;
                    }
                    else {
                        areTheyFriend[first][second] = true;
                    }
                }

                // print result
                System.out.println(getPairCombinationCount(studentNo));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    static int getPairCombinationCount(int studentNo) {
        int firstStudent = -1;
        for(int i = 0; i < studentNo; i++) {
            if( !isThisStudentUsed[i] ) {
                firstStudent = i;
                break;
            }
        }
        if( firstStudent == -1 ) {
            return 1;
        }

        int sum = 0;
        for(int secondStudent = firstStudent + 1; secondStudent < studentNo; secondStudent++) {
            if( (isThisStudentUsed[secondStudent] == false) && areTheyFriend[firstStudent][secondStudent] ) {
                isThisStudentUsed[firstStudent] = isThisStudentUsed[secondStudent] = true;
                sum += getPairCombinationCount(studentNo);
                isThisStudentUsed[firstStudent] = isThisStudentUsed[secondStudent] = false;
            }
        }
        return sum;
    }
}

