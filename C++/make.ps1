param(
    [string]$Number,
    [ValidateSet("all", "compile", "clean")]
    [string]$Action
)

# --- Functions for Actions ---
function Compile-Run-Clean {
    # 1. Compile
    Write-Host "Compiling $($sourceFile.Name)..." -ForegroundColor Green
    g++ -std=c++17 -Wall -Wextra -g "$($sourceFile.FullName)" -o "$executable"
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Compilation failed!" -ForegroundColor Red
        exit 1
    }
    Write-Host "Compilation successful!" -ForegroundColor Green

    # 2. Execute
    Write-Host "Running $([System.IO.Path]::GetFileName($executable))..." -ForegroundColor Cyan
    Write-Host "==================================================" -ForegroundColor DarkGray
    & $executable
    Write-Host "==================================================" -ForegroundColor DarkGray

    # 3. Clean up
    Write-Host "Cleaning up..." -ForegroundColor Yellow
    Remove-Item $executable -ErrorAction SilentlyContinue
}

function Compile-Only {
    Write-Host "Compiling $($sourceFile.Name)..." -ForegroundColor Green
    g++ -std=c++17 -Wall -Wextra -g "$($sourceFile.FullName)" -o "$executable"

    if ($LASTEXITCODE -eq 0) {
        Write-Host "Compilation successful!" -ForegroundColor Green
        Write-Host "Executable created at: $executable" -ForegroundColor Cyan
    } else {
        Write-Host "Compilation failed!" -ForegroundColor Red
        exit 1
    }
}

function Clean-All {
    Write-Host "Cleaning all .exe files..." -ForegroundColor Yellow
    $exeFiles = Get-ChildItem -Path ".\" -Recurse -Filter "*.exe"
    if ($exeFiles) {
        foreach ($file in $exeFiles) {
            Write-Host "Removing $($file.FullName)" -ForegroundColor DarkGray
            Remove-Item -Path $file.FullName -Force
        }
        Write-Host "Cleanup complete." -ForegroundColor Green
    } else {
        Write-Host "No .exe files found to clean." -ForegroundColor Cyan
    }
}

# --- Main Logic ---

# Handle 'clean' action separately as it doesn't require a number
if ($Action -eq "clean") {
    Clean-All
    exit 0
}

# Set default action if not specified
if (-not $Action) {
    $Action = "all"
}

# --- Help Message & Number Check ---
if (-not $Number) {
    Write-Host "Usage: .\make.ps1 <problem_number> [action]" -ForegroundColor Yellow
    Write-Host "Actions: all (default), compile, clean" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Green
    Write-Host "  .\make.ps1 217        # Compiles, runs, and cleans the executable" -ForegroundColor White
    Write-Host "  .\make.ps1 217 compile # Only compiles the code" -ForegroundColor White
    Write-Host "  .\make.ps1 clean      # Removes all .exe files from the C++ directory" -ForegroundColor White
    exit 1
}

# --- Find Source File ---
$sourceFile = Get-ChildItem -Path "Easy\$Number-*.cc", "Medium\$Number-*.cc", "Hard\$Number-*.cc" -ErrorAction SilentlyContinue | Select-Object -First 1

if (-not $sourceFile) {
    Write-Host "Error: Source file for problem '$Number' not found." -ForegroundColor Red
    exit 1
}

$executable = $sourceFile.FullName -replace '\.cc$', '.exe'

# --- Execute Action ---
switch ($Action) {
    "all"     { Compile-Run-Clean }
    "compile" { Compile-Only }
}