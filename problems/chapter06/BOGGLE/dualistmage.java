package chapter07.BOGGLE;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class dualistmage {

    public static int MATRIX_SIZE = 5;

    public static void main(String[] args) {

        BufferedReader reader = new BufferedReader( new InputStreamReader(System.in) );

        try {
            int count = Integer.parseInt(reader.readLine());

            String[] matrix;
            String[] words;
            String[] result;
            int wordCount;
            matrix = new String[MATRIX_SIZE];
            while( count-- > 0 ) {
                // read matrix
                for(int lineNo = 0; lineNo < MATRIX_SIZE; lineNo++) {
                    matrix[lineNo] = reader.readLine();
                }

                // read expected words
                wordCount = Integer.parseInt(reader.readLine());
                words = new String[wordCount];
                for(int lineNo = 0; lineNo < wordCount; lineNo++) {
                    words[lineNo] = reader.readLine();
                }

                result = new String[wordCount];

                runWithBruteForce(matrix, words, result);

                // print result
                for(int wordIdx = 0; wordIdx < wordCount; wordIdx++) {
                    System.out.println(words[wordIdx] + " " + result[wordIdx]);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private static int DIRECTION_NUM = 8;
    private static int[] dx = new int[]{ -1, 0, 1, -1, 1, -1, 0, 1};
    private static int[] dy = new int[]{ -1, -1, -1, 0, 0, 1, 1, 1};

    private static boolean outOfRange(int x, int y) {
        if( x < 0 || x >= MATRIX_SIZE )
            return true;
        if( y < 0 || y >= MATRIX_SIZE )
            return true;
        return false;
    }
    private static boolean foundPath(int x, int y, String word, String[] matrix)
    {
        if( outOfRange(x,y) )
            return false;
        else if(word.charAt(0) != matrix[y].charAt(x))
            return false;
        else
        {
            if( word.length() == 1 )
                return true;
            for(int curDir = 0; curDir < DIRECTION_NUM; curDir++)
                if( foundPath(x + dx[curDir], y + dy[curDir], word.substring(1), matrix) )
                    return true;
            return false;
        }
    }

    private static void runWithBruteForce(String[] matrix, String[] words, String[] result) {
        for(int wordIdx = 0; wordIdx < words.length; wordIdx++)
        {
            boolean isPathFound = false;
            for(int x = 0; x < MATRIX_SIZE; x++) {
                for (int y = 0; y < MATRIX_SIZE; y++) {
                    if( foundPath(x,y,words[wordIdx],matrix) ) {
                        isPathFound = true;
                        break;
                    }
                }
                if( isPathFound )
                    break;
            }
            if( isPathFound )
                result[wordIdx] = "YES";
            else
                result[wordIdx] = "NO";
        }
    }

    private static void runOptimizedProcess(String[] matrix, String[] words, String[] result) {
        // TODO : Not Yet Implemented
    }
}