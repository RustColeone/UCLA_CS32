g++ -o generateTests.exe generateTests.cpp
g++ -o testerHash.exe NameTablevhash.cpp testNameTable.cpp
g++ -o testerMap.exe NameTablevmap.cpp testNameTable.cpp
g++ -o testerSlow.exe NameTablevslow.cpp testNameTable.cpp

generateTests.exe
testerHash.exe
testerMap.exe
testerSlow.exe
