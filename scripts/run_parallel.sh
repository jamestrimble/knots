if [ "$#" -ne 3 ]; then
  echo "Parameters: N i BASENAME"
else
  ../c/partial_search $1 $2 | shuf > $3.txt
  split -d -a10 -l10 $3.txt $3-
  ls $3-* | parallel "mv {} {}.partial"
  ls $3-*.partial | parallel "../c/finish_search {} > {}.out"
  cat $3-*.partial.out > $3_results.txt
  rm $3-*.partial
  rm $3-*.out
fi

