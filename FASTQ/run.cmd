@echo off
mingw32-make 2>debug/errors || exit
for /L %%i in (1,1,1) do (
.\bin\main -c test_io/test_in.txt test_io/test_out.txt 2>debug/log || exit
fc .\test_io\test_in.txt .\test_io\test_in.txt_decompressed || exit 
echo Test %%i OK
)     
