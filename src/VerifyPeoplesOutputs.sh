for group in {1..28}
do
echo "Group $group 's output:\r\n"
./CheckOutput InputFiles/input_group13.txt OutputFilesToVerify/output_from_$group.txt
done
