@echo off
echo [%date% %time%] ��ʼͬ����GitHub
cd /d "D:\codes"

:: ��������޸ĵ��ļ�
git add .

:: �ύ����
git commit -m "�Զ��ύ: %date% %time%"

:: ���͵�GitHub
git push origin main

echo [%date% %time%] ͬ�����
pause