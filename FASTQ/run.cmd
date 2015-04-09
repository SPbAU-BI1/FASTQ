.\src\generator\generator.exe
mingw32-make 2>log
.\bin\main test_io/test_in.txt test_io/test_out.txt 2>errors
fc .\test_io\test_in.txt .\test_io\test_in.txt_decompressed || exit
