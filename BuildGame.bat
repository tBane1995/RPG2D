@echo off

SET SFML_DIR="f:\libs\SFML\SFML-2.6.2"
SET FILE_TO_COMPILE="MainGame.cpp"
mkdir Build

cl /JMC /permissive- /GS /W3 /Zc:wchar_t -I%SFML_DIR%\include /ZI /Gm- /Od /sdl /Fd"vc142.pdb" /Zc:inline /fp:precise /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope /Gd /MDd /FC /EHsc /nologo /diagnostics:column /std:c++20 %FILE_TO_COMPILE% %SFML_DIR%\lib\sfml-system-d.lib %SFML_DIR%\lib\sfml-main-d.lib %SFML_DIR%\lib\sfml-graphics-d.lib %SFML_DIR%\lib\sfml-audio-d.lib %SFML_DIR%\lib\sfml-window-d.lib /DEBUG /INCREMENTAL

copy *.exe Build\
copy *.ilk Build\
copy *.obj Build\
copy *.idb Build\
copy *.pdb Build\
copy *.dll Build\

del *.exe
del *.ilk
del *.obj
del *.idb
del *.pdb
