<#
.SYNOPSIS
    LeetCode Solutions - PowerShell Build Script (Windows Native)
.DESCRIPTION
    Compiles, runs, and verifies LeetCode solutions in C, C++, and Java.
    This is the Windows-native equivalent of the Makefile.
.EXAMPLE
    .\build.ps1 1              # Run problem 1 in default language (C)
    .\build.ps1 1 c++          # Run problem 1 in C++
    .\build.ps1 1 java         # Run problem 1 in Java
    .\build.ps1 help           # Show help
    .\build.ps1 summary        # Show summary table
    .\build.ps1 find 42        # Find problem 42
    .\build.ps1 verify all     # Verify all solutions
#>

param(
    [Parameter(Position=0)]
    [string]$Command = "help",
    
    [Parameter(Position=1)]
    [string]$Arg1 = "",
    
    [Parameter(Position=2)]
    [string]$Arg2 = ""
)

# ============================================================================
# Configuration
# ============================================================================
$Script:DefaultLang = "c"
$Script:OutDir = "Out"
$Script:LogsDir = "$OutDir/logs"
$Script:TempDir = "$OutDir/tmp"
$Script:Languages = @("c", "c++", "java")

# Compiler settings
$Script:CC = "gcc"
$Script:CFlags = "-std=c11 -Wall -Wextra -g"
$Script:CXX = "g++"
$Script:CXXFlags = "-std=c++20 -Wall -Wextra -g"

# Find clang-format in common locations
$Script:ClangFormat = $null
$clangFormatPaths = @(
    "clang-format",  # In PATH
    "C:\Program Files\LLVM\bin\clang-format.exe",
    "C:\Program Files (x86)\LLVM\bin\clang-format.exe",
    "$env:LOCALAPPDATA\Programs\LLVM\bin\clang-format.exe"
)
foreach ($path in $clangFormatPaths) {
    if ($path -eq "clang-format") {
        $cmd = Get-Command $path -ErrorAction SilentlyContinue
        if ($cmd) {
            $Script:ClangFormat = $cmd.Source
            break
        }
    } elseif (Test-Path $path) {
        $Script:ClangFormat = $path
        break
    }
}

# ============================================================================
# Helper Functions
# ============================================================================

function Get-LangDir($lang) {
    switch ($lang.ToLower()) {
        "c"    { return "C" }
        "c++"  { return "C++" }
        "java" { return "Java" }
        default { return "C" }
    }
}

function Get-FileExtension($lang) {
    switch ($lang.ToLower()) {
        "c"    { return "*.c" }
        "c++"  { return "*.cc" }
        "java" { return "*.java" }
        default { return "*.c" }
    }
}

function Find-SourceFile($num, $lang) {
    $dir = Get-LangDir $lang
    $ext = switch ($lang.ToLower()) {
        "c"    { ".c" }
        "c++"  { ".cc" }
        "java" { ".java" }
    }
    
    foreach ($difficulty in @("Easy", "Medium", "Hard")) {
        $path = Join-Path $dir $difficulty
        if (Test-Path $path) {
            $files = Get-ChildItem -Path $path -ErrorAction SilentlyContinue |
                     Where-Object { $_.Name -match "^$num-.*$([regex]::Escape($ext))$" }
            if ($files) {
                return $files[0]
            }
        }
    }
    return $null
}

function Get-Difficulty($filePath) {
    if ($filePath -match "Easy") { return "Easy" }
    if ($filePath -match "Medium") { return "Medium" }
    if ($filePath -match "Hard") { return "Hard" }
    return "Unknown"
}

function Verify-Output($problemNum, $outputFile, $difficulty) {
    $expectedFile = "Results/$difficulty/$problemNum.txt"
    
    if (-not (Test-Path $expectedFile)) {
        Write-Host ""
        Write-Host "Expected output file not found: $expectedFile"
        Write-Host "Skipping verification."
        return
    }
    
    $expectedLines = Get-Content $expectedFile
    $numTests = [int]$expectedLines[0]
    
    # Extract Output lines from actual output
    $actualContent = Get-Content $outputFile -ErrorAction SilentlyContinue
    $outputs = $actualContent | Where-Object { $_ -match "^Output:" } | ForEach-Object { $_ -replace "^Output:\s*", "" }
    
    if (-not $outputs) {
        Write-Host ""
        Write-Host "No 'Output:' lines found in program output."
        Write-Host "Make sure your solution prints 'Output: <result>' for verification."
        return
    }
    
    $passed = 0
    $failed = 0
    $mismatches = @()
    
    $i = 0
    foreach ($actual in $outputs) {
        if ($i -lt $numTests) {
            $expected = $expectedLines[$i + 1]
            if ($actual -eq $expected) {
                $passed++
            } else {
                $failed++
                $mismatches += "  Test $($i+1): Expected '$expected', got '$actual'"
            }
        }
        $i++
    }
    
    # Build expected outputs string
    $expectedOutputs = ($expectedLines[1..$numTests]) -join ", "
    
    Write-Host ""
    Write-Host "Expected Outputs: $expectedOutputs"
    if ($failed -eq 0) {
        Write-Host "Result: Passed ($passed test(s))" -ForegroundColor Green
    } else {
        Write-Host "Result: Failed ($failed mismatch(es) found)" -ForegroundColor Red
        $mismatches | ForEach-Object { Write-Host $_ }
    }
}

# ============================================================================
# Main Commands
# ============================================================================

function Show-Help {
    Write-Host ""
    Write-Host "  =======================================================================" -ForegroundColor Cyan
    Write-Host "                LeetCode Solutions - PowerShell Build Script             " -ForegroundColor Cyan
    Write-Host "  =======================================================================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "  Usage:" -ForegroundColor Yellow
    Write-Host "    .\build.ps1 <number>              Run problem with default lang (c)"
    Write-Host "    .\build.ps1 <number> c            Run problem in C"
    Write-Host "    .\build.ps1 <number> c++          Run problem in C++"
    Write-Host "    .\build.ps1 <number> java         Run problem in Java"
    Write-Host ""
    Write-Host "  Examples:" -ForegroundColor Yellow
    Write-Host "    .\build.ps1 153                   Run problem 153 (default: c)"
    Write-Host "    .\build.ps1 1 java                Run problem 1 in Java"
    Write-Host "    .\build.ps1 42 c++                Run problem 42 in C++"
    Write-Host ""
    Write-Host "  Verification & Summary:" -ForegroundColor Yellow
    Write-Host "    .\build.ps1 verify all            Verify all (C, C++, Java)"
    Write-Host "    .\build.ps1 verify c              Verify C solutions"
    Write-Host "    .\build.ps1 verify c++            Verify C++ solutions"
    Write-Host "    .\build.ps1 verify java           Verify Java solutions"
    Write-Host "    .\build.ps1 summary               Show & save summary"
    Write-Host ""
    Write-Host "  Formatting:" -ForegroundColor Yellow
    Write-Host "    .\build.ps1 format                Format all source files"
    Write-Host "    .\build.ps1 format c              Format only C files"
    Write-Host "    .\build.ps1 format c++            Format only C++ files"
    Write-Host "    .\build.ps1 format java           Format only Java files"
    Write-Host "    .\build.ps1 format-check          Check format without modifying"
    Write-Host ""
    Write-Host "  Other commands:" -ForegroundColor Yellow
    Write-Host "    .\build.ps1 find <N> [lang]       Find problem N"
    Write-Host "    .\build.ps1 compile <N> [lang]    Compile only (no run)"
    Write-Host "    .\build.ps1 run <N> [lang]        Run only (must be compiled)"
    Write-Host "    .\build.ps1 clean <N> [lang]      Clean specific problem"
    Write-Host "    .\build.ps1 clean_all [lang]      Clean all executables"
    Write-Host "    .\build.ps1 clean out             Delete Out/ folder"
    Write-Host ""
    Write-Host "  =======================================================================" -ForegroundColor Cyan
    Write-Host ""
}

function Invoke-Compile($num, $lang) {
    $file = Find-SourceFile $num $lang
    if (-not $file) {
        $dir = Get-LangDir $lang
        Write-Host "No source file found starting with $num- in $dir" -ForegroundColor Red
        return $null
    }
    
    $srcPath = $file.FullName
    $dir = $file.DirectoryName
    
    switch ($lang.ToLower()) {
        "c" {
            $exePath = $srcPath -replace "\.c$", ".exe"
            Write-Host "Compiling $($file.Name) to $($file.BaseName).exe"
            & $Script:CC $Script:CFlags.Split(' ') $srcPath -o $exePath 2>&1
            if ($LASTEXITCODE -eq 0 -and (Test-Path $exePath)) {
                return $exePath
            }
        }
        "c++" {
            $exePath = $srcPath -replace "\.cc$", ".exe"
            Write-Host "Compiling $($file.Name) to $($file.BaseName).exe"
            & $Script:CXX $Script:CXXFlags.Split(' ') $srcPath -o $exePath 2>&1
            if ($LASTEXITCODE -eq 0 -and (Test-Path $exePath)) {
                return $exePath
            }
        }
        "java" {
            Write-Host "Compiling $($file.Name)"
            Push-Location $dir
            & javac $file.Name 2>&1
            Pop-Location
            $classFile = Join-Path $dir "Test.class"
            if (Test-Path $classFile) {
                return $classFile
            }
        }
    }
    
    Write-Host "Compilation failed!" -ForegroundColor Red
    return $null
}

function Invoke-Run($num, $lang) {
    $file = Find-SourceFile $num $lang
    if (-not $file) {
        return
    }
    
    $dir = $file.DirectoryName
    $difficulty = Get-Difficulty $file.FullName
    
    # Create temp directory (use absolute path from script root)
    $scriptRoot = $PSScriptRoot
    if (-not $scriptRoot) { $scriptRoot = (Get-Location).Path }
    $tempDir = Join-Path $scriptRoot (Join-Path $Script:TempDir (Get-LangDir $lang))
    if (-not (Test-Path $tempDir)) {
        New-Item -ItemType Directory -Path $tempDir -Force | Out-Null
    }
    $tmpOutput = Join-Path $tempDir "$num.txt"
    
    switch ($lang.ToLower()) {
        "c" {
            $exePath = $file.FullName -replace "\.c$", ".exe"
            if (Test-Path $exePath) {
                Write-Host "Running $($file.BaseName).exe"
                & $exePath | Tee-Object -FilePath $tmpOutput
                Verify-Output $num $tmpOutput $difficulty
                Remove-Item $exePath -ErrorAction SilentlyContinue
            }
        }
        "c++" {
            $exePath = $file.FullName -replace "\.cc$", ".exe"
            if (Test-Path $exePath) {
                Write-Host "Running $($file.BaseName).exe"
                & $exePath | Tee-Object -FilePath $tmpOutput
                Verify-Output $num $tmpOutput $difficulty
                Remove-Item $exePath -ErrorAction SilentlyContinue
            }
        }
        "java" {
            $classFile = Join-Path $dir "Test.class"
            if (Test-Path $classFile) {
                Write-Host "Running Test.class"
                Push-Location $dir
                & java Test | Tee-Object -FilePath $tmpOutput
                Pop-Location
                Verify-Output $num $tmpOutput $difficulty
                Get-ChildItem -Path $dir -Filter "*.class" -ErrorAction SilentlyContinue | Remove-Item -Force
            }
        }
    }
    
    # Cleanup temp
    Remove-Item $tmpOutput -ErrorAction SilentlyContinue
}

function Invoke-Problem($num, $lang) {
    $langDir = Get-LangDir $lang
    Write-Host ""
    Write-Host "Running problem $num in $langDir ($lang)..." -ForegroundColor Cyan
    Write-Host ""
    
    $exe = Invoke-Compile $num $lang
    if ($exe) {
        Invoke-Run $num $lang
    }
}

function Find-Problem($num, $lang) {
    $file = Find-SourceFile $num $lang
    if ($file) {
        Write-Host "Found file: $($file.FullName)" -ForegroundColor Green
    } else {
        $dir = Get-LangDir $lang
        Write-Host "No file found starting with $num- in $dir" -ForegroundColor Red
    }
}

function Show-Summary {
    # Count files per language and difficulty
    $counts = @{
        "C" = @{ "Easy" = 0; "Medium" = 0; "Hard" = 0 }
        "C++" = @{ "Easy" = 0; "Medium" = 0; "Hard" = 0 }
        "Java" = @{ "Easy" = 0; "Medium" = 0; "Hard" = 0 }
        "Tests" = @{ "Easy" = 0; "Medium" = 0; "Hard" = 0 }
    }
    
    foreach ($diff in @("Easy", "Medium", "Hard")) {
        $counts["C"][$diff] = (Get-ChildItem -Path "C/$diff" -Filter "*.c" -ErrorAction SilentlyContinue).Count
        $counts["C++"][$diff] = (Get-ChildItem -Path "C++/$diff" -Filter "*.cc" -ErrorAction SilentlyContinue).Count
        $counts["Java"][$diff] = (Get-ChildItem -Path "Java/$diff" -Filter "*.java" -ErrorAction SilentlyContinue).Count
        $counts["Tests"][$diff] = (Get-ChildItem -Path "Results/$diff" -Filter "*.txt" -ErrorAction SilentlyContinue).Count
    }
    
    # Create output
    $output = @()
    $output += ""
    $output += "   LeetCode Solutions - Summary:"
    $output += ""
    $output += "  +------------+--------+--------+--------+--------+"
    $output += ("  | {0,-10} | {1,6} | {2,6} | {3,6} | {4,6} |" -f "Language", "Easy", "Medium", "Hard", "Total")
    $output += "  +------------+--------+--------+--------+--------+"
    
    foreach ($lang in @("C", "C++", "Java")) {
        $easy = $counts[$lang]["Easy"]
        $medium = $counts[$lang]["Medium"]
        $hard = $counts[$lang]["Hard"]
        $total = $easy + $medium + $hard
        $output += ("  | {0,-10} | {1,6} | {2,6} | {3,6} | {4,6} |" -f $lang, $easy, $medium, $hard, $total)
    }
    
    $output += "  +------------+--------+--------+--------+--------+"
    
    $totalEasy = $counts["C"]["Easy"] + $counts["C++"]["Easy"] + $counts["Java"]["Easy"]
    $totalMedium = $counts["C"]["Medium"] + $counts["C++"]["Medium"] + $counts["Java"]["Medium"]
    $totalHard = $counts["C"]["Hard"] + $counts["C++"]["Hard"] + $counts["Java"]["Hard"]
    $grandTotal = $totalEasy + $totalMedium + $totalHard
    
    $output += ("  | {0,-10} | {1,6} | {2,6} | {3,6} | {4,6} |" -f "Total", $totalEasy, $totalMedium, $totalHard, $grandTotal)
    $output += "  +------------+--------+--------+--------+--------+"
    
    $testEasy = $counts["Tests"]["Easy"]
    $testMedium = $counts["Tests"]["Medium"]
    $testHard = $counts["Tests"]["Hard"]
    $testTotal = $testEasy + $testMedium + $testHard
    
    $output += ("  | {0,-10} | {1,6} | {2,6} | {3,6} | {4,6} |" -f "Tests", $testEasy, $testMedium, $testHard, $testTotal)
    $output += "  +------------+--------+--------+--------+--------+"
    $output += ""
    
    # Problems detail table
    $output += "   Problems Detail:"
    $output += ""
    
    # Get all unique problems
    $problems = @{}
    foreach ($lang in @("C", "C++", "Java")) {
        $ext = switch ($lang) { "C" { "*.c" } "C++" { "*.cc" } "Java" { "*.java" } }
        foreach ($diff in @("Easy", "Medium", "Hard")) {
            $files = Get-ChildItem -Path "$lang/$diff" -Filter $ext -ErrorAction SilentlyContinue
            foreach ($file in $files) {
                if ($file.Name -match "^(\d+)-(.+)\.[^.]+$") {
                    $num = $matches[1]
                    $name = $matches[2]
                    if (-not $problems.ContainsKey($num)) {
                        $problems[$num] = @{
                            "Name" = $name
                            "Level" = $diff
                            "C" = $false
                            "C++" = $false
                            "Java" = $false
                            "Test" = $false
                        }
                    }
                    $problems[$num][$lang] = $true
                }
            }
        }
    }
    
    # Check for tests
    foreach ($diff in @("Easy", "Medium", "Hard")) {
        $testFiles = Get-ChildItem -Path "Results/$diff" -Filter "*.txt" -ErrorAction SilentlyContinue
        foreach ($file in $testFiles) {
            $num = $file.BaseName
            if ($problems.ContainsKey($num)) {
                $problems[$num]["Test"] = $true
            }
        }
    }
    
    $output += "  +------+----------------------------------------------+--------+------+------+------+------+"
    $output += ("  | {0,-4} | {1,-44} | {2,-6} | {3,-4} | {4,-4} | {5,-4} | {6,-4} |" -f "NUM", "Problem", "Level", " C ", "C++", "Java", "Test")
    $output += "  +------+----------------------------------------------+--------+------+------+------+------+"
    
    $sortedNums = $problems.Keys | Sort-Object { [int]$_ }
    foreach ($num in $sortedNums) {
        $p = $problems[$num]
        $name = if ($p["Name"].Length -gt 44) { $p["Name"].Substring(0, 41) + "..." } else { $p["Name"] }
        $cMark = if ($p["C"]) { "OK" } else { "  " }
        $cppMark = if ($p["C++"]) { "OK" } else { "  " }
        $javaMark = if ($p["Java"]) { "OK" } else { "  " }
        $testMark = if ($p["Test"]) { "OK" } else { "  " }
        $output += ("  | {0,4} | {1,-44} | {2,-6} |  {3}  |  {4}  |  {5}  |  {6}  |" -f $num, $name, $p["Level"], $cMark, $cppMark, $javaMark, $testMark)
    }
    
    $output += "  +------+----------------------------------------------+--------+------+------+------+------+"
    $output += ""
    $output += "   Total distinct problems: $($problems.Count)"
    $output += ""
    
    # Print output
    $output | ForEach-Object { Write-Host $_ }
    
    # Save to file
    if (-not (Test-Path $Script:OutDir)) {
        New-Item -ItemType Directory -Path $Script:OutDir -Force | Out-Null
    }
    $output | Out-File -FilePath "$Script:OutDir/Solutions_summary.txt" -Encoding UTF8
    Write-Host "   Summary saved to: $Script:OutDir/Solutions_summary.txt" -ForegroundColor Green
    Write-Host ""
}

function Invoke-Verify($langFilter) {
    $langs = if ($langFilter -eq "all") { @("c", "c++", "java") } else { @($langFilter) }
    
    Write-Host ""
    Write-Host "  Verifying solutions..." -ForegroundColor Cyan
    Write-Host ""
    
    $results = @()
    
    # Get script root for absolute paths
    $scriptRoot = $PSScriptRoot
    if (-not $scriptRoot) { $scriptRoot = (Get-Location).Path }
    
    foreach ($lang in $langs) {
        $langDir = Get-LangDir $lang
        $ext = switch ($lang) { "c" { "*.c" } "c++" { "*.cc" } "java" { "*.java" } }
        
        foreach ($diff in @("Easy", "Medium", "Hard")) {
            $searchPath = Join-Path $scriptRoot "$langDir/$diff"
            $files = Get-ChildItem -Path $searchPath -Filter $ext -ErrorAction SilentlyContinue
            foreach ($file in $files) {
                if ($file.Name -match "^(\d+)-") {
                    $num = $matches[1]
                    Write-Host "  Testing: $langDir - $($file.Name)" -ForegroundColor Yellow
                    
                    # Compile
                    $exe = Invoke-Compile $num $lang
                    if ($exe) {
                        # Create temp output with absolute path
                        $tempDir = Join-Path $scriptRoot (Join-Path $Script:TempDir $langDir)
                        if (-not (Test-Path $tempDir)) {
                            New-Item -ItemType Directory -Path $tempDir -Force | Out-Null
                        }
                        $tmpOutput = Join-Path $tempDir "$num.txt"
                        
                        # Run and capture output
                        switch ($lang.ToLower()) {
                            "c" {
                                $exePath = $file.FullName -replace "\.c$", ".exe"
                                & $exePath > $tmpOutput 2>&1
                                Remove-Item $exePath -ErrorAction SilentlyContinue
                            }
                            "c++" {
                                $exePath = $file.FullName -replace "\.cc$", ".exe"
                                & $exePath > $tmpOutput 2>&1
                                Remove-Item $exePath -ErrorAction SilentlyContinue
                            }
                            "java" {
                                Push-Location $file.DirectoryName
                                & java Test > $tmpOutput 2>&1
                                Pop-Location
                                Get-ChildItem -Path $file.DirectoryName -Filter "*.class" -ErrorAction SilentlyContinue | Remove-Item -Force
                            }
                        }
                        
                        # Verify
                        $expectedFile = Join-Path $scriptRoot "Results/$diff/$num.txt"
                        $status = "SKIP"
                        
                        if (Test-Path $expectedFile) {
                            $expectedLines = Get-Content $expectedFile
                            $numTests = [int]$expectedLines[0]
                            $actualContent = Get-Content $tmpOutput -ErrorAction SilentlyContinue
                            $outputs = $actualContent | Where-Object { $_ -match "^Output:" } | ForEach-Object { $_ -replace "^Output:\s*", "" }
                            
                            if ($outputs) {
                                $passed = 0
                                $i = 0
                                foreach ($actual in $outputs) {
                                    if ($i -lt $numTests -and $actual -eq $expectedLines[$i + 1]) {
                                        $passed++
                                    }
                                    $i++
                                }
                                $status = if ($passed -eq $numTests) { "PASS" } else { "FAIL" }
                            }
                        }
                        
                        $results += [PSCustomObject]@{
                            Num = $num
                            Problem = $file.BaseName -replace "^\d+-", ""
                            Lang = $langDir
                            Level = $diff
                            Status = $status
                        }
                        
                        Remove-Item $tmpOutput -ErrorAction SilentlyContinue
                    }
                }
            }
        }
    }
    
    # Print results table
    Write-Host ""
    Write-Host "  +------+----------------------------------+------+--------+--------+"
    Write-Host ("  | {0,-4} | {1,-32} | {2,-4} | {3,-6} | {4,-6} |" -f "NUM", "Problem", "Lang", "Level", "Status")
    Write-Host "  +------+----------------------------------+------+--------+--------+"
    
    foreach ($r in $results | Sort-Object { [int]$_.Num }) {
        $name = if ($r.Problem.Length -gt 32) { $r.Problem.Substring(0, 29) + "..." } else { $r.Problem }
        $color = switch ($r.Status) { "PASS" { "Green" } "FAIL" { "Red" } default { "Yellow" } }
        Write-Host ("  | {0,4} | {1,-32} | {2,-4} | {3,-6} | " -f $r.Num, $name, $r.Lang, $r.Level) -NoNewline
        Write-Host ("{0,-6}" -f $r.Status) -ForegroundColor $color -NoNewline
        Write-Host " |"
    }
    
    Write-Host "  +------+----------------------------------+------+--------+--------+"
    
    $passCount = ($results | Where-Object { $_.Status -eq "PASS" }).Count
    $failCount = ($results | Where-Object { $_.Status -eq "FAIL" }).Count
    $skipCount = ($results | Where-Object { $_.Status -eq "SKIP" }).Count
    
    Write-Host ""
    Write-Host "  Results: " -NoNewline
    Write-Host "$passCount PASS" -ForegroundColor Green -NoNewline
    Write-Host ", " -NoNewline
    Write-Host "$failCount FAIL" -ForegroundColor Red -NoNewline
    Write-Host ", " -NoNewline
    Write-Host "$skipCount SKIP" -ForegroundColor Yellow
    Write-Host ""
}

function Invoke-RunOnly($num, $lang) {
    $file = Find-SourceFile $num $lang
    if (-not $file) {
        $dir = Get-LangDir $lang
        Write-Host "No source file found starting with $num- in $dir" -ForegroundColor Red
        return
    }
    
    $dir = $file.DirectoryName
    $difficulty = Get-Difficulty $file.FullName
    
    # Create temp directory
    $scriptRoot = $PSScriptRoot
    if (-not $scriptRoot) { $scriptRoot = (Get-Location).Path }
    $tempDir = Join-Path $scriptRoot (Join-Path $Script:TempDir (Get-LangDir $lang))
    if (-not (Test-Path $tempDir)) {
        New-Item -ItemType Directory -Path $tempDir -Force | Out-Null
    }
    $tmpOutput = Join-Path $tempDir "$num.txt"
    
    switch ($lang.ToLower()) {
        "c" {
            $exePath = $file.FullName -replace "\.c$", ".exe"
            if (Test-Path $exePath) {
                Write-Host "Running $($file.BaseName).exe"
                & $exePath | Tee-Object -FilePath $tmpOutput
                Verify-Output $num $tmpOutput $difficulty
            } else {
                Write-Host "Executable not found. Please compile first with: .\build.ps1 compile $num $lang" -ForegroundColor Red
            }
        }
        "c++" {
            $exePath = $file.FullName -replace "\.cc$", ".exe"
            if (Test-Path $exePath) {
                Write-Host "Running $($file.BaseName).exe"
                & $exePath | Tee-Object -FilePath $tmpOutput
                Verify-Output $num $tmpOutput $difficulty
            } else {
                Write-Host "Executable not found. Please compile first with: .\build.ps1 compile $num $lang" -ForegroundColor Red
            }
        }
        "java" {
            $classFile = Join-Path $dir "Test.class"
            if (Test-Path $classFile) {
                Write-Host "Running Test.class"
                Push-Location $dir
                & java Test | Tee-Object -FilePath $tmpOutput
                Pop-Location
                Verify-Output $num $tmpOutput $difficulty
            } else {
                Write-Host "Class file not found. Please compile first with: .\build.ps1 compile $num $lang" -ForegroundColor Red
            }
        }
    }
    
    Remove-Item $tmpOutput -ErrorAction SilentlyContinue
}

function Invoke-CleanProblem($num, $lang) {
    $file = Find-SourceFile $num $lang
    if (-not $file) {
        $dir = Get-LangDir $lang
        Write-Host "No source file found starting with $num- in $dir" -ForegroundColor Red
        return
    }
    
    $dir = $file.DirectoryName
    $cleaned = $false
    
    switch ($lang.ToLower()) {
        "c" {
            $exePath = $file.FullName -replace "\.c$", ".exe"
            $xPath = $file.FullName -replace "\.c$", ".x"
            if (Test-Path $exePath) {
                Remove-Item $exePath -Force
                Write-Host "Deleted $($file.BaseName).exe" -ForegroundColor Green
                $cleaned = $true
            }
            if (Test-Path $xPath) {
                Remove-Item $xPath -Force
                Write-Host "Deleted $($file.BaseName).x" -ForegroundColor Green
                $cleaned = $true
            }
        }
        "c++" {
            $exePath = $file.FullName -replace "\.cc$", ".exe"
            $xPath = $file.FullName -replace "\.cc$", ".x"
            if (Test-Path $exePath) {
                Remove-Item $exePath -Force
                Write-Host "Deleted $($file.BaseName).exe" -ForegroundColor Green
                $cleaned = $true
            }
            if (Test-Path $xPath) {
                Remove-Item $xPath -Force
                Write-Host "Deleted $($file.BaseName).x" -ForegroundColor Green
                $cleaned = $true
            }
        }
        "java" {
            Get-ChildItem -Path $dir -Filter "*.class" -ErrorAction SilentlyContinue | ForEach-Object {
                Remove-Item $_.FullName -Force
                Write-Host "Deleted $($_.Name)" -ForegroundColor Green
                $cleaned = $true
            }
        }
    }
    
    if (-not $cleaned) {
        Write-Host "No executables found for problem $num in $(Get-LangDir $lang)" -ForegroundColor Yellow
    }
}

function Invoke-CleanAll($lang) {
    if ($lang) {
        $langs = @($lang)
    } else {
        $langs = @("C", "C++", "Java")
    }
    
    foreach ($l in $langs) {
        $langDir = if ($l -in @("c", "c++", "java")) { Get-LangDir $l } else { $l }
        Write-Host "Cleaning $langDir..." -ForegroundColor Cyan
        
        foreach ($diff in @("Easy", "Medium", "Hard")) {
            $path = "$langDir/$diff"
            if (Test-Path $path) {
                Get-ChildItem -Path $path -Filter "*.exe" -ErrorAction SilentlyContinue | Remove-Item -Force
                Get-ChildItem -Path $path -Filter "*.class" -ErrorAction SilentlyContinue | Remove-Item -Force
                Get-ChildItem -Path $path -Filter "*.x" -ErrorAction SilentlyContinue | Remove-Item -Force
            }
        }
    }
    Write-Host "Done!" -ForegroundColor Green
}

function Invoke-Format($lang) {
    # Check if clang-format is available
    $hasClangFormat = $null -ne $Script:ClangFormat
    
    if ($lang) {
        $langs = @($lang)
    } else {
        $langs = @("c", "c++", "java")
    }
    
    $modifiedFiles = @()
    
    foreach ($l in $langs) {
        $langDir = Get-LangDir $l
        $ext = switch ($l.ToLower()) {
            "c"    { @("*.c", "*.h") }
            "c++"  { @("*.cc", "*.h") }
            "java" { @("*.java") }
        }
        
        Write-Host ""
        Write-Host "Formatting $langDir files..." -ForegroundColor Cyan
        
        foreach ($diff in @("Easy", "Medium", "Hard")) {
            $path = "$langDir/$diff"
            if (Test-Path $path) {
                foreach ($pattern in $ext) {
                    $files = Get-ChildItem -Path $path -Filter $pattern -ErrorAction SilentlyContinue
                    foreach ($file in $files) {
                        $modified = $false
                        
                        if ($hasClangFormat) {
                            # Use clang-format for C, C++, and Java
                            $originalContent = Get-Content $file.FullName -Raw
                            & $Script:ClangFormat -i $file.FullName 2>$null
                            $newContent = Get-Content $file.FullName -Raw
                            if ($originalContent -ne $newContent) {
                                $modified = $true
                                $modifiedFiles += "$($file.Name) (clang-format)"
                            }
                        }
                        
                        # Ensure file ends with newline
                        $content = Get-Content $file.FullName -Raw
                        if ($content -and -not $content.EndsWith("`n")) {
                            $content += "`n"
                            Set-Content -Path $file.FullName -Value $content -NoNewline
                            if (-not $modified) {
                                $modifiedFiles += "$($file.Name) (added final newline)"
                            }
                        }
                    }
                }
            }
        }
    }
    
    Write-Host ""
    Write-Host "Formatting complete!" -ForegroundColor Green
    Write-Host ""
    
    if ($modifiedFiles.Count -gt 0) {
        Write-Host "Modified files:" -ForegroundColor Yellow
        $modifiedFiles | ForEach-Object { Write-Host "  - $_" }
    } else {
        Write-Host "No files were modified."
    }
    
    if (-not $hasClangFormat -and ($lang -in @("c", "c++", $null))) {
        Write-Host ""
        Write-Host "Note: clang-format not found. Install it for better C/C++ formatting:" -ForegroundColor Yellow
        Write-Host "  winget install LLVM.LLVM" -ForegroundColor DarkGray
    }
}

function Invoke-FormatCheck($lang) {
    $hasClangFormat = $null -ne $Script:ClangFormat
    
    if ($lang) {
        $langs = @($lang)
    } else {
        $langs = @("c", "c++", "java")
    }
    
    $unformattedFiles = @()
    
    foreach ($l in $langs) {
        $langDir = Get-LangDir $l
        $ext = switch ($l.ToLower()) {
            "c"    { @("*.c", "*.h") }
            "c++"  { @("*.cc", "*.h") }
            "java" { @("*.java") }
        }
        
        Write-Host "Checking $langDir files..." -ForegroundColor Cyan
        
        foreach ($diff in @("Easy", "Medium", "Hard")) {
            $path = "$langDir/$diff"
            if (Test-Path $path) {
                foreach ($pattern in $ext) {
                    $files = Get-ChildItem -Path $path -Filter $pattern -ErrorAction SilentlyContinue
                    foreach ($file in $files) {
                        if ($hasClangFormat) {
                            $result = & $Script:ClangFormat --dry-run --Werror $file.FullName 2>&1
                            if ($LASTEXITCODE -ne 0) {
                                $unformattedFiles += $file.Name
                            }
                        }
                        
                        # Check if file ends with newline
                        $content = Get-Content $file.FullName -Raw
                        if ($content -and -not $content.EndsWith("`n")) {
                            if ($file.Name -notin $unformattedFiles) {
                                $unformattedFiles += "$($file.Name) (missing final newline)"
                            }
                        }
                    }
                }
            }
        }
    }
    
    Write-Host ""
    if ($unformattedFiles.Count -gt 0) {
        Write-Host "The following files need formatting:" -ForegroundColor Red
        $unformattedFiles | ForEach-Object { Write-Host "  - $_" }
        Write-Host ""
        Write-Host "Run '.\build.ps1 format' to fix them." -ForegroundColor Yellow
    } else {
        Write-Host "All files are properly formatted!" -ForegroundColor Green
    }
    
    if (-not $hasClangFormat -and ($lang -in @("c", "c++", $null))) {
        Write-Host ""
        Write-Host "Note: clang-format not found. Install it for C/C++ format checking:" -ForegroundColor Yellow
        Write-Host "  winget install LLVM.LLVM" -ForegroundColor DarkGray
    }
}

function Invoke-Clean($target) {
    if ($target -eq "out") {
        if (Test-Path $Script:OutDir) {
            Remove-Item -Recurse -Force $Script:OutDir
            Write-Host "Deleted $Script:OutDir folder" -ForegroundColor Green
        } else {
            Write-Host "$Script:OutDir folder does not exist" -ForegroundColor Yellow
        }
    } elseif ($target -match "^\d+$") {
        # Clean specific problem number - but we need lang from Arg2
        Write-Host "Use '.\build.ps1 clean <number> [lang]' to clean a specific problem" -ForegroundColor Yellow
    } else {
        # Clean all executables (legacy behavior)
        Invoke-CleanAll $null
    }
}

# ============================================================================
# Main Entry Point
# ============================================================================

# Check if command is a number (problem number)
if ($Command -match "^\d+$") {
    $num = $Command
    $lang = if ($Arg1 -and $Arg1 -in $Script:Languages) { $Arg1 } else { $Script:DefaultLang }
    Invoke-Problem $num $lang
}
elseif ($Command -eq "help" -or $Command -eq "-h" -or $Command -eq "--help") {
    Show-Help
}
elseif ($Command -eq "summary") {
    Show-Summary
}
elseif ($Command -eq "find") {
    if ($Arg1) {
        $lang = if ($Arg2 -and $Arg2 -in $Script:Languages) { $Arg2 } else { $Script:DefaultLang }
        Find-Problem $Arg1 $lang
    } else {
        Write-Host "Usage: .\build.ps1 find <number> [lang]" -ForegroundColor Red
    }
}
elseif ($Command -eq "compile") {
    if ($Arg1) {
        $lang = if ($Arg2 -and $Arg2 -in $Script:Languages) { $Arg2 } else { $Script:DefaultLang }
        Invoke-Compile $Arg1 $lang
    } else {
        Write-Host "Usage: .\build.ps1 compile <number> [lang]" -ForegroundColor Red
    }
}
elseif ($Command -eq "run") {
    if ($Arg1) {
        $lang = if ($Arg2 -and $Arg2 -in $Script:Languages) { $Arg2 } else { $Script:DefaultLang }
        Invoke-RunOnly $Arg1 $lang
    } else {
        Write-Host "Usage: .\build.ps1 run <number> [lang]" -ForegroundColor Red
    }
}
elseif ($Command -eq "verify") {
    if ($Arg1 -eq "all" -or $Arg1 -in $Script:Languages) {
        Invoke-Verify $Arg1
    } else {
        Write-Host "Usage: .\build.ps1 verify <all|c|c++|java>" -ForegroundColor Red
    }
}
elseif ($Command -eq "format") {
    $lang = if ($Arg1 -and $Arg1 -in $Script:Languages) { $Arg1 } else { $null }
    Invoke-Format $lang
}
elseif ($Command -eq "format-check") {
    $lang = if ($Arg1 -and $Arg1 -in $Script:Languages) { $Arg1 } else { $null }
    Invoke-FormatCheck $lang
}
elseif ($Command -eq "clean") {
    if ($Arg1 -match "^\d+$") {
        # Clean specific problem
        $lang = if ($Arg2 -and $Arg2 -in $Script:Languages) { $Arg2 } else { $Script:DefaultLang }
        Invoke-CleanProblem $Arg1 $lang
    } elseif ($Arg1 -eq "out") {
        Invoke-Clean "out"
    } else {
        Invoke-Clean $Arg1
    }
}
elseif ($Command -eq "clean_all") {
    $lang = if ($Arg1 -and $Arg1 -in $Script:Languages) { $Arg1 } else { $null }
    Invoke-CleanAll $lang
}
else {
    Write-Host "Unknown command: $Command" -ForegroundColor Red
    Write-Host "Use '.\build.ps1 help' for usage information."
}
