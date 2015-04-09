mingw32-make 2>log || exit
.\bin\main test_io/test_in.txt test_io/test_out.txt 2>errors || exit
fc .\test_io\test_in.txt .\test_io\test_in.txt_decompressed || exit
del log
