@echo off
@REM @Describe Binary copy of ts file to mp4 file

@REM Binary copy
copy /b .\video.ts .\video.mp4

@REM delete source ts file
@REM del .\video.ts
