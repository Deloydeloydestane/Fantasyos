#!/bin/sh
pkg update -y && pkg install clang git -y
git clone https://github.com
cd Fantasyos
clang os.c -o fantasyos
echo "./Fantasyos/fantasyos" >> ~/.bashrc
