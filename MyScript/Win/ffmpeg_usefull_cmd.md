
# 1. 让音频滞后0.45秒（让画面从0.45秒开始播放，PS: 下方源文件需重复一次）
```shell
ffmpeg -itsoffset 00:00:00.45 -i index.mp4 -i index.aac -map 0:v -map 1:a -vcodec copy -acodec copy index_turn.mp4
```

# 2. 顺时针旋转90度（transpose=1、逆时针90度=0、顺时针180度=2、顺时针270度=3）
```shell
ffmpeg -threads 2 -i index.mp4 -max_muxing_queue_size 1024 -vf transpose=1 index_r90.mp4
```

# 3. 区间剪切视频
```shell
ffmpeg -ss 00:00:01 -to 00:08:10 -i index.mp4 -vcodec copy -acodec copy indexOutput1.mp4 -y
```

# 4. 多个视频片段合并
## 4.1. 新建片段文件
filelist.txt
```
file 'indexOutput1.mp4'
file 'indexOutput2.mp4'
file 'indexOutput3.mp4'
```
## 4.2. 再合并多个片段
```shell
ffmpeg -f concat -i filelist.txt -vcodec copy -acodec copy index.mp4
# 或
ffmpeg -f concat -i filelist.txt -max_muxing_queue_size 1024 -vcodec copy -acodec copy index.mp4
```

# 视频拼接
```shell
ffmpeg -f concat -safe 0 -i filelist.txt -c copy index.mp4

ffmpeg -i "concat:index_cut1.mp4|index_cut2.mp4" -c copy index.mp4
```

# 5. 提取音频
```shell
ffmpeg -i index.mp4 -acodec copy -vn output.aac
```

# 6. 视频转高质量gif
```shell
ffmpeg -i index.mp4 -b 2048k index.gif
```
