@ECHO OFF
SETLOCAL
WHERE gradle >NUL 2>&1
IF %ERRORLEVEL% NEQ 0 (
  ECHO gradle executable not found. Please install Gradle or use GitHub Actions setup-gradle.
  EXIT /B 1
)
gradle %*
