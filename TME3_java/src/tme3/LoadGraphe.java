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
import java.util.Set;
import java.util.Map.Entry;
import java.util.PriorityQueue;
import java.util.Queue;

public class LoadGraphe {

	static final String email = "after_cleaning/email-Eu-core.txt";
	static final String amazon = "after_cleaning/com-amazon.ungraph.txt";
	static final String lj = "after_cleaning/com-lj.ungraph.txt";
	static final String orkut = "after_cleaning/com-orkut.ungraph.txt";

	public class Edge  {
		int p,q;

		public Edge(int p, int q) {

			this.p =p;
			this.q = q;
		}		
	}

	public class Pair{

		int node,depth;
		public Pair(int node, int depth) {
			this.node = node;
			this.depth = depth;
		}
	}

	private ArrayList<Integer>  noeuds;
	private ArrayList<Edge> edges;
	private Map<Integer, ArrayList<Integer>> mapAdjacence;
	private Map<Integer,Integer> nodeDegreeMap;
	private int[][] matriceAdjacence;
	
	public LoadGraphe() {
		noeuds= new ArrayList<Integer>();
		edges = new ArrayList<Edge>();
		nodeDegreeMap = new HashMap<Integer,Integer>();
		mapAdjacence =  new HashMap<Integer, ArrayList<Integer>>();

	}

	public void LoadGraphMemory(String nomFichier) {
		loadGraphe(nomFichier);
		mapAdjacence = getListeAdjacence();
		matriceAdjacence = getAdjacencyMatrix(nomFichier);
		
	}

	public int[][] getAdjacencyMatrix(String nomFichier) {
		//Premier parcours de fichier pour recuperer la taille de noeuds
		ArrayList<Integer> nodes = new ArrayList<Integer>();
		try{
			InputStream flux=new FileInputStream(nomFichier); 
			InputStreamReader lecture=new InputStreamReader(flux);
			BufferedReader buff=new BufferedReader(lecture);
			String ligne;
			while ((ligne=buff.readLine())!=null){

				if(!ligne.startsWith("#")) {
					String[] parts = ligne.split("\\s+");
					int p1 = Integer.parseInt(parts[0]);
					int p2 = Integer.parseInt(parts[1]);
					if(!nodes.contains(p1)) nodes.add(p1);
					if(!nodes.contains(p2)) nodes.add(p2);

				}
			}
			buff.close(); 
		}		
		catch (Exception e){
			System.out.println(e.toString());
		}	
		
		System.out.println("le nombre de noeuds est :"+ nodes.size());
		int V = nodes.size();
		int[][] result=new int[V][V];
		for (int i=0;i<V;i++) for (int j=0;j<V;j++) result[i][j]=0;

		//Deuxieme parcours pour calculer la matrice
		try{
			InputStream flux=new FileInputStream(nomFichier); 
			InputStreamReader lecture=new InputStreamReader(flux);
			BufferedReader buff=new BufferedReader(lecture);
			String ligne;
			while ((ligne=buff.readLine())!=null){

				if(!ligne.startsWith("#")) {
					String[] parts = ligne.split("\\s+");
					int p1 = Integer.parseInt(parts[0]);
					int p2 = Integer.parseInt(parts[1]);
				
					if(p1!=p2) {
						result[p1][p2] = 1;
						result[p2][p1] = 1;	
					}
				}
			}
			buff.close(); 
		}		
		catch (Exception e){
			System.out.println(e.toString());
		}	
		return result;
	}

	public long getQuantity(String nomFichier) {
		
		//lire le fichier de node-degree
		 Map<Integer,Integer> nodeDegree = new  HashMap<Integer,Integer>();
		try{
			InputStream flux=new FileInputStream("results/exercice4.txt"); 
			InputStreamReader lecture=new InputStreamReader(flux);
			BufferedReader buff=new BufferedReader(lecture);
			String ligne;
			while ((ligne=buff.readLine())!=null){

				if(!ligne.startsWith("#")) {
					String[] parts = ligne.split("\\s+");
					int node = Integer.parseInt(parts[0]);
					int degree = Integer.parseInt(parts[1]);
					nodeDegree.put(node, degree);			
				}
			}
			buff.close(); 
		}		
		catch (Exception e){
			System.out.println(e.toString());
		}
		
		//lire le graphe
		long quantity= 0 ;
		try{
			InputStream flux=new FileInputStream(nomFichier); 
			InputStreamReader lecture=new InputStreamReader(flux);
			BufferedReader buff=new BufferedReader(lecture);
			String ligne;
			while ((ligne=buff.readLine())!=null){

				if(!ligne.startsWith("#")) {
					String[] parts = ligne.split("\\s+");
					int p1 = Integer.parseInt(parts[0]);
					int p2 = Integer.parseInt(parts[1]);
					if(p1!=p2) {
						quantity+=nodeDegree.get(p1)*nodeDegree.get(p2);				
					}
				}
			}
			buff.close(); 
		}		
		catch (Exception e){
			System.out.println(e.toString());
		}	
		System.out.println("quantity = "+ quantity);
		return quantity;
	}

	public Map<Integer, ArrayList<Integer>> getListeAdjacence(){
		Map<Integer, ArrayList<Integer>> result = new  HashMap<Integer, ArrayList<Integer>>();
		for(Edge e : edges) {

			if(!result.containsKey(e.p)) {
				ArrayList<Integer> list = new ArrayList<Integer>();
				list.add(e.q);

				result.put(e.p,list );

			}else {

				ArrayList<Integer> list =  result.get(e.p);
				if(!list.contains(e.q)) list.add(e.q);


				result.put(e.p, list);				

			}



			if(!result.containsKey(e.q)) {
				ArrayList<Integer> list = new ArrayList<Integer>();
				list.add(e.p);

				result.put(e.q,list );

			}else {

				ArrayList<Integer> list =  result.get(e.q);
				if(!list.contains(e.p)) list.add(e.p);
				result.put(e.q, list);				
			}
		}
		return result;

	}

	public void printListeAdjacence() {
		for(Entry<Integer, ArrayList<Integer>> entry : mapAdjacence.entrySet()) { 
			int cle = entry.getKey();
			ArrayList<Integer> list = entry.getValue();
			System.out.print(cle+"   : ");

			System.out.print(" [");
			for(Integer i : list) {
				System.out.print(i+ " ");

			}
			System.out.print(" ]\n");

		}

	}

	public void loadGraphe(String nomFichier) {

		try{
			InputStream flux=new FileInputStream(nomFichier); 
			InputStreamReader lecture=new InputStreamReader(flux);
			BufferedReader buff=new BufferedReader(lecture);
			String ligne;
			while ((ligne=buff.readLine())!=null){

				if(!ligne.startsWith("#")) {
					String[] parts = ligne.split("\\s+");
					int p1 = Integer.parseInt(parts[0]);
					int p2 = Integer.parseInt(parts[1]);

					if(!noeuds.contains(p1))	noeuds.add(p1);
					if(!noeuds.contains(p2))	noeuds.add(p2);
					
					if(p1!=p2) {
						Edge edge = new Edge(p1,p2);
						edges.add(edge);
					}
				}
			}
			buff.close(); 
		}		
		catch (Exception e){
			System.out.println(e.toString());
		}
		
		System.out.println("loadGraphe finished !");
	}


	public void BFSconnectedComponents() {

		ArrayList<ArrayList<Integer>> components = new ArrayList<ArrayList<Integer>>();

		Set<Integer> marques = new HashSet<Integer>();

		while(marques.size()<noeuds.size()) {

			for(Integer node : noeuds) {


				if(!marques.contains(node)) {
					ArrayList<Integer> component = getComponent(node);
					marques.addAll(component);
					components.add(component);

				}
			}
		}
		System.out.println(" Il y a "+components.size()+"component total");
		System.out.println("Leurs tailles sont : ");
		for(ArrayList<Integer> c : components) {
			System.out.println(c.size());
		}
	}


	public ArrayList<Integer> getComponent(int node){
		ArrayList<Integer> component = new ArrayList<Integer>();
		//BFS
		Set<Integer> marques = new HashSet<Integer>();
		Queue<Integer> queue = new PriorityQueue<Integer>();
		queue.add(node);
		marques.add(node);

		while(!queue.isEmpty())
		{

			int  s = queue.poll();
			if(mapAdjacence.containsKey(s)) {
				for(Integer voisin :mapAdjacence.get(s) ) {
					if(!marques.contains(voisin)) {
						queue.add(voisin);
						marques.add(voisin);
					}				
				}
			}
		}
		component.addAll(marques);
		return component;

	}
	public void BFSComputeDiameter(ArrayList<Integer> component) {

		int maxDepth = 0;	
		for(Integer firstNode: component) {
			ArrayList<Pair> queue = new ArrayList<Pair>();
			Set<Integer> marques = new HashSet<Integer>();

			Pair nodeAndDepth = new Pair(firstNode,0);
			queue.add(nodeAndDepth);
			marques.add(firstNode);

			while(!queue.isEmpty())
			{
				Pair pair = queue.get(0);
				int node = pair.node;
				int depth = pair.depth;
				queue.remove(0);

				if (depth>maxDepth) maxDepth = depth;
				depth++;		

				for(Integer voisin :mapAdjacence.get(node) ) {
					if(!marques.contains(voisin)) {
						Pair p = new Pair(voisin,depth);
						queue.add(p);
						marques.add(voisin);
					}				
				}
			}

		}
		System.out.println("maxDepth = "+ maxDepth);
	}

	// matrix multiplication 
	void multiply(int A[][], int B[][], int C[][]) {
		int V = A.length;
		for (int i = 0; i < V; i++) { 
			for (int j = 0; j < V; j++) { 
				C[i][j] = 0; 
				for (int k = 0; k < V; k++) { 
					C[i][j] += A[i][k]* B[k][j]; 
				} 
			} 
		} 
	} 

	// Calculer trace of a matrix (sum of diagnonal elements) 
	int getTrace(int graph[][]) { 
		int trace = 0; 

		for (int i = 0; i < graph.length; i++) { 
			trace += graph[i][i]; 
		} 
		return trace; 
	} 
	int triangleInGraph(int graph[][]) { 

		int V = graph.length;
		// To Store graph^2 
		int[][] aux2 = new int[V][V];   

		// To Store graph^3 
		int[][] aux3 = new int[V][V]; 

		// Initialising aux matrices 
		// with 0 
		for (int i = 0; i < V; ++i) 
		{ 
			for (int j = 0; j < V; ++j) 
			{ 
				aux2[i][j] = aux3[i][j] = 0; 
			} 
		} 
		multiply(graph, graph, aux2); 
		multiply(graph, aux2, aux3); 

		int trace = getTrace(aux3); 

		return trace / 6; 
	} 
	public void calculClustering(String nomfichier) {
		
		//Calculer le nombre de triangles
		
		int nbTriangle = triangleInGraph(matriceAdjacence);

		System.out.println("nombre de triangle est " +nbTriangle);

		//	Calculer number of connected triples
		int somme = 0;	
		Set<Integer> dejaVue = new HashSet<Integer>();
		for(Edge edge: edges) {

			int k;
			if(!dejaVue.contains(edge.p)){
				k=mapAdjacence.get(edge.p).size();
				somme+= k*(k-1)/2;

				dejaVue.add(edge.p);

			}
			if(!dejaVue.contains(edge.q)){
				k=mapAdjacence.get(edge.q).size();
				somme+= k*(k-1)/2;
				dejaVue.add(edge.q);


			}
		}
		System.out.println("nombre de triplet connecte = "+somme);
		double G = (double)3*nbTriangle/ (double)somme;
		System.out.println("G = "+G);


	}

	public void WriteDegreeDistribution() {

					
					
					Map<Integer,Integer> degreeNodeMap = new HashMap<Integer,Integer>();
					
					for(Entry<Integer,Integer> entry : nodeDegreeMap.entrySet()) { 
						int node = entry.getKey();
					    int degree = entry.getValue();
		
					    
					    if(!degreeNodeMap.containsKey(degree)) {
					    	
					    	degreeNodeMap.put(degree, 1);
					    	
					    }else {
					    	
					    	degreeNodeMap.put(degree,degreeNodeMap.get(degree)+1 );
					    }
					
					}
					
					
					File result = new File("results/Exercice6.txt");
		
					FileWriter writer;
					try {
						writer = new FileWriter(result);
						  writer.write( "degree		number of node\n");
							for(Entry<Integer,Integer> entry : degreeNodeMap.entrySet()) { 
								int cle = entry.getKey();
							    int valeur = entry.getValue();
							    writer.write(cle + "	"+valeur +"\n");
							    
							
							}
							
					            writer.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				
					

	}
	public void writeExercice4(String nomFichier) {


		 Map<Integer,Integer> nodeDegree = new  HashMap<Integer,Integer>();
		System.out.println("Generer le resultat de exercice4......");

		File result = new File("results/exercice4.txt");
		try{
			InputStream flux=new FileInputStream(nomFichier); 
			InputStreamReader lecture=new InputStreamReader(flux);
			BufferedReader buff=new BufferedReader(lecture);
			String ligne;
			while ((ligne=buff.readLine())!=null){

				if(!ligne.startsWith("#")) {
					String[] parts = ligne.split("\\s+");
					int p1 = Integer.parseInt(parts[0]);
					int p2 = Integer.parseInt(parts[1]);

					
					if(p1!=p2) {
						
						
						if(!nodeDegree.containsKey(p1)) {
							nodeDegree.put(p1, 1);
						}else {
							nodeDegree.put(p1, nodeDegree.get(p1)+1);
						}
						
						if(!nodeDegree.containsKey(p2)) {
							nodeDegree.put(p2, 1);
						}else {
							nodeDegree.put(p2, nodeDegree.get(p2)+1);
						}
					}
				}
			}
			buff.close(); 
		}		
		catch (Exception e){
			System.out.println(e.toString());
		}
		try{
			FileWriter writer = new FileWriter(result);
			writer.write( "#node	degree\n");
			for(Entry<Integer, Integer> entry : nodeDegree.entrySet()) { 
				int cle = entry.getKey();
				int valeur = entry.getValue();
				writer.write(cle + "	"+valeur +"\n");
			}
			writer.close();

		}	
		catch (Exception e){
			System.out.println(e.toString());
		}


		System.out.println("le fichier de Node-degree se trouve dans results/exercice4.txt");
	}


	public static void main(String args[]) {
	
		//Ici pour modifier le nom de fichier a traiter
		String filename = email;
		LoadGraphe load = new LoadGraphe();
		
		

		/*Exercice4*/
		load.writeExercice4(filename);
		
		/*Exercice5*/
		long debut = System.currentTimeMillis();
		long q = load.getQuantity(filename);
		System.out.println("Temps d'execution pour calcul du Quantity(ms) : "+(System.currentTimeMillis()-debut));

		

		load.LoadGraphMemory(filename);
		
		/*Exercice6*/
		load.WriteDegreeDistribution();
		
		/*Exercice8*/
		load.BFSconnectedComponents();
		load.BFSComputeDiameter(load.getComponent(load.noeuds.get(0)));
		load.calculClustering(filename);

	}


}
