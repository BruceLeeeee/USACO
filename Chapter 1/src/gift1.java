/*
ID: jl39301
LANG: JAVA
TASK: gift1
*/
import java.io.*;
import java.util.*;

public class gift1 {
	public static void main(String arg[]) throws IOException {
		BufferedReader rd = new BufferedReader(new FileReader("gift1.in"));
		PrintWriter wt = new PrintWriter(new FileWriter("gift1.out"));
		ArrayList<String> nameList = new ArrayList<String>(); 
		HashMap<String, Integer> nameInitMap = new HashMap<String, Integer>();
		HashMap<String, Integer> nameFinalMap = new HashMap<String, Integer>();
		StringTokenizer tokenizer = new StringTokenizer(rd.readLine());
		int NP = Integer.valueOf(tokenizer.nextToken());
		for (int i = 0; i < NP; i++) {
			String name = rd.readLine();
			nameList.add(name);
			nameFinalMap.put(name, 0);
		}
		
		for (int i = 0; i < NP; i++) {
			String giver = rd.readLine();
			String receiver;
			tokenizer = new StringTokenizer(rd.readLine());
			int init = Integer.valueOf(tokenizer.nextToken());
			int m = Integer.valueOf(tokenizer.nextToken());
			int gift = 0;
			int remainder = init;
			if (m != 0) {
				gift = init / m;
				remainder = init % m;
			}
			nameInitMap.put(giver, init);
			nameFinalMap.put(giver, nameFinalMap.get(giver) + remainder);
			for (int j = 0; j < m; j++) {
				receiver = rd.readLine();
				nameFinalMap.put(receiver, nameFinalMap.get(receiver) + gift);
			}
		}
		
		for (int i = 0; i < nameList.size(); i++) {
			String name = nameList.get(i);
			int net = nameFinalMap.get(name) - nameInitMap.get(name);
			
			wt.println(name + " " + net);
		}
		wt.close();
		System.exit(0); // don't omit this!
	}
}
