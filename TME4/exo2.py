import random
import networkx as nx
import matplotlib.pyplot as plt 


# set its label to a label occurring with the 
# highest frequency among its neighbours
def set_label(node, voisins, labels):


	l_labels =[]
	for v in voisins:
		l_labels.append(labels[v])

	d = {x:l_labels.count(x) for x in l_labels}

	# print("labels[node]=",labels[node])

	max = 0
	max_label = d.values()[0]
	for k,v in d.items():
		if v>max:
			max = v
			max_label = k

	labels[node] = max_label


def load_graph(filename):
	file = open(filename,"r")
	edges = []
	for ligne in file:
		if not ligne[0]=="#":
			edge = ligne[:-1].split()
			edges.append((int(edge[0]),int(edge[1])))
	file.close()

	graphe = nx.from_edgelist(edges)
	return graphe

def plot_graph(graph, labels=None):
    dict_community = {}

    for k, v in labels.items():
        dict_community[v] = [k] if v not in dict_community.keys() \
            else dict_community[v] + [k]

    pos = nx.spring_layout(graph)  # positions for all nodes

    color = ['green', 'blue', 'red', 'yellow', 'orange', 'magenta',
             'cyan', 'chocolate', 'pink' ]

    i = 0
    for k, v in dict_community.items():
        while i >= len(color):
            i -= 1
        nx.draw_networkx_nodes(graph,
                               pos,
                               nodelist=v,
                               node_color=color[i],
                               node_size=50,
                               alpha=0.8)
        i += 1
    
    del dict_community
    
    nx.draw_networkx_edges(graph, pos, width=1.0, alpha=0.5)
    
   #  # Pour avoir les labels sur les node du plot mais c'est moins visible
   # # dict_labels = {}
   # dict_labels = {node: node for node, label in labels.items()}

   # nx.draw_networkx_labels(graph, pos)

    plt.axis('off')
    plt.savefig("comunity_youtube.png")  # save as png
    # nx.draw(graph)
    plt.show()

if __name__ == "__main__":
	# filename = "graphe.txt"
	filename = "data/com-youtube.ungraph.txt"
	graphe = load_graph(filename)
	nodes = list(graphe.nodes())
	edges = list(nx.edges(graphe))

	# Step 1:give a unique label to each node in the network
	labels = {node: node for node in nodes}

	nb_label = len(set(labels.values()))
	fin = False
	while not fin:

		# Step 2: Arrange the nodes in the network in a random order
		random.shuffle(nodes)

		# Step 3:for each node, set its label to a label occurring with the 
		# highest frequency among its neighbours
		for node in nodes:
		
			voisins = nx.neighbors(graphe, node)
			set_label(node, voisins ,labels)


		# Step 4:go to 2 as long as there exists a node with a labelthat 
		# does not have the highest frequency among itsneighbours.
		number_label_courrant = len(set(labels.values()))
		# print("the number of labels " ,number_label_courrant)

		if number_label_courrant == nb_label:
			fin = True
		else:
			nb_label = number_label_courrant

	plot_graph(graphe, labels)
