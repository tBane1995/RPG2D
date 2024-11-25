rmdir /s /q .\Build
mkdir Build
cd Build
cmake ..
REM cmake --build . --config Debug --verbose
REM cmake --build . --config Release --verbose
cd ..

mkdir Build\Debug

mkdir Build\Debug\assets
xcopy assets Build\Debug\assets /S /E

mkdir Build\Debug\basic_locations
xcopy basic_locations Build\Debug\basic_locations /S /E

mkdir Build\Debug\dialogues
xcopy dialogues Build\Debug\dialogues /S /E

mkdir Build\Debug\world
xcopy world Build\Debug\world /S /E

copy *.dll Build\Debug\
