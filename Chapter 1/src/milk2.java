/*
ID: jl39301
LANG: JAVA
TASK: milk2
 */
import java.io.*;
import java.util.*;

class Interval implements Comparable<Interval> {
	public int start, end;
	public boolean merged;
	
	public int compareTo(Interval compareInterval) {
		return this.start - compareInterval.start;
	}
}

public class milk2 {
	public static void main(String[] args) throws IOException {
		BufferedReader rd = new BufferedReader(new FileReader("milk2.in"));
		PrintWriter wt = new PrintWriter(new BufferedWriter(new FileWriter("milk2.out")));
		StringTokenizer st;
		int n = Integer.valueOf(rd.readLine());
		Interval[] arr = new Interval[n];
		ArrayList<Interval> list = new ArrayList<Interval>(); 
		
		for (int i = 0; i < n; i++) {
			st = new StringTokenizer(rd.readLine());
			arr[i] = new Interval();
			arr[i].start = Integer.valueOf(st.nextToken());
			arr[i].end = Integer.valueOf(st.nextToken());
			arr[i].merged = false;
		}
		
		merge(arr);
		for (int i = 0; i < n; i++)
			if (arr[i].merged == false)
				list.add(arr[i]);
		Collections.sort(list);
		output(list, wt);
		
		wt.close(); // close the output file
		System.exit(0); // don't omit this!
	}
	
	private static void output(ArrayList<Interval> list, PrintWriter wt) {
		int maxCon = 0;
		int maxIdle = 0;
		int tmp = 0;
		
		for (int i = 0; i < list.size(); i++) {
			//wt.println("start: " + list.get(i).start + " " + "end: " + list.get(i).end);
			if (list.get(i).end - list.get(i).start > maxCon) 
				maxCon = list.get(i).end - list.get(i).start;
			if (i != 0 && list.get(i).start - list.get(i - 1).end > maxIdle) {
				maxIdle = list.get(i).start - list.get(i - 1).end;
				tmp = i;
			}
		}
		
		//wt.println("index: " + tmp);
		wt.println(maxCon + " " + maxIdle);
	}
	
	private static void merge(Interval[] arr) {
		for (int i = 0; i < arr.length; i++)
			for (int j = i + 1; j < arr.length; j++)
				if (overlap(arr[i], arr[j])) {
					arr[i].merged = true;
					arr[j].end = arr[i].end > arr[j].end ? arr[i].end : arr[j].end;
					arr[j].start = arr[i].start < arr[j].start ? arr[i].start : arr[j].start;
					break;
				}
	}
	
	private static boolean overlap(Interval int1, Interval int2) {
		if (int1.end >= int2.start && int1.end <= int2.end)
			return true;
		if (int1.start >= int2.start && int1.start <= int2.end)
			return true;
		if (int2.end >= int1.start && int2.end <= int1.end)
			return true;
		if (int2.start >= int1.start && int2.start <= int1.end)
			return true;
		return false;
	}
}