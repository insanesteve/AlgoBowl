for group in {1..28}
do
./CheckOutput InputFiles/out_input.txt OutputFilesToVerify/output_group$group.txt
done
