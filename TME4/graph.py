import networkx as nx 
import matplotlib.pyplot as plt

G = nx.Graph()
G.add_nodes_from(range(10))

G.add_edge(1,2)
G.add_edge(0,9)

nx.draw(G, with_labels=True)
plt.show()