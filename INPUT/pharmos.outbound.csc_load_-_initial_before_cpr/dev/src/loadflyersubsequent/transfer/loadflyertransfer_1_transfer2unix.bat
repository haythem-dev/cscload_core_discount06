@echo off
echo Loadflyer transfer process, this is step 1 of 4
set rc=0
if not exist z:\ ( set drv=z: && goto :founddrv )
if not exist y:\ ( set drv=y: && goto :founddrv )
if not exist x:\ ( set drv=x: && goto :founddrv )
if not exist w:\ ( set drv=w: && goto :founddrv )
if not exist v:\ ( set drv=v: && goto :founddrv )
if not exist u:\ ( set drv=u: && goto :founddrv )
if not exist t:\ ( set drv=t: && goto :founddrv )
if not exist s:\ ( set drv=s: && goto :founddrv )
if not exist r:\ ( set drv=r: && goto :founddrv )
if not exist q:\ ( set drv=q: && goto :founddrv )
if not exist p:\ ( set drv=p: && goto :founddrv )
if not exist o:\ ( set drv=o: && goto :founddrv )
if not exist n:\ ( set drv=n: && goto :founddrv )
if not exist m:\ ( set drv=m: && goto :founddrv )
if not exist l:\ ( set drv=l: && goto :founddrv )
if not exist k:\ ( set drv=k: && goto :founddrv )
if not exist j:\ ( set drv=j: && goto :founddrv )
if not exist h:\ ( set drv=h: && goto :founddrv )
:notfound
echo Failed to allocate drive, transfer process failed
set rc=3
goto :End
:founddrv
set drv=%drv: =%
echo Drive found = %drv%
echo Connecting windows drive...
net use %drv% "\\NTNX-DENU01CL5002-1.phoenix.loc\data$" /user:"PHOENIX\svc.ftp.apxtowindows" "ewkTGrsPhx!2"
if exist %drv%\ (
  echo Drive successfully connected
  %drv%
  cd \DEPPE1\Abteilung\SRM_WKZRechnungen\Transfer_IDF-gesteuerte_Wannenbeilage\
  echo Scanning for new CSV files...
  if exist ftp.txt (del ftp.txt)
  echo Preparing ftp transfer...
  echo open zdev21>> ftp.txt
  echo devuser>> ftp.txt
  echo phosix+>> ftp.txt
  echo ascii>> ftp.txt
  echo cd /software/wss/de/ksc/load/data/flyer>> ftp.txt
  echo mput *.csv>> ftp.txt
  echo disconnect>> ftp.txt
  echo quit>> ftp.txt
  ftp -i -s:ftp.txt
  if ERRORLEVEL 1 (
    echo FTP not successful for csv files
    set rc=2
  ) else (
    echo FTP successful for csv files
  )
  del ftp.txt
  del *.csv
  echo Transfer done
  c:
  net use %drv% /delete
) else (
  echo Drive not successfully connected
  set rc=3
)
:End
echo Returncode %rc%
pause
exit %rc%