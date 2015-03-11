package chapter06.BOGGLE;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class dualistmage {

    public static int MATRIX_SIZE = 5;

    public static void main(String[] args) {

        BufferedReader reader = new BufferedReader(
                new InputStreamReader(System.in)
        );
        StringTokenizer tokenizer = new StringTokenizer("");

        try {
            int count = Integer.parseInt(reader.readLine());

            String[] matrix;
            String[] words;
            String[] result;
            int wordCount;
            matrix = new String[MATRIX_SIZE];
            while( count-- > 0 )
            {
                // read matrix
                for(int lineNo = 0; lineNo < MATRIX_SIZE; lineNo++)
                {
                    matrix[lineNo] = reader.readLine();
                }

                // read expected words
                wordCount = Integer.parseInt(reader.readLine());
                words = new String[wordCount];
                for(int lineNo = 0; lineNo < wordCount; lineNo++)
                {
                    words[lineNo] = reader.readLine();
                }

                result = new String[wordCount];

                runWithBruteForce(matrix, words, result);

                // print result
                for(int wordIdx = 0; wordIdx < wordCount; wordIdx++)
                {
                    System.out.println(words[wordIdx] + " " + result[wordIdx]);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }


    }

    private static void runWithBruteForce(String[] matrix, String[] words, String[] result) {
        // XXX : template code start
        System.out.println("print matrix");
        System.out.println("--------------------------");
        for( String line : matrix )
        {
            System.out.println(line);
        }
        System.out.println();

        System.out.println("print words");
        System.out.println("--------------------------");
        for( String line : words )
        {
            System.out.println(line);
        }
        System.out.println();

        result[0] = "YES";
        result[1] = "YES";
        result[2] = "YES";
        result[3] = "NO";
        result[4] = "NO";
        result[5] = "YES";
        // XXX : template code end

        // TODO : nyi
    }
}