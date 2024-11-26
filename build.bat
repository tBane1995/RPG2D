rmdir /s /q .\Build
mkdir Build
cd Build
cmake ..
REM cmake --build . --config Debug --verbose
REM cmake --build . --config Release --verbose
cd ..
