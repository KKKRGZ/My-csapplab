S 38a08c,1 miss
L 38a0c0,8 miss
L 38a084,4 hit
L 38a080,4 hit

--- 
`index = (address>>b) & ((-1u) >> (64-s))`
L 30a080,4 miss eviction load  a[0][0] 加载A冲突
S 34a080,4 miss eviction store b[0][0] 刚刚set存入a,index相同存b,冲突不命中
L 30a084,4 miss eviction      00110000101000 00100 00100 load  a[0][1] 又要加载A 到相同sit 又要替换
S 34a0a0,4 miss store b[1][0] 00110100101000 00101 00000 b[1][0]所在的cache line的set index 为 00101
L 30a088,4 hit  load  a[0][2] 00110000101000 00100 01000 这个cache set已被加载过,直接用之前加载进来的就行了,所以hit
S 34a0c0,4 miss eviction store b[2][0] 00110100101000 00110 00000 set index = 00110
L 30a08c,4 hit load a[0][3] 每个cache line可以存32个字节 即8个整数
S 34a0e0,4 miss store b[3][0] 00110100101000 00111 00000 
L 30a090,4 hit load a[0][4] 命中
S 34a100,4 miss store b[4][0] 00110100101000 01000 00000 由规律看出这里转置矩阵b 是列优先 地址空间不连续
L 30a094,4 hit load a[5][0]
S 34a120,4 miss
L 30a098,4 hit load a[6][0]
S 34a140,4 miss
L 30a09c,4 hit load a[7][0] 到这里刚好一个cache line 末尾，set_index 都是  00100
S 34a160,4 miss
L 30a0a0,4 miss eviction a[1][0] 00110000101000 00101 00000
S 34a084,4 miss eviction
L 30a0a4,4 hit
S 34a0a4,4 miss eviction
L 30a0a8,4 miss eviction
S 34a0c4,4 hit
L 30a0ac,4 hit
S 34a0e4,4 hit
L 30a0b0,4 hit
S 34a104,4 hit
L 30a0b4,4 hit
S 34a124,4 hit
L 30a0b8,4 hit
S 34a144,4 hit
L 30a0bc,4 hit
S 34a164,4 hit
L 30a0c0,4 miss eviction
S 34a088,4 hit
L 30a0c4,4 hit
S 34a0a8,4 miss eviction
L 30a0c8,4 hit
S 34a0c8,4 miss eviction
L 30a0cc,4 miss eviction
S 34a0e8,4 hit
L 30a0d0,4 hit
S 34a108,4 hit
L 30a0d4,4 hit
S 34a128,4 hit
L 30a0d8,4 hit
S 34a148,4 hit
L 30a0dc,4 hit
S 34a168,4 hit
L 30a0e0,4 miss eviction
S 34a08c,4 hit
L 30a0e4,4 hit
S 34a0ac,4 hit
L 30a0e8,4 hit
S 34a0cc,4 miss eviction
L 30a0ec,4 hit
S 34a0ec,4 miss eviction
L 30a0f0,4 miss eviction
S 34a10c,4 hit
L 30a0f4,4 hit
S 34a12c,4 hit
L 30a0f8,4 hit
S 34a14c,4 hit
L 30a0fc,4 hit
S 34a16c,4 hit
L 30a100,4 miss eviction
S 34a090,4 hit
L 30a104,4 hit
S 34a0b0,4 hit
L 30a108,4 hit
S 34a0d0,4 hit
L 30a10c,4 hit
S 34a0f0,4 miss eviction
L 30a110,4 hit
S 34a110,4 miss eviction
L 30a114,4 miss eviction
S 34a130,4 hit
L 30a118,4 hit
S 34a150,4 hit
L 30a11c,4 hit
S 34a170,4 hit
L 30a120,4 miss eviction
S 34a094,4 hit
L 30a124,4 hit
S 34a0b4,4 hit
L 30a128,4 hit
S 34a0d4,4 hit
L 30a12c,4 hit
S 34a0f4,4 hit
L 30a130,4 hit
S 34a114,4 miss eviction
L 30a134,4 hit
S 34a134,4 miss eviction
L 30a138,4 miss eviction
S 34a154,4 hit
L 30a13c,4 hit
S 34a174,4 hit
L 30a140,4 miss eviction
S 34a098,4 hit
L 30a144,4 hit
S 34a0b8,4 hit
L 30a148,4 hit
S 34a0d8,4 hit
L 30a14c,4 hit
S 34a0f8,4 hit
L 30a150,4 hit
S 34a118,4 hit
L 30a154,4 hit
S 34a138,4 miss eviction
L 30a158,4 hit
S 34a158,4 miss eviction
L 30a15c,4 miss eviction
S 34a178,4 hit
L 30a160,4 miss eviction
S 34a09c,4 hit
L 30a164,4 hit
S 34a0bc,4 hit
L 30a168,4 hit
S 34a0dc,4 hit
L 30a16c,4 hit
S 34a0fc,4 hit
L 30a170,4 hit
S 34a11c,4 hit
L 30a174,4 hit
S 34a13c,4 hit
L 30a178,4 hit
S 34a15c,4 miss eviction
L 30a17c,4 hit
S 34a17c,4 miss eviction
S 38a08d,1 miss eviction