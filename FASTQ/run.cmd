@echo off
mingw32-make 2>log || exit
for /L %%i in (1,1,1) do (
.\bin\main test_io/test_in.txt test_io/test_out.txt 2>errors || exit
fc .\test_io\test_in.txt .\test_io\test_in.txt_decompressed || exit
echo Test %%i OK
)
del log
