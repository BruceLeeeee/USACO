/*
ID: jl39301
LANG: JAVA
TASK: ride
*/
import java.io.*;
import java.util.*;

class ride {
	public static void main(String[] args) throws IOException {
		// Use BufferedReader rather than RandomAccessFile; it's much faster
		BufferedReader rd = new BufferedReader(new FileReader("ride.in"));
		// input file name goes above
		PrintWriter wt = new PrintWriter(new BufferedWriter(new FileWriter(
				"ride.out")));
		String cometName = rd.readLine();
		String groupName = rd.readLine();
		int cometVal = eval(cometName);
		int groupVal = eval(groupName);
		if (cometVal % 47 == groupVal % 47) {
			wt.println("GO"); 
		} else {
			wt.println("STAY");
		}
		
		
		wt.close(); // close the output file
		System.exit(0); // don't omit this!
	}
	
	public static int eval(String str) {
		int product = 1;
		
		for (int i = 0; i < str.length(); i++)
			product *= str.charAt(i) - 'A' + 1;
		
		return product;
	}
}