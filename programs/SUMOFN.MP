0:   mar := pc; rd;  # 0 - 20, 1 - 28, 2 - 19
1:   rd; pc := pc + 1;
2:   a := mbr;
3:   mar := pc; rd;
4:   rd; d := 0;
5:   b := mbr;
6:   mar := a; rd;
7:   rd; pc := pc + 1;
8:   c := mbr;
9:   mar := b; rd;
10:  rd;
11:  c := c + (-1);
12:  e := mbr;
13:  d := d + e;
14:  b := b + 1;
15:  c := c; if z then goto 17;
16:  goto 9;
17:  mar := pc; rd;
18:  rd;
19:  a := mbr;
20:  mar := a; mbr := d; wr;
21:  wr;
# This program sums n-numbers (n located at m[20]) and stores the result in m[19]
# Numbers are stored in m[28] and higher