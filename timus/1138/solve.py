## 1138

_TEST_ = False


def get_input():
    n, s = map(int, input().split())

    return n, s

def get_tests():
    tests = []
    tests.append([[10, 2], 5])
    tests.append([[10, 10], 1])
    tests.append([[1, 1], 1])
    tests.append([[4, 2], 2])
    tests.append([[3, 2], 2])
    tests.append([[5, 2], 3])
    tests.append([[6, 2], 4])
    tests.append([[2, 1], 2])
    tests.append([[12, 11], 1])
    tests.append([[12, 10], 2])
    tests.append([[100, 7], 7])
    tests.append([[20, 7], 2])
    tests.append([[10000, 1], 37])
    
    return tests
    

ans = [0] * (10**4 + 1)
max_per = 201

def rec_solve(n: int, s: int) -> int:
    if s == n:
        return 0
    if ans[s] != 0:
        return ans[s]
    max_ans = 0
    for per in range(max_per):
        to: float = s * per / 100
        if to.is_integer() and s < to and to <= n:
            max_ans = max(max_ans, rec_solve(n, int(to)) + 1)
        if to > n:
            break
    ans[s] = max_ans
    # print(s, ans[s])
    return ans[s]

def solve(_input):
    n, s = _input
    return rec_solve(n, s) + 1
    
    
if _TEST_:
    for idx, (test, answer) in enumerate(get_tests()):
        ans = [0] * (10**4 + 1)
        ret = solve(test)
        if ret == answer:
            print(f'TEST {idx} OK')
        else:
            print(f"TEST {idx} failed")
            print(test)
            print(f'SHOULD: {answer}')
            print(f'SOLVE: {ret}')
            break
    
else:
    _input = get_input()
    print(solve(_input))