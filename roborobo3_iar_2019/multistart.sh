N=40

for (( i=1 ; i<=N ; i++))

do
	echo "############## SIMULATION n°$i ###############"
     ./roborobo -l config/IAR.properties -m 0.004 #execution du programme
done
echo "############## Fin de simulation ###############"
exit 0;
