# StanProjectBuilder
Stan project builder

# Windows build information
## build
> g++ C:/mingw/include/json/json.cpp ./src/main/cpp/core/project/Module.cpp ./src/main/cpp/core/project/command/Command.cpp ./src/main/cpp/core/project/command/CommandModule.cpp ./src/main/cpp/core/project/command/CommandGroup.cpp ./src/main/cpp/core/project/Project.cpp ./src/main/cpp/helpers/project/ProjectBuilder.cpp ./src/main/cpp/helpers/threads/ExeThread.cpp ./src/main/cpp/helpers/project/TypesHelper.cpp ./src/main/cpp/helpers/files/FilesHelper.cpp ./src/main/cpp/Const.cpp ./src/main/cpp/ui/windows/MainWindow.cpp ./src/main/cpp/main.cpp -o spb -static -static-libgcc -static-libstdc++ -mwindows -lFOX-1.6 -lkernel32 -lwsock32