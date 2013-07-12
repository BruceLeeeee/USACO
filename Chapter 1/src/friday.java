/*
ID: jl39301
LANG: JAVA
TASK: friday
 */
import java.io.*;
import java.util.*;

class friday {
	public static void main(String[] args) throws IOException {
		BufferedReader rd = new BufferedReader(new FileReader("friday.in"));
		PrintWriter wt = new PrintWriter(new BufferedWriter(new FileWriter(
				"friday.out")));
		int n = Integer.valueOf(rd.readLine());
		int year = 1900;
		int month = 2;
		int[] count = new int[10];
		int tracker = 6;
		
		for (int i = 0; i < 10; i++)
			count[i] = 0;
		count[tracker]++;
		while (true) {
			int days = getMonthDays(year, month - 1);
			tracker = (tracker + days % 7) % 7;
			//wt.println(tracker);
			count[tracker]++;
			month++;
			if (month == 13) {
				month = 1;
				year++;
			}
			if (year == 1900 + n)
				break;
		}

		output(wt, count);

		wt.close(); // close the output file
		System.exit(0); // don't omit this!
	}

	public static int getMonthDays(int year, int month) {
		switch (month) {
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
				return 29;
			} else {
				return 28;
			}
		default:
			return 31;
		}
	}

	private static void output(PrintWriter wt, int[] count) {
		String res = "" + count[6] + " " + count[0];

		for (int i = 1; i <= 5; i++)
			res += " " + count[i];
		wt.println(res);
	}
}