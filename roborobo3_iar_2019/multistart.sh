N=40

for (( i=1 ; i<=N ; i++))

do
<<<<<<< HEAD
     ./roborobo -l config/IAR.properties -m 0.004 #execution du programme
done
=======
	echo "############## SIMULATION n°$i ###############"
     ./roborobo -l config/IAR.properties #execution du programme
done
echo "############## Fin de simulation ###############"
exit 0;
>>>>>>> 3056f70098111da13aa56f7d0dc374ab38908641
