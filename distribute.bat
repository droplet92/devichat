@echo off
set ssh_account=%1
set id_rsa_location=%2
echo start update
echo upload server file
echo.
echo ssh connects to %ssh_account%...
ssh -i %id_rsa_location% %ssh_account% "rm -rf server/ & rm -rf client/"
ssh -i %id_rsa_location% %ssh_account% "mkdir server client"
echo.
echo sftp connects to %ssh_account%...
sftp -b upload.txt -i %id_rsa_location% %ssh_account%
echo.
echo upload server file done!
echo rerun server
echo.
echo ssh connects to %ssh_account%...
ssh -i %id_rsa_location% %ssh_account% "./rerun.tcsh"
echo.
echo rerun server done!
echo finish