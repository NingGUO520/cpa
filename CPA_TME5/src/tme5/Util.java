package tme5;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public abstract class Util {
	
	public static List<Integer>[] getAdjacencyList(String filename) {
		int max = getMax(filename)+1;
		List<Integer>[] adjencyList = new ArrayList[max];
		adjencyList[0] = new ArrayList<Integer>();
		try {
			BufferedReader br = new BufferedReader(new FileReader(new File(filename)));
			String line = br.readLine();
			while (line != null) {
				String[] splitted = line.split("\\s");
				if (!splitted[0].equals("#")) {
					int s1 = Integer.parseInt(splitted[0]);
					int s2 = Integer.parseInt(splitted[1]);
					
					if (adjencyList[s1] == null)
						adjencyList[s1] = new ArrayList<Integer>();
					if (adjencyList[s2] == null)
						adjencyList[s2] = new ArrayList<Integer>();
					
					if (!adjencyList[s1].contains(s2))
						adjencyList[s1].add(s2);
					if (!adjencyList[s2].contains(s1))
						adjencyList[s2].add(s1);
				}	
				line = br.readLine();
			}
			br.close();
			
			return adjencyList;
			
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
	}
	
	public static int getMax(String filename) {
		int max = -1;
		try {
			BufferedReader br = new BufferedReader(new FileReader(new File(filename)));
			String line = br.readLine();
			while (line != null) {
				String[] splitted = line.split("\\s");
				if (!splitted[0].equals("#")) {
					int s1 = Integer.parseInt(splitted[0]);
					int s2 = Integer.parseInt(splitted[1]);
					
					if (s1 > max)
						max = s1;
					if (s2 > max)
						max = s2;
				
				}
				line = br.readLine();
			}
			br.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		return max;
	}
}
