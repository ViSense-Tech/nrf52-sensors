@echo off

set PATH=%~dp0\util;%PATH%
rem set TI_DS_ENABLE_LOGGING=1
rem set TI_DS_LOGGING_OUTPUT=c:/temp/my.log
rem echo ---ARGS--- %1 %2 %3 > c:/temp/my.log

if "%~1"=="not_chrome" goto NOT_CHROME else goto CHROME

:CHROME
rem echo ---CHROME--- >> c:/temp/my.log
"%~dp0/node.exe" "%~dp0/src/main_chrome.js" %*
goto END

:NOT_CHROME
rem echo ---NOT_CHROME--- >> c:/temp/my.log
"%~dp0/node.exe" "%~dp0/src/main.js" %*

:END

