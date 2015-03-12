import java.io.*;

/**
 * Created by Administrator on 2015-03-12.
 */
public class Boggle {

    static int[] xPointAry = {-1, -1, -1,  0, 0,  1, 1, 1};
    static int[] yPointAry = {-1,  0,  1, -1, 1, -1, 0, 1};

    public static void main(String[] args){

        BufferedReader reader = null;

        try {

            // read Sample and set Matrix Array
            if(args.length != 2){
                System.out.println("Invalid Argument");
                System.exit(0);
            }else{
                 reader = new BufferedReader(new FileReader(args[0]));
            }

            String[][] matrix = new String[5][5];
            int lineCount = 0;
            String buf;

            while( (buf = reader.readLine()) != null ){
                for(int charIdx=0; charIdx <buf.length(); charIdx++){
                    matrix[lineCount][charIdx] = buf.substring(charIdx, charIdx+1);
                }
                lineCount++;
            }
            reader.close();

            System.out.println("- Matrix -");

            for(int i=0; i<5; i++){
                for(int j=0; j<5; j++){
                    System.out.print(matrix[i][j] + " ");
                }
                System.out.println("");
            }
            System.out.println("----------");
            String word = args[1];
            System.out.println("Input Word >>> [" + word +"]");

            for(int i=0; i<5; i++){
                for(int j=0; j<5; j++){
                    if( matrix[i][j].equals(word.substring(0, 1))){
                        if( searchWord(matrix, i, j, word, true, 0) ){
                            System.out.println("[" + word + "] is included");
                            System.exit(0);
                        }
                    }

                }
            }
            System.out.println("[" + word + "] is not included");

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (reader != null)  reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    static public boolean searchWord(String[][] matrix, int xPoint, int yPoint, String word, boolean isFirst, int depth){
        // check Invalid Point
        if( (xPoint < 0) || (xPoint > 4) || (yPoint < 0) || (yPoint > 4) ){
            return false;
        }
        if(!isFirst) {
            if (!matrix[xPoint][yPoint].equals(word.substring(0, 1)))
                return false;
        }
        // finished function
        if( word.length() == 1 ){
            return true;
        }

        for(int idx=0; idx<xPointAry.length; idx++){
            int nextXPoint = xPoint + xPointAry[idx];
            int nextYPoint = yPoint + yPointAry[idx];

            if( searchWord(matrix, nextXPoint, nextYPoint, word.substring(1), false, depth+1) ) {
                return true;
            }
        }
        return false;
    }
}
