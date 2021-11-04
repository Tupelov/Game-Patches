if ( Test-Path -Path "./Publish" -PathType Container ) { Remove-Item "./Publish" -Recurse }
New-Item "./Publish" -ItemType Directory

$allscripts = Get-ChildItem "./" -Include Publish.ps1 -File -Recurse | Select-Object -ExpandProperty FullName 
$solutiondir = Get-Location

foreach ($script in $allscripts) {
   $scriptdir = Split-Path($script)
   Set-Location -Path $scriptdir -PassThru
   &$script
   Set-Location -Path $solutiondir -PassThr
}