@echo off

set PROGRAM="%~1"

rem ��������� ����������� ������� ����� ��� ����� (�������� ��� �� ��������� ����� �������� ������������)
%PROGRAM% empty.dat %TEMP%\empty.dat
if ERRORLEVEL 1 goto err
fc.exe /B %TEMP%\empty.dat empty.dat
if ERRORLEVEL 1 goto err

rem ��������� ������
%PROGRAM% --compress input.dat %TEMP%\output.dat
if ERRORLEVEL 1 goto err
%PROGRAM% --decompress %TEMP%\output.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err
fc.exe /B input.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err

rem ��������� ����������
%PROGRAM% --encrypt 3 input.dat %TEMP%\output.dat
if ERRORLEVEL 1 goto err
%PROGRAM% --decrypt 3 %TEMP%\output.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err
fc.exe /B input.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err

rem ��������� ������� ����������
%PROGRAM% --encrypt 3 --encrypt 100500 input.dat %TEMP%\output.dat
if ERRORLEVEL 1 goto err
%PROGRAM% --decrypt 100500 --decrypt 3 %TEMP%\output.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err
fc.exe /B input.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err

rem ��������� ������� ���������� � ������
%PROGRAM% --encrypt 3 --encrypt 100500 --compress input.dat %TEMP%\output.dat
if ERRORLEVEL 1 goto err
%PROGRAM% --decompress --decrypt 100500 --decrypt 3 %TEMP%\output.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err
fc.exe /B input.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err

rem ���������, ��� ������ ������������ ���� ������������ ������
%PROGRAM% --encrypt 3 input.dat %TEMP%\output.dat
if ERRORLEVEL 1 goto err
%PROGRAM% --decrypt 100500 %TEMP%\output.dat %TEMP%\input.dat.restored
if ERRORLEVEL 1 goto err
fc.exe /B input.dat %TEMP%\input.dat.restored > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem ���������, ��� ����� ����������� ����������� ����, � ����� ������������
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