def calc_zero(s):
    cnt = 0
    while s > 0 and s % 10 == 0:
        cnt += 1
        s = s // 10
    return cnt

def formula(n):
    a = [1,1,2,0]
    if (n - 5) % 20 == 0:
        return 2
    return a[n % 4 - 1]


n = int(input())
print(formula(n))

# for n in range(1, 500):
#     s = 1**n + 2**n + 3**n + 4**n
    
#     cnt = calc_zero(s)
#     ans = formula(n)
#     # if ans != cnt:
#     print(n, cnt, ans, ans == cnt)