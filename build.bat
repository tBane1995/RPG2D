rmdir /s /q .\Build
mkdir Build
cd Build
cmake ..
REM cmake --build . --config Debug --verbose
REM cmake --build . --config Release --verbose
cd ..
mkdir Build\Debug
xcopy assets Build\Debug\ /E/H
xcopy basic_locations Build\Debug\ /E/H
xcopy dialogues Build\Debug\ /E/H
xcopy world Build\Debug\ /E/H
copy *.dll Build\Debug\
