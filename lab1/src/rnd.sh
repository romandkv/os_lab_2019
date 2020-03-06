# !/bin/bash
for i in `seq 150`
do
od -An -N1 -i /dev/random
done
