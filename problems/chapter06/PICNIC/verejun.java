package chapter_6_3;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Picnic {
	private final TestCase[] testCases;
	
	public Picnic(File input) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(input), "utf-8"));
		this.testCases = new TestCase[Integer.parseInt(br.readLine())];
		for(int i = 0; i < this.testCases.length; i++) {
			String[] tokens = br.readLine().split(" ");
			this.testCases[i] = new TestCase(Integer.parseInt(tokens[0]));
			
			tokens = br.readLine().split(" ");
			for(int j = 0; j < tokens.length; j += 2) {
				int x = Integer.parseInt(tokens[j]);
				int y = Integer.parseInt(tokens[j + 1]);
				this.testCases[i].relations[x][y] = this.testCases[i].relations[y][x] = true;
			}
			
		}
		br.close();
	}
	
	public void calculate() {
		for(TestCase tc : this.testCases) {
			tc.result = this.countPairings(tc);
		}
	}
	
	public void print() {
		for(TestCase tc : this.testCases) {
			System.out.println(tc.result);
		}
	}
	
	private int countPairings(TestCase tc) {
		int firstFree = -1;
		for(int i = 0; i < tc.students.length; i++){
			if(!tc.students[i]) {
				firstFree = i;
				break;
			}
		}
		
		if(firstFree == -1) {
			return 1;
		}
		
		int ret = 0;
		for(int pairWith = firstFree + 1; pairWith < tc.students.length; pairWith++) {
			if(!tc.students[pairWith] && tc.relations[firstFree][pairWith]) {
				tc.students[firstFree] = tc.students[pairWith] = true;
				ret += countPairings(tc);
				tc.students[firstFree] = tc.students[pairWith] = false;
			}
		}
		return ret;		
	}
	
	public static void main(String[] args) {
		try {
			Picnic picnic = new Picnic(new File("./data/input"));
			picnic.calculate();
			picnic.print();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

class TestCase {
	boolean[][] relations;
	boolean[] students;
	int result;
	
	public TestCase(int students) {
		this.relations = new boolean[students][students];
		this.students = new boolean[students];
	}
}
