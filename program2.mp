# Just another test program
0:  a := 1 + 1;          # 2
1:  a := lshift(a + a);  # 8
2:  a := lshift(a + a);  # 32
3:  a := lshift(a + a);  # 128
4:  a := lshift(a + a);  # 512
5:  a := lshift(a + a);  # 2048
6:  a := lshift(a + a);  # 8192
7:  a := lshift(a + a);  # 32768
8:  a := lshift(a + a);  # 131072 -> Overflow here (undefined behavior)
