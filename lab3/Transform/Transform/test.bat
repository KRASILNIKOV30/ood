@echo off

set PROGRAM="%~1"

rem проверяем копирование пустого файла без опций (копируем его во временную папку текущего пользователя)
%PROGRAM% empty.dat %TEMP%\empty.dat
if ERRORLEVEL 1 goto err
fc.exe /B %TEMP%\empty.dat empty.dat
if ERRORLEVEL 1 goto err

rem проверяем сжатие
%PROGRAM% --compress input.dat %TEMP%\output.dat
if ERRORLEVEL 1 goto err
%PROGRAM% --decompress %TEMP%\output.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err
fc.exe /B input.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err

rem проверяем шифрование
%PROGRAM% --encrypt 3 input.dat %TEMP%\output.dat
if ERRORLEVEL 1 goto err
%PROGRAM% --decrypt 3 %TEMP%\output.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err
fc.exe /B input.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err

rem проверяем двойное шифрование
%PROGRAM% --encrypt 3 --encrypt 100500 input.dat %TEMP%\output.dat
if ERRORLEVEL 1 goto err
%PROGRAM% --decrypt 100500 --decrypt 3 %TEMP%\output.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err
fc.exe /B input.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err

rem проверяем двойное шифрование и сжатие
%PROGRAM% --encrypt 3 --encrypt 100500 --compress input.dat %TEMP%\output.dat
if ERRORLEVEL 1 goto err
%PROGRAM% --decompress --decrypt 100500 --decrypt 3 %TEMP%\output.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err
fc.exe /B input.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err

rem проверяем, что нельзя расшифровать файл неправильным ключом
%PROGRAM% --encrypt 3 input.dat %TEMP%\output.dat
if ERRORLEVEL 1 goto err
%PROGRAM% --decrypt 100500 %TEMP%\output.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err
fc.exe /B input.dat %TEMP%\input.dat.restored > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem проверяем, что можно зашифровать исполняемый файл, а затем расшифровать
%PROGRAM% --encrypt 3 %PROGRAM% %TEMP%\output.dat
if ERRORLEVEL 1 goto err
%PROGRAM% --decrypt 3 %TEMP%\output.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err
fc.exe /B %PROGRAM% %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1