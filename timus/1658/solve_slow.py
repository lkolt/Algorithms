## 1658
import sys

_TEST_ = True

no_solve = 'No solution'

def get_input():
    n = int(sys.stdin.readline())
    a = []
    for i in range(n):
        a.append(map(int, sys.stdin.readline().split()))
    return n, a

def get_tests():
    tests = [[[3, [[9, 81], [2, 4], [20, 40]]], ["9", "2", "2" * 10]]]
    tests += [[[4, [[9, 81], [12, 9], [6, 10], [7, 9]]], ["9", no_solve, "1122", '111112']]]
    tests += [[[3, [[1, 1], [2, 4], [5, 25]]], ["1", "2", '5']]]
    tests += [[[1, [[808, 6464]]], [no_solve]]]
    tests += [[[4, [[50, 100], [60, 120], [200, 400], [202, 404]]], ["2"*25, "2" * 30,"2"*100, no_solve]]]
    return tests


class SingleAnswer:

    def __init__(self):
        self.res = [0] * 10
        self.cnt = 0

    def add(self, digit, num=1):
        self.cnt += num
        self.res[digit] += num

    def less(self, another):
        if self.cnt < 0:
            return False # failed
        if another.cnt < 0:
            return True
        if self.cnt < another.cnt:
            return True
        for i in range(10):
            if self.res[i] < another.res[i]:
                return True
            elif self.res[i] > another.res[i]:
                return False
        return False
    
    def copy(self, another):
        self.cnt = another.cnt
        for i in range(10):
            self.res[i] = another.res[i]

    def print(self):
        if self.cnt < 0:
            return no_solve
        ans = ""
        for i in range(10):
            ans += str(i) * self.res[i]

        if ans == "":
            return "zero"
        return ans

class Mem:
    def __init__(self):
        self.reset()

    def reset(self):
        self.ans = {}
        self.max_n = 901
        self.max_m = 8101

    def get(self, s1, s2):
        num = s1 * self.max_m + s2
        if num not in self.ans:
            self.ans[num] = SingleAnswer()
        return self.ans[num]

no_res = SingleAnswer()
no_res.cnt = -1
def rec_solve(s1: int, s2: int, depth=0):
    # print(f'{s1=}, {s2=}, {depth=}')
    # if depth > 102:
    #     # print(f'FOUND for {s1=} {s2=} depth > 100 {no_res.print()}')
    #     return no_res
    if s2 < s1:
        # print(f'FOUND for {s1=} {s2=} s2 < s1 {no_res.print()}')
        return no_res
    
    if s1 > 900 or s2 > 8100 or s1 < 0:
        # print(f'FOUND for {s1=} {s2=} big {no_res.print()}')
        return no_res
    
    cur = mem.get(s1, s2)
    
    if cur.cnt != 0:
        # print(f'FOUND for {s1=} {s2=} exist {cur.print()}')
        return cur
    
    if s1 == s2:
        if s1 + depth > 99:
            # print(f'FOUND for {s1=} {s2=} {no_res.print()}')
            return no_res
        cur.add(1, s1)
        # print(f'FOUND for {s1=} {s2=} {cur.print()}')
        return cur
    
    default = no_res
    add = 0
    for dec in range(2, 10):
        new_res = rec_solve(s1 - dec, s2 - dec**2, depth + 1)
        if new_res.cnt > 99:
            continue
        if new_res.less(default):
            default = new_res
            add = dec
    if default.cnt < 0:
        cur.cnt = -1
        # print(f'FOUND for {s1=} {s2=} {cur.print()}')
        return no_res

    cur.copy(default)
    cur.add(add)
    # print(f'FOUND for {s1=} {s2=} {cur.print()}')
        
    return cur
    
def solve(_input):
    _, a = _input
    return [rec_solve(s1, s2) for s1, s2 in a]
    

mem = Mem()

if _TEST_:
    for idx, (test, answer) in enumerate(get_tests()):
        # mem.reset()
        ret = solve(test)
        ret = [s.print() for s in ret]
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
    res = solve(_input)
    for ans in res:
        sys.stdout.write(ans + '\n')