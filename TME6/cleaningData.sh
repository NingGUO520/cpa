#!/bin/bash

for f in data/*.txt 
do
	FILE=$(echo $f| cut -d'/' -f 2)
	

     
	awk '{
			if ($1 > $2) {
				printf("%d ",$2); 
				printf("%d\n", $1);
				}else if($1 < $2) {
				printf("%d ",$1); 
				printf("%d\n", $2);
			}
		}'   < "$f"  |sort | uniq > "graphs_cleaned/$FILE"

done    
exit 0


