package tme5;

public class MainTME5 {

	public static void main(String[] args) {
		// Fichier graphe
		String testFile = "test.txt";
		// String wikiFile = "/Vrac/CPA-PageRank/alr21--dirLinks--enwiki-20071018.txt";
		String wikiFile = "data/alr21--dirLinks--enwiki-20071018.txt";

		// Exercice 1
		 Exercice1.PageRank(wikiFile, 30, 0.2F);
		// Exercice1.PageRank(testFile, 30, 0.20F);
		// Exercice1.powerIteration(testFile, 5, 0.15F, true);

		// Exercice 2 - Degrés
//		Exercice2.computeWithInDegrees(wikiFile);
		// Exercice2.computeWithInDegrees(testFile);
		// Exercice2.computeWithOutDegrees(wikiFile);
		
		// Exercice 2 - Calcul avec les deux valeurs de alphas
		// Exercice2.computeWithTwoAlphas(wikiFile, 0.15f, 0.1f);
		// Exercice2.computeWithTwoAlphas(wikiFile, 0.15f, 0.2f);
		// Exercice2.computeWithTwoAlphas(wikiFile, 0.15f, 0.5f);
		// Exercice2.computeWithTwoAlphas(wikiFile, 0.15f, 0.9f);
	}
}
