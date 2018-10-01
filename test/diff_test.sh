readonly DIR_TARGET="trash"
readonly PROJECT_PATH="${PWD}"
readonly TEST_BIN="diff_test.sh"

# Loop over DIR_TARGET
# For each TARGET
echo "$DIR_TARGET" | while IFS= read -r -d ':' TARGET
do
	echo "$TARGET";
	# For each file (not directory)
	for file in `find "$TARGET" -type f -print`;
	do
		# Print the filename, then compute the diff
		# between ft_nm and the real nm
		echo "$file"; "$PROJECT_PATH"/"$TEST_BIN" $NM_FLAGS "$file" > diff.txt

		# When the last error code is 129, it means its a segfault ...
		if [[ $? -ge 129 ]]
		then
			echo "SEGV on $TARGET"
			exit 1
		fi

		nm $NM_FLAGS "$file" > diff_bin.txt

		# diff returns 0 when a difference occurs
		diff diff.txt diff_bin.txt || exit
	done
done
