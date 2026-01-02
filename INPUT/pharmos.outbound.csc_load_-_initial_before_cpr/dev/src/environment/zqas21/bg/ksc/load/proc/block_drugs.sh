#!/bin/sh

##################################################
export CLIENT_LOCALE=bg_bg.8859-5
export DB_LOCALE=bg_bg.8859-5
export DBMONEY=.
export DBDATE="MDY4/"
export GL_DATE=%m/%d/%iY

logfile=block_drugs.log
timestamp="date +'[%Y-%m-%d %H:%M:%S]'"

### log to logfile #############################################################
function f_log
# $1: log message
{
    printf "%s %s\n"         \
        "$(eval $timestamp)" \
        "$1"                 \
        >> $logfile
}

f_log "Start"

dbaccess obg21 -<<%
begin work;
select artikel_nr from artikelzentral
where
trunc(etartklasse1/512)-2*trunc(etartklasse1/(512*2))=1
into temp t_btms;

update artikellokal
set artikellokal.artikelaktiv = artikellokal.artikelaktiv + 7
where artikellokal.filialnr=25
and artikellokal.artikel_nr in
(select t_btms.artikel_nr from t_btms);

commit work;
%

f_log "Stop"

#################################################
