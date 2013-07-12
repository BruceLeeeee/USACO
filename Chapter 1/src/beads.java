/*
ID: jl39301
LANG: JAVA
TASK: beads
 */
import java.io.*;
import java.util.*;

class beads {
	public static void main(String[] args) throws IOException {
		BufferedReader rd = new BufferedReader(new FileReader("beads.in"));
		PrintWriter wt = new PrintWriter(new BufferedWriter(new FileWriter(
				"beads.out")));
		int n = Integer.valueOf(rd.readLine());
		String str = rd.readLine();
		int max = 0;

		for (int i = 0; i < n; i++) {
			int amount = collect(str, i, -1) + collect(str, (i + 1) % n, +1);
			if (amount > max)
				max = amount;
		}
		if (max > n)
			max = n;
		wt.println(max);
		wt.close(); // close the output file
		System.exit(0); // don't omit this!
	}

	private static int collect(String str, int sPos, int move) {
		char color = str.charAt(sPos);
		int p = sPos;
		int count = 0;

		while (true) {
			if (str.charAt(p) != 'w' && color == 'w')
				color = str.charAt(p);
			if (str.charAt(p) == 'w' || str.charAt(p) == color || color == 'w') {
				p += move;
				count++;
			}
			else
				break;
			if (p >= str.length())
				p %= str.length();
			if (p < 0)
				p += str.length();
			if (p == sPos)
				break;

		}
		
		return count;
	}
}