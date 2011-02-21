mkdir Debug
mkdir Release

call ..\..\..\deps\scripts\copyOne.bat \dlls\wpcap\wpcap.dll .\Debug\
call ..\..\..\deps\scripts\copyOne.bat \dlls\wpcap\Packet.dll .\Debug\
call ..\..\..\deps\scripts\copyOne.bat \dlls\pthreadVC2.dll .\Debug\

call ..\..\..\deps\scripts\copyOne.bat \dlls\wpcap\wpcap.dll .\Release\
call ..\..\..\deps\scripts\copyOne.bat \dlls\wpcap\Packet.dll .\Release\
call ..\..\..\deps\scripts\copyOne.bat \dlls\pthreadVC2.dll .\Release\
