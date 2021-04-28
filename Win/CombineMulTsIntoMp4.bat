@echo off
@REM @Describe Refer to local.m3u8 to merge multiple ts files in the current folder into mp4 files
@REM @Depende ffmpeg

for /d %%i in (*) do  (
    ffmpeg -allowed_extensions ALL -i %%i/local.m3u8 -c copy %%i.mp4
)
:end

@REM pause
