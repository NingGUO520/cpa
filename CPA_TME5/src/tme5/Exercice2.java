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


public abstract class Exercice2 {

	private static int taille = 0;

	public static List<Integer>[] getInAdjacencyList(String filename) {
		System.out.print("Chargement en mémoire du graphe \"" + filename + "\" dans une liste d'adjacence...");
		taille = 0;
		long debut, fin, res;
		debut = System.nanoTime();
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

					if (adjencyList[s2] == null) {
						taille++;
						adjencyList[s2] = new ArrayList<Integer>();
					}

					if (!adjencyList[s2].contains(s1)) {
						adjencyList[s2].add(s1);
					}
					
				}
				line = br.readLine();
			}
			br.close();

			System.out.println("Fait");

			// Affichage optionnel
			/*for (int i = 0; i < adjencyList.length; i++) {
				if (adjencyList[i] != null) {
					System.out.println("[" + i + "] : " + adjencyList[i].toString());
				}
			}*/
			
			fin = System.nanoTime();
			res = fin - debut;
			
			System.out.println("Execution time in second : " + res / 1000000000);

			return adjencyList;

		} catch(IOException e) {
			e.printStackTrace();
			return null;
		}
	}

	public static void computeWithOutDegrees(String filename) {
		System.out.println("Génération des résultats pour les degrés sortants");
		List<Integer>[] adjency = Exercice1.getAdjacencyList(filename);
		float[] ranks = Exercice1.powerIteration(adjency, 30, 0.15f, false);
		
		try { 
			String file = "resultats/res_out_degree.txt";
			System.out.print("Sauvegarde des resultats dans le fichier : \"" + file + "\"...");
			BufferedWriter bw = new BufferedWriter(new FileWriter(new File(file)));
			for (int i=0; i<ranks.length; i++) {
				// Évite des erreurs dû au fichier sale
				if (adjency[i] != null) {
					String value = new BigDecimal(ranks[i]).toPlainString();
					value = value.replace(',', '.');
					bw.write(value + " " + adjency[i].size() + "\n");
					bw.flush();
				}
			}
			bw.close();
			System.out.println("Fait");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void computeWithInDegrees(String filename) {
		System.out.println("Génération des résultats pour les degrés entrants");
		List<Integer>[] inDegre = getInAdjacencyList(filename);
		List<Integer>[] adjency = Exercice1.getAdjacencyList(filename);
		float[] ranks = Exercice1.powerIteration(adjency, 30, 0.15f, false);
		
		try { 
			String file = "resultats/res_in_degree.txt";
			System.out.print("Sauvegarde des resultats dans le fichier : \"" + file + "\"...");
			BufferedWriter bw = new BufferedWriter(new FileWriter(new File(file)));
			for (int i=0; i<ranks.length; i++) {
				// Évite des erreurs dû au fichier sale
				if (inDegre[i] != null) {
					String value = new BigDecimal(ranks[i]).toPlainString();
					value = value.replace(',', '.');
					bw.write(value + " " + inDegre[i].size() + "\n");
					bw.flush();
				}
			}
			bw.close();
			System.out.println("Fait");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void computeWithTwoAlphas(String filename, float alpha1, float alpha2) {
		System.out.println("Génération des résultats pour valeurs de alpha suivantes : " + alpha1 + ", " + alpha2);
		List<Integer>[] adjency = Exercice1.getAdjacencyList(filename);
		System.out.println("Calcul du premier page rank...");
		float[] ranks1 = Exercice1.powerIteration(adjency, 30, alpha1, false);
		System.out.println("Calcul du second page rank...");
		float[] ranks2 = Exercice1.powerIteration(adjency, 30, alpha2, false);
		try {
			String file = "resultats/res_two_alphas.txt";
			System.out.print("Sauvegarde des resultats dans le fichier : \"" + file + "\"...");
			BufferedWriter bw = new BufferedWriter(new FileWriter(new File(file)));
			for (int i=0; i<ranks1.length; i++) {
				// Évite des erreurs dû au fichier sale
				if (adjency[i] != null) {
					String value1 = new BigDecimal(ranks1[i]).toPlainString();
					value1 = value1.replace(',', '.');
					String value2 = new BigDecimal(ranks2[i]).toPlainString();
					value2 = value2.replace(',', '.');
					bw.write(value1 + " " + value2 + "\n");
					bw.flush();
				}
			}
			bw.close();
			System.out.println("Fait");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
