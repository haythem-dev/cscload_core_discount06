#!/usr/bin/ksh
###############################################################################################
# HEADER-DATA 
###############################################################################################
#Author:            d.gugonatu                                                                                 
#Creation-Date:     28.08.2023                                                                                
#Creation-Time:     12:00                                                                                     
#Creator:           author                                                 
#Creation-Type:     ONLINE_SERVER_PROCEDURE                                                                   
#Purpose:           export article plus price data for pharmacy portal in DE(only) for presentation only.            
###############################################################################################
set -x

while getopts h:u:p:l: flag
do
    case "${flag}" in
        h) host=${OPTARG};;
        u) user=${OPTARG};;
        p) pass=${OPTARG};;
        l) location=${OPTARG};;
    esac
done

db=ide21
odir="${DATA_PATH}/adg-productdata"
ofilename="products_deliverable_$(date +%Y%m%d).csv"
ofile="${odir}/${ofilename}"
ofileansi="${odir}/products_deliverable_ansi_$(date +%Y%m%d).csv"
delim="'|'"

echo "Host: $host";
#echo "User: $user";
#echo "Password: $pass";
echo "Local file: $ofile";
echo "Remote location: $location";

dbaccess $db << end1

create temp table kt (pzn integer, datum_lieferbar_ab integer);

create unique index i_kt on kt (pzn);

insert into kt (pzn, datum_lieferbar_ab)
select article_code::integer, datum_lieferbar_ab from zartikel z
inner join carticlecodes c on z.artikel_nr=c.articleno
where code_type=16 and datum_ah=0 and artikel_gesperrt=0 and zentr_eksperre=0 and bestellsperre=0 and nichtuebergh=0 and nahrungsergaenzung!='G' order by article_code;

-- select count(*) from kt;

unload to ${ofileansi} delimiter ${delim} select * from kt;

end1

iconv -c -f CP1252 -t UTF-8 ${ofileansi} > ${ofile}

rm ${ofileansi}

#-i turns off interactive prompting. 
#-n Restrains FTP from attempting the auto-login feature. 
#-v enables verbose and progress.

ftp -inv $host << EOF
user $user $pass
cd $location
lcd $odir
put $ofilename
bye

EOF

