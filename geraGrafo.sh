i=32000
echo "strict digraph exemplo {"
for (int i=32000; i>0; i--) do
	echo
 	echo -e "\tY$i [Y=1];"
	echo -e "\tZ$i [Z=1];"
	echo -e "\tX$i [X=1];"
	# echo
	echo -e "\tA$i -> B$i;"
	echo -e "\tA$i -> C$i;"
	echo -e "\tB$i -> X$i;"
	echo -e "\tB$i -> Y$i;"
	echo -e "\tB$i -> Z$i;"
	echo -e "\tC$i -> Y$i;"
	echo -e "\tC$i -> Z$i;"
	echo -e "\tZ$i -> A$(($i-1));"
done
i=$((i+1))
echo
#echo -e "\tY$i [Y=1];"
# echo -e "\tZ$i [Z=1];"
#echo -e "\tX$i [X=1];"
#echo -e "\tA$((i-1)) [A=1];"
echo "}"
