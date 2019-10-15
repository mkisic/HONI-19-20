for file in test/zapatak.in.*; 
	do time ./triangulacija_krivi_greedy < "$file" > "${file%.in.*}.out.${file##*.}"; 
done;

