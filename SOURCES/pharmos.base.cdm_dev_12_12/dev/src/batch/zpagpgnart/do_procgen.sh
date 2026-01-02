#!/usr/bin/env ksh
# Generate zpagpgnart batch job wrappers for APX scheduler
# inside current directory
# -prog 1 (alias: zpagpgnart): transfer AGP to zartpreis
# -prog 2 (alias: zpagpgnart_clean): remove old entries from AGP internal load tables
#
# Tested with:
# procgen Version: 02.01.00.00 2016-01-12

procgen.sh << INPUT1
3
cdm
ws
0
zpagpgnart
import
1
2

0
0
13
0

1
1
1
1
INPUT1

sed -e '/ADDITIONAL_PARA/s#""#"-prog 1 -srv ich21 -db ich21"#' ch/cdm/ws/vars/zpagpgnart.vars > sed_tmp
mv sed_tmp ch/cdm/ws/vars/zpagpgnart.vars
sed -e '/Purpose/s#home.*#wss/ch/cdm/ws/bin/zpagpgnart#' ch/cdm/ws/proc/zpagpgnart.option > sed_tmp
mv sed_tmp ch/cdm/ws/proc/zpagpgnart.option

procgen.sh << INPUT2
3
cdm
ws
0
zpagpgnart_clean

0
0
13
0

1
1
1
1
INPUT2

sed -e '/ADDITIONAL_PARA/s#""#"-prog 2 -srv ich21 -db ich21"#' ch/cdm/ws/vars/zpagpgnart_clean.vars > sed_tmp
mv sed_tmp ch/cdm/ws/vars/zpagpgnart_clean.vars
sed -e '/Purpose/s#home.*#wss/ch/cdm/ws/bin/zpagpgnart#' ch/cdm/ws/proc/zpagpgnart_clean.option > sed_tmp
mv sed_tmp ch/cdm/ws/proc/zpagpgnart_clean.option

sed -e '/export readonly/s#=.*zpagpgnart#=/software/wss/ch/cdm/ws#' ch/cdm/ws/vars/cdm_ws_global.vars > sed_tmp
mv sed_tmp ch/cdm/ws/vars/cdm_ws_global.vars

for f in ch/cdm/ws/proc/*.sh; do
  sed -e '/readonly BINARY/s#zpagpgnart.*bin$#zpagpgnart#' "$f" > sed_tmp
  mv sed_tmp "$f"
done
