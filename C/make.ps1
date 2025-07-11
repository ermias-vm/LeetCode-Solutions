param(
    [string]$Number,
    [string]$Action = "all"
)

if (-not $Number) {
    Write-Host "Usage: .\make.ps1 <problem_number> [action]" -ForegroundColor Yellow
    Write-Host "Actions: compile, all (default)" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Green
    Write-Host "  .\make.ps1 217        # Compile, run, and clean" -ForegroundColor White
    Write-Host "  .\make.ps1 217 compile # Just compile" -ForegroundColor White
    exit 1
}

# Search for source file
$sourceFile = $null
$patterns = @("Easy\$Number-*.c", "Medium\$Number-*.c", "Hard\$Number-*.c")

foreach ($pattern in $patterns) {
    $files = Get-ChildItem -Path $pattern -ErrorAction SilentlyContinue
    if ($files) {
        $sourceFile = $files[0]
        break
    }
}

if (-not $sourceFile) {
    Write-Host "No source file found for problem $Number" -ForegroundColor Red
    exit 1
}

$executable = $sourceFile.FullName -replace '\.c$', '.exe'

# Check if TCC is available
$tccPath = ".\tcc\tcc.exe"
if (-not (Test-Path $tccPath)) {
    Write-Host "TCC not found. Downloading..." -ForegroundColor Yellow
    
    # Create directory for TCC
    New-Item -ItemType Directory -Force -Path ".\tcc" | Out-Null
    
    # Download portable TCC
    $tccUrl = "http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.27-win64-bin.zip"
    $tccZip = ".\tcc\tcc.zip"
    
    try {
        Write-Host "Downloading TCC..." -ForegroundColor Cyan
        Invoke-WebRequest -Uri $tccUrl -OutFile $tccZip
        
        Write-Host "Extracting TCC..." -ForegroundColor Cyan
        Expand-Archive -Path $tccZip -DestinationPath ".\tcc" -Force
        
        # Move files from subdirectory to main directory
        $extractedDir = Get-ChildItem ".\tcc" -Directory | Select-Object -First 1
        if ($extractedDir) {
            Get-ChildItem $extractedDir.FullName | Move-Item -Destination ".\tcc"
            Remove-Item $extractedDir.FullName -Recurse -Force
        }
        
        Remove-Item $tccZip -Force
        Write-Host "TCC installed successfully!" -ForegroundColor Green
    } catch {
        Write-Host "Failed to download TCC: $_" -ForegroundColor Red
        exit 1
    }
}

function Compile-Only {
    # Compile
    Write-Host "Compiling $($sourceFile.Name)..." -ForegroundColor Green
    $compileCmd = "& `"$tccPath`" -o `"$executable`" `"$($sourceFile.FullName)`""

    try {
        Invoke-Expression $compileCmd
        if ($LASTEXITCODE -ne 0) {
            Write-Host "Compilation failed!" -ForegroundColor Red
            exit 1
        }
    } catch {
        Write-Host "Compilation error: $_" -ForegroundColor Red
        exit 1
    }

    Write-Host "Compilation successful!" -ForegroundColor Green
    Write-Host "Executable: $([System.IO.Path]::GetFileName($executable))" -ForegroundColor Cyan
}

function Compile-Run-Clean {
    # Compile
    Write-Host "Compiling $($sourceFile.Name)..." -ForegroundColor Green
    $compileCmd = "& `"$tccPath`" -o `"$executable`" `"$($sourceFile.FullName)`""

    try {
        Invoke-Expression $compileCmd
        if ($LASTEXITCODE -ne 0) {
            Write-Host "Compilation failed!" -ForegroundColor Red
            exit 1
        }
    } catch {
        Write-Host "Compilation error: $_" -ForegroundColor Red
        exit 1
    }

    Write-Host "Compilation successful!" -ForegroundColor Green

    # Execute
    Write-Host "Running $([System.IO.Path]::GetFileName($executable))..." -ForegroundColor Cyan
    Write-Host "=" * 50 -ForegroundColor DarkGray
    & $executable
    Write-Host "=" * 50 -ForegroundColor DarkGray

    # Clean up
    Write-Host "Cleaning up..." -ForegroundColor Yellow
    Remove-Item $executable -ErrorAction SilentlyContinue
}

# Execute based on action
switch ($Action.ToLower()) {
    "compile" { Compile-Only }
    "all"     { Compile-Run-Clean }
    default {
        Write-Host "Invalid action: $Action" -ForegroundColor Red
        Write-Host "Valid actions: compile, all" -ForegroundColor Yellow
        exit 1
    }
}
