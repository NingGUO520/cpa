import networkx as nx  
import matplotlib.pyplot as plt 
import random

G=nx.Graph()
G.add_nodes_from(range(400))
f = open("graphe.txt","w+")

p = 0.9
q = 0.1
for i in range(400):
	for j in range(400):
		if(i//100==j//100):
			if random.random()<p:
				f.write("%d %d\n" %(i,j))
				G.add_edge(i,j)
		elif random.random()<q:
			f.write("%d %d\n" %(i,j))
			G.add_edge(i,j)

f.close()
options = {'node_color': 'black','node_size': 100,'width': 3,}
nx.draw(G)
plt.savefig("exo1.png")
plt.show()
