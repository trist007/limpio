@echo off

REM tcc -o parser.exe parser.c -luser32 -lkernel32
clang -g -o parser.exe parser.c -luser32 -lkernel32
