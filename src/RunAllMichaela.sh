# This script runs AlgoBowl on all AlgoBowl inputs. 
# We plan to run this script multiple times to ensure a good solution is found

#!/bin/bash
for int in {1..50}
do 
	for group in {1..27}
	do
		echo "Starting input_group$group.txt"
		./AlgoBowl InputFiles/input_group$group.txt MichaelaOutputs/output_group$group.txt &
		echo "done."
	done
	wait
	sleep 5
done
