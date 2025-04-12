$directoryPath = "."
$extensionsToKeep = @('*.cpp', '*.h', '*.vcxproj', '*.sln', '*.ps1')

# Get all files except those with the specified extensions
$filesToDelete = Get-ChildItem -Path $directoryPath -Recurse -File -Force | Where-Object { 
    $shouldDelete = $true
    foreach ($extension in $extensionsToKeep) {
        if ($_.FullName -like "*$extension") {
            $shouldDelete = $false
            break
        }
    }
    return $shouldDelete
}

# Delete files
foreach ($file in $filesToDelete) {
    Remove-Item -Recurse -Path $file.FullName -Force
}

# Get and delete empty directories recursively
do {
    $dirsToDelete = Get-ChildItem -Path $directoryPath -Recurse -Directory -Force | Where-Object { 
        (Get-ChildItem -Path $_.FullName -Recurse -File -Force) -eq $null 
    }
    
    foreach ($dir in $dirsToDelete) {
        Remove-Item -Recurse -Path $dir.FullName -Force
    }
}
while ($dirsToDelete.Count -gt 0)
