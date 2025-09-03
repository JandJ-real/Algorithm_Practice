@echo off
echo [%date% %time%] 开始同步到GitHub
cd /d "D:\codes"

:: 添加所有修改的文件
git add .

:: 提交更改
git commit -m "自动提交: %date% %time%"

:: 推送到GitHub
git push origin main

echo [%date% %time%] 同步完成
pause