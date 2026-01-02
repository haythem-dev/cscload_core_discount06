set PATH_DOCU=.\codedocu\internal
if not exist %PATH_DOCU% mkdir %PATH_DOCU%
rmdir /s /q %PATH_DOCU%
..\..\ext\doxygen\doxygen\bin\doxygen.exe -d Preprocessor Doxyfile.internal

set PATH_DOCU=.\codedocu\customer
if not exist %PATH_DOCU% mkdir %PATH_DOCU%
rmdir /s /q %PATH_DOCU%
..\..\ext\doxygen\doxygen\bin\doxygen.exe -d Preprocessor Doxyfile.customer

ftp -i -s:doxy_ftp.txt


