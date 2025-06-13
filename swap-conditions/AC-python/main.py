#!/usr/bin/env pypy3



t = int(input())
for _ in range(t):
      x, y, r = map(int, input().split())
      x -= 1
      y -= 1
      r -= 1
      a = list(map(int, input().split()))
      def judge(s, strict):
         b = [0] * 4
         for i in range(4):
               if i == x:
                  b[i] = a[i] + s * 4
               elif i == y:
                  b[i] = a[i] - s * 2
               else:
                  b[i] = a[i] - s

         rank = sorted(range(4), key=lambda i: (b[i], -i)).index(x)

         return rank == 3 - r if strict else rank >= 3 - r
      ac = 10**18
      wa = -1
      while ac - wa > 1:
         wj = ac + (wa - ac) // 2
         if judge(wj, False):
               ac = wj
         else:
               wa = wj
   
      print(ac if judge(ac, True) else -1)
