@echo off
@REM @Describe Use 7-zip software to compress subfolders
@REM @Depende 7-zip


@REM 7-zip software installation path
@REM set SoftwarePath=C:\"Program Files"\7-Zip\7z.exe
set SoftwarePath=C:\"Program Files"\7-Zip\7z.exe

@REM the output compression format (eg. 7z, zip)
@REM set COmpressFormat=7z
set COmpressFormat=7z


for /d %%i in (*) do (echo %%i
%SoftwarePath% a "%%i.%COmpressFormat%" "%%i"
)
pause