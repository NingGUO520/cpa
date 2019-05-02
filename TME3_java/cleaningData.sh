#!/bin/bash
#variable du fichier
for f in graphs/*.txt 
do
	FILE=$(echo $f| cut -d'/' -f 2)
	

     
	awk '{
			if ($1 > $2) {
				printf("%d ",$2); 
				printf("%d\n", $1);
				}else {
				printf("%d ",$1); 
				printf("%d\n", $2);
			}
		}'   < "$f"  |sort | uniq > "after_cleaning/$FILE"

done    
exit 0


