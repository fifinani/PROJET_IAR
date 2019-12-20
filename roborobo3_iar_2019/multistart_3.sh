N=40

for (( i=1 ; i<=N ; i++))

do
	echo "############## SIMULATION n°$i ###############"
     ./roborobo -l config/IAR_3.properties #execution du programme
done
echo "############## Fin de simulation ###############"
exit 0;
