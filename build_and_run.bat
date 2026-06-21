@echo off
g++ -std=c++11 -Wall -Wextra main.cpp tien_ich.cpp du_lieu.cpp ngan_hang_cau_hoi.cpp thi.cpp bao_cao.cpp menu.cpp -o main.exe
if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)
main.exe
