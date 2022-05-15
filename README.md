# Repo de Laboratorio 
### Miembros del grupo:
* Asier Ochoa | 1101331
* Yeuris Terrero | 1099399
* Carlos Garcia |
* Miguel Payton |
___
El repositorio contiene todos los proyectos de laboratorio. Cada proyecto tiene su propia carpeta con su
propio `CMakeLists.txt` ademas de uno global. Para configurar el proyecto en su maquina, debe correr cmake
con las opciones correspondientes al sistema operativo y compilador que vaya a usar.

Comando ejemplo para construir un proyecto CodeBlocks Unix usando el compilador `g++`:
```
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=/bin/make -DCMAKE_C_COMPILER=/bin/gcc -DCMAKE_CXX_COMPILER=/bin/g++ -G "CodeBlocks - Unix Makefiles" -S "Proyectos LabINS378L" -B "Proyectos LabINS378L/cmake-build-debug"
```