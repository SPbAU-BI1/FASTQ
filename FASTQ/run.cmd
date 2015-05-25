@echo off
mingw32-make 2>debug/errors || exit
for /L %%i in (1,1,1) do (
.\bin\main -c test_io/test_in.txt test_io/test_out.txt 2>debug/log || exit
.\bin\main -d test_io/test_out.txt test_io/test_in.txt_decompressed 2>debug/log2 || exit
fc .\test_io\test_in.txt .\test_io\test_in.txt_decompressed || exit 
echo Test %%i OK
)     
