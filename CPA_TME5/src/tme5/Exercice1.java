package tme5;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

public abstract class Exercice1 {

	private static int taille = 0;

	public static List<Integer>[] getAdjacencyList(String filename) {
		System.out.print("Chargement en mémoire du graphe \"" + filename + "\" dans une liste d'adjacence...");
		taille = 0;
		int max = Util.getMax(filename) + 1;
		List<Integer>[] adjencyList = new ArrayList[max];
		try {
			BufferedReader br = new BufferedReader(new FileReader(new File(filename)));
			String line = br.readLine();
			while (line != null) {
				String[] splitted = line.split("\\s");
				if (!splitted[0].equals("#")) {
					int s1 = Integer.parseInt(splitted[0]);
					int s2 = Integer.parseInt(splitted[1]);

					if (adjencyList[s1] == null) {
						taille++;
						adjencyList[s1] = new ArrayList<Integer>();
					}

					if (!adjencyList[s1].contains(s2))
						adjencyList[s1].add(s2);
				}
				line = br.readLine();
			}
			br.close();

			System.out.println("Fait");
			/*
			 * // Affichage optionnel for(int i=0; i<adjencyList.length; i++) { if
			 * (adjencyList[i] != null) { System.out.println("[" + i + "] : " +
			 * adjencyList[i].toString()); } }
			 */

			System.out.println("Taille : " + taille);

			return adjencyList;

		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
	}
	
	public static void PageRank(String filename, int t, float alpha) {
		System.out.println("Calcule de PageRank pour t = " + t + " et \u03B1 = " + alpha);
		List<Integer>[] adjencyList = getAdjacencyList(filename);
		
		powerIteration(adjencyList, t, alpha, true);
	}
	
	public static int[] computeOutD(List<Integer>[] adjencyList) {
		int[] res = new int[adjencyList.length];

		for (int i = 0; i < adjencyList.length; i++) {
			if (adjencyList[i] != null)
				res[i] = adjencyList[i].size();
		}

		return res;
	}

	public static float[] prodMatVect(List<Integer>[] adjencyList, float[] P, int[] outD) {

		float[] result = new float[adjencyList.length];

		for (int i = 0; i < adjencyList.length; i++) {
			if (adjencyList[i] != null) {
				for (Integer j : adjencyList[i]) {
					if (outD[j] != 0)
						result[j] += P[i] / outD[i];
				}
			}
		}

		return result;
	}

	public static float[] powerIteration(List<Integer>[] adjencyList, int t, float alpha, boolean save) {
		float[] weight = new float[adjencyList.length];
		int[] outD = computeOutD(adjencyList);

		float somme2 = 0;
		for (int i = 0; i < adjencyList.length; i++) {
			weight[i] = 1 / (float) taille;
			somme2 += weight[i];
		}
		
		System.out.println("Somme 2 :" + somme2);
		

		float[] tmp = weight;

		String progress;
		for (int i = 0; i < t; i++) {
			progress = "Étape : " + (i+1) + "/" + t;
			System.out.println(progress);
			System.out.flush();
			tmp = prodMatVect(adjencyList, tmp, outD);

			// P ← (1 − α) × P + α × I
			for (int j = 0; j < tmp.length; j++) {
				tmp[j] = (1 - alpha) * tmp[j] + alpha * weight[j];
			}
			
			double norm = 0;
			for (int j = 0; j < tmp.length; j++) {
				norm += tmp[j] * tmp[j];
			}
			
			norm = Math.sqrt(norm);

			// P ← NORMALIZE2(P)
			for (int j = 0; j < tmp.length; j++) {
				tmp[j] += (1 - norm) / (float) taille;
			}
		}
		
		/*for (int i = 0; i < tmp.length; i++) {
			System.out.println("["+i+"] : " + tmp[i]);
		}*/

		if (save) {
			try { 
				String file = "resultats/res.txt";
				System.out.print("Sauvegarde des resultats dans le fichier : \"" + file + "\"...");
				BufferedWriter bw = new BufferedWriter(new FileWriter(new File(file)));
				for (int i = 0; i < tmp.length; i++) {
					// Évite des erreurs dû au fichier sale
					if (adjencyList[i] != null) {
						String value = new BigDecimal(tmp[i]).toPlainString();
						value = value.replace(',', '.');
						bw.write(i + " " + value + "\n");
						bw.flush();
					}
				}
				bw.close();
				System.out.println("Fait");
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		return tmp;
	}

}
