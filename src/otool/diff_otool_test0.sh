make
echo "$DIR_TARGET" | while IFS= read -r -d ':' TARGET
do
	echo "$TARGET";
	for file in `ls -1 "$TARGET"`;
	do
		echo "$file"; ./ft_otool "$TARGET/$file" > diff.txt
		otool -t "$TARGET/$file" > diff_bin.txt
		diff diff.txt diff_bin.txt || exit
	done
done
