
$vsDevCmd = "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat"

# Laad de Visual Studio-omgeving en bouw het project.
cmd.exe /c "`"$vsDevCmd`" -arch=x64 && cmake --build build"

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build mislukt."
    exit $LASTEXITCODE
}

# Start het programma.
& ".\build\SFMLTest.exe"
