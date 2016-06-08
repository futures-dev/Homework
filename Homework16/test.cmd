@echo off

toyBDD >res

echo n | comp res sample >testres 2>&1

IF %ERRORLEVEL% EQU 0 (
	echo Test 1 : PASSED
)

IF %ERRORLEVEL% NEQ 0 (
	echo Test 1 : FAILED
)

del /Q res
del /Q testres

pause
