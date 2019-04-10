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

	r = random.randint(0,len(d)-1)
	max_label ,max_number = list(d.items())[r]
	for label , number in d.items():
		if number >max_number:
			max_number = number
			max_label = label

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

    color = [ 'blue', 'red', 'yellow', 'orange', 'magenta',
             'cyan', 'chocolate', 'pink','green' ]

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
    
   #
    plt.axis('off')

    # sauvegarder
    plt.savefig("comunity_youtube.png")  
    # nx.draw(graph)
    plt.show()

def verifier_fin(graphe,nodes,labels):

	fin = True
	for node in nodes:
		# check if the node has the label of highest frequency among itsneighbours.
		voisins = nx.neighbors(graphe, node)

		l_labels =[]
		for v in voisins:
			l_labels.append(labels[v])

		d = {x:l_labels.count(x) for x in l_labels}

		r = random.randint(0,len(d)-1)
		max_label ,max_number = list(d.items())[r]

		for label , number in d.items():
			if number >max_number:
				max_number = number
				max_label = label

		if not labels[node] == max_label :
			fin = False
		

	return fin 
def LabelPropagation(){
	


}
if __name__ == "__main__":
	# filename = "graphe.txt"
	# filename = "data/exemple.txt"
	filename = "data/com-youtube.ungraph.txt"
	graphe = load_graph(filename)
	nodes = list(graphe.nodes())
	edges = list(nx.edges(graphe))

	# Step 1:give a unique label to each node in the network
	labels = {node: node for node in nodes}

	fin = False
	while not fin :

		# print("labels : ",labels)
		# Step 2: Arrange the nodes in the network in a random order
		random.shuffle(nodes)

		# Step 3:for each node, set its label to a label occurring with the 
		# highest frequency among its neighbours
		for node in nodes:
		
			voisins = nx.neighbors(graphe, node)
			set_label(node, voisins ,labels)

		# Step 4:go to 2 as long as there exists a node with a labelthat 
		# does not have the highest frequency among itsneighbours.

		if verifier_fin(graphe,nodes,labels):
			fin = True

		# print("the number of labels " ,number_label_courrant)

		
	#the numbers of communities obtained
	set_labels = set(labels.values())
	l_labels = list(labels.values())
	nb_communities = len(set_labels)
	print("the numbers of communities: ", nb_communities)
	
	size_community = {x:l_labels.count(x) for x in l_labels}
	print(size_community)


	plot_graph(graphe, labels)
