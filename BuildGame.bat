@echo off

SET SFML_DIR=.\dependencies\SFML
SET FILE_TO_COMPILE="src\Game\MainGame.cpp"


WHERE /Q cl.exe
IF %ERRORLEVEL% NEQ 0 (
    ECHO Ten skrypt powinien byc uruchamiany z konsoli "x64 Native Tools Command Prompt for VS"
    BREAK
) ELSE (
    cl /JMC /permissive- /GS /W3 /Zc:wchar_t -I.\dependencies\SFML\include -I.\src /ZI /Gm- /Od /sdl /Fd"vc142.pdb" /Zc:inline /fp:precise /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope /Gd /MDd /FC /EHsc /nologo /diagnostics:column /std:c++20 %FILE_TO_COMPILE% %SFML_DIR%\lib\sfml-system-d.lib %SFML_DIR%\lib\sfml-main-d.lib %SFML_DIR%\lib\sfml-graphics-d.lib %SFML_DIR%\lib\sfml-audio-d.lib %SFML_DIR%\lib\sfml-window-d.lib /DEBUG /INCREMENTAL

    del *.ilk
    del *.obj
    del *.idb
    del *.pdb
)
