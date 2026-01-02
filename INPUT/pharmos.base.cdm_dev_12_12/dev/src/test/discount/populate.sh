#!/bin/sh
rm -f populate.log

for s in *.sql; do
  printf "Executing script $s"
  dbaccess -e ich21@zdev21_tcp "$s" >> populate.log 2>&1
  echo " ... returned $?"
done

exit 0

