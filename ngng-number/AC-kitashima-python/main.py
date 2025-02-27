#!/usr/bin/env pypy3
# 桁DPのC++からの移植版

mod = 998244353

s = input()

dp = []

n_index = 0
ng_index = 0
i = 0
n = s[0]
while i < len(s) and s[i] == n: i+=1
n_index = i
if i != len(s):
    g = s[i]
    while i < len(s) and s[i] == g: i+=1
    ng_index = i

dp.append([[0, 0, 0, 0], [0, 0, 0, 0]])
dp[0][0][0] = 1
dp[0][1][0] = int(n) - 1
for i in range(1, len(s)):
    dp.append([[0, 0, 0, 0], [0, 0, 0, 0]])
    
    # n数
    if i < n_index:
        dp[i][0][0] = 1
    elif i == n_index and s[i] > n:
        dp[i][1][0] += 1
    dp[i][1][0] += dp[i - 1][1][0]
    dp[i][1][0] += 9
    
    # ng数
    if i < n_index:
        dp[i][1][1] += int(n)
    elif n_index <= i < ng_index:
        dp[i][0][1] = 1
    elif i == ng_index and s[i] > g:
        dp[i][1][1] += 1
    if i == n_index:
        dp[i][1][1] += int(g) - (1 if n < g else 0)
    dp[i][1][1] += dp[i - 1][1][1]
    dp[i][1][1] += dp[i - 1][1][0] * 9
    
    # ngn数
    if i < ng_index and dp[i - 1][0][1] and s[i] > n:
        dp[i][1][2] += 1
    if i == ng_index or (i > ng_index and (dp[i - 1][0][2] or dp[i - 1][0][3])):
        if s[i] == n:
            dp[i][0][2] = 1
        elif s[i] > n:
            dp[i][1][2] += 1
    dp[i][1][2] += dp[i - 1][1][1]
    dp[i][1][2] += dp[i - 1][1][2]
    dp[i][1][2] += dp[i - 1][1][3]
    
    # ngng数
    if dp[i - 1][0][2] or dp[i - 1][0][3]:
        if s[i] == g:
            dp[i][0][3] = 1
        elif s[i] > g:
            dp[i][1][3] += 1
    dp[i][1][3] += dp[i - 1][1][2]
    dp[i][1][3] += dp[i - 1][1][3]
    
    # modをとる
    for j in range(2):
        for k in range(4):
            dp[i][j][k] %= mod
        
print((dp[-1][0][3] + dp[-1][1][3]) % mod)