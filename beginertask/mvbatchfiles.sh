#! /bin/sh
i=1
cd batchfiles
for eachfile in `ls -1`
do
    mv $eachfile $i 
    ((i++))
done
cd ..
