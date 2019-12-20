N=40

for (( i=1 ; i<=N ; i++))

do
	echo "############## SIMULATION n°$i ###############"
     ./roborobo -l config/IAR.properties #execution du programme
done

exit 0;
