@set SolutionDir=%1
@set ProjectDir=%2
@set ThriftDir=%SolutionDir%\thrift

for %%f in (%ThriftDir%\idl\*.thrift) do ( call %SolutionDir%\..\ext\thrift\bin\thrift.cmd -v -strict -r -o %ThriftDir% -I %SolutionDir%\pxverbund\include --gen cpp %ThriftDir%\idl\%%~nxf > %ProjectDir%\%%~nxf.log )

#pause