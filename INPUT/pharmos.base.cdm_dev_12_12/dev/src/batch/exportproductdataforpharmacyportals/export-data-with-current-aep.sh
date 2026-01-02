#!/usr/bin/ksh
###############################################################################################
# HEADER-DATA 
###############################################################################################
#Author:            d.gugonatu                                                                                 
#Creation-Date:     07.07.2023                                                                                
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
ofilename="ifa_products_$(date +%Y%m%d).csv"
ofile="${odir}/${ofilename}"
ofileansi="${DATA_PATH}/adg-productdata/ifa_products_ansi_$(date +%Y%m%d).csv"
delim="'|'"

echo "Host: $host";
#echo "User: $user";
#echo "Password: $pass";
echo "Local file: $ofile";
echo "Remote location: $location";

dbaccess $db << end1

create temp table kt (artikel_nr integer, datumgueltigab integer, shop smallint, aep decimal(9,2), ke_mwst char(1));

create unique index i_kt on kt (artikel_nr);

-- total exported articles 
insert into kt select artikel_nr, 0, 0, 0.00, '0' from zartikel where (datum_ah=0 or datum_ah>(TO_CHAR(TODAY,'%Y%m%d')::INTEGER)-20000) and datum_ifaloesch=0;

-- outcommented selects for testing
-- select count(*) from kt;

create temp table kt1 (artikel_nr integer, datumgueltigab integer, shop smallint, aep decimal(9,2), ke_mwst char(1));

create unique index i_kt1 on kt1 (artikel_nr);

-- articles for the shop
insert into kt1 select distinct z.artikel_nr, max(p.datumgueltigab), 1, 0.00, '0' from zartikel z
inner join zartpreis p on z.artikel_nr=p.artikel_nr
where datum_ah=0 and datum_ifaloesch=0 and artikel_gesperrt=0 and zentr_eksperre=0 and bestellsperre=0 and nahrungsergaenzung!='G' and nichtuebergh=0 and (grosso>=0.01 or impfstoff>0) and hersteller_nr not in (5535, 37206, 37208, 37209, 80000)
and p.datumgueltigab<=TO_CHAR(TODAY,'%Y%m%d')::INTEGER group by artikel_nr;

MERGE INTO kt1 USING zartpreis ON kt1.artikel_nr=zartpreis.artikel_nr and kt1.datumgueltigab=zartpreis.datumgueltigab
WHEN MATCHED THEN UPDATE SET kt1.aep=zartpreis.aep, kt1.ke_mwst=zartpreis.ke_mwst; 

-- select count(*) from kt1;

MERGE INTO kt USING kt1 ON kt.artikel_nr = kt1.artikel_nr 
WHEN MATCHED THEN UPDATE SET kt.datumgueltigab = kt1.datumgueltigab, kt.shop = 1, kt.aep = kt1.aep;

-- select count(*) from kt where shop=1;
-- select count(*) from kt where datumgueltigab>0;

-- get informations to export - new field shop added to the end (0=No, 1=Yes)
create temp table kt2 (product_name char(50), pzn char(25), is_BTM char(1), kuehlartikel_level char(1), delivery char(1), delivery_notice char(1), country char(3), manufacturer_web char(60), manufacturer char(22), content char(9), form char(3),
 is_rx char(1), is_otc char(1), min_temp char(4), max_temp char(4), raw_storage char(1), min_order_quantity integer, chargenartikel char(1), aep decimal(9,2), vat char(1), validfrom integer, shop smallint);

create unique index i_kt2 on kt2 (pzn);

insert into kt2 (product_name, pzn, is_BTM, kuehlartikel_level, delivery, delivery_notice, country, manufacturer_web, manufacturer, content, form, is_rx, is_otc, min_temp, max_temp, raw_storage, min_order_quantity, chargenartikel, aep, vat, validfrom, shop)
select z.artikel_name as product_name, c.article_code as pzn, z.btm as is_BTM, z.kuehlartikel as kuehlartikel_level, '' as delivery, '' as delivery_notice, h.landeskuerzel as country, h.homepage as manufacturer_web, h.name as manufacturer,
	z.einheit as content, z.darreichform as form, z.rezeptpfl as is_rx, z.apothekenpfl as is_otc, '' as min_temp, '' as max_temp, '' as raw_storage, z.mindestbezug as min_order_quantity, z.chargenartikel as chargenartikel, kt.aep as aep, kt.ke_mwst as vat, kt.datumgueltigab as validfrom, kt.shop as shop
from zartikel z
inner join carticlecodes c on z.artikel_nr=c.articleno 
inner join herstel h on z.hersteller_nr = h.hersteller_nr
inner join kt on z.artikel_nr=kt.artikel_nr
where c.code_type=16 and z.artikel_nr not in (select a00pzn from zifaoart) order by c.article_code;

insert into kt2 (product_name, pzn, is_BTM, kuehlartikel_level, delivery, delivery_notice, country, manufacturer_web, manufacturer, content, form, is_rx, is_otc, min_temp, max_temp, raw_storage, min_order_quantity, chargenartikel, aep, vat, validfrom, shop)
select z.artikel_langname as product_name, c.article_code as pzn, z.btm as is_BTM, z.kuehlartikel as kuehlartikel_level, '' as delivery, '' as delivery_notice, h.landeskuerzel as country, h.homepage as manufacturer_web, h.name as manufacturer,
       z.einheit as content, z.darreichform as form, z.rezeptpfl as is_rx, z.apothekenpfl as is_otc, i.a05tmin as min_temp, i.a05tmax as max_temp, '' as raw_storage, z.mindestbezug as min_order_quantity, z.chargenartikel as chargenartikel, kt.aep as aep, kt.ke_mwst as vat, kt.datumgueltigab as validfrom, kt.shop as shop
from zartikel z
inner join carticlecodes c on z.artikel_nr=c.articleno 
inner join herstel h on z.hersteller_nr = h.hersteller_nr
inner join zifaoart i on z.artikel_nr=i.a00pzn 
inner join kt on z.artikel_nr=kt.artikel_nr
where c.code_type=16 order by c.article_code;

unload to ${ofileansi} delimiter ${delim} select * from kt2;

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

