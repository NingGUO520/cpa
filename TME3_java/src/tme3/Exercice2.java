package tme3;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Map.Entry;

import tme3.LoadGraphe.Edge;

import java.util.Set;

public class Exercice2 {

	
	
	
	static final String email = "after_cleaning/email-Eu-core.txt";
	static final String amazon = "after_cleaning/com-amazon.ungraph.txt";
	static final String lj = "after_cleaning/com-lj.ungraph.txt";
	static final String orkut = "after_cleaning/com-orkut.ungraph.txt";

	public static void main(String[] args) {
	
		
		ArrayList<Edge> edges = new ArrayList<Edge>();
		String filename = email;
		Set<Integer> noeuds = new HashSet<Integer>();
		try{
			InputStream flux=new FileInputStream(filename); 
			InputStreamReader lecture=new InputStreamReader(flux);
			BufferedReader buff=new BufferedReader(lecture);
			String ligne;
			int nbEdges=0;
			while ((ligne=buff.readLine())!=null){
								
				if(!ligne.startsWith("#")) {
				String[] parts = ligne.split("\\s+");
				int p1 = Integer.parseInt(parts[0]);
				int p2 = Integer.parseInt(parts[1]);
				noeuds.add(p1);
				noeuds.add(p2);
				nbEdges++;
			
				}
			}
			
			System.out.println("number of  edges is:  " + nbEdges);
			System.out.println("number of nodes is:  " + noeuds.size());

			buff.close(); 
			}		
			catch (Exception e){
			System.out.println(e.toString());
			}
		
	}	

}
