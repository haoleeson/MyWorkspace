@echo off
@REM @Describe Simple and efficient cutting Video Script
@REM @Depende ffmpeg

@REM Source video path(Absolute path and relative path both ok)
@REM set VideoSource=C:\Music\testVideo.mp4
set VideoSource=.\testVideo.mp4

@REM Cut video output path(Absolute path and relative path both ok)
@REM set VideoOutput=C:\Music\VideoOutput.mp4
set VideoOutput=.\VideoOutput.mp4

@REM Shear start time
set VideoStart=00:00:15

@REM Shear start time
set VideoEnd=00:02:00

@REM echo "start cutting video..."
ffmpeg -i "%VideoSource%" -vcodec copy -acodec copy -ss %VideoStart% -to %VideoEnd% "%VideoOutput%" -y

@REM if %errorlevel% == 0 (
@REM     echo -e "\e[1;42m Cut video success \e[0m"
@REM ) else (
@REM     echo -e "\e[1;41m Cut video failed \e[0m"
@REM )
@REM pause