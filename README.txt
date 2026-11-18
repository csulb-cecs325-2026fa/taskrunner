Task Master: CMake starter project

src/main.cpp contains the initial argument handling and task-file parser call.
Students will implement the list, run, and all jobs.

provided/tasks.h defines Task and Command.
provided/taskparser.h and provided/taskparser.cpp parse task files.
provided/uniquefile.h declares UniqueFile and implements its borrowing accessor.
provided/uniquefile.cpp contains student TODOs for acquisition and cleanup.

The provided/ files are intentionally excluded from the CMake target. Students
will move headers into include/, source files into src/, and update the target.
The include/ directory is already configured as a header search directory.

Configure from a Linux/WSL terminal:
  cmake -S . -B build

Build after moving the provided files and adding the source files to CMakeLists.txt:
  cmake --build build

examples/sample.tasks is copied to build/examples/ when CMake configures.
No third-party libraries are required by these initial files.
