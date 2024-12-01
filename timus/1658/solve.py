## 1658
import sys

_TEST_ = False

no_solve = 'No solution'

def get_input():
    n = int(sys.stdin.readline())
    a = []
    for i in range(n):
        a.append(map(int, sys.stdin.readline().split()))
    return n, a

def get_tests():
    tests = []
    tests += [[[1, [[1, 10000]]], [no_solve]]]
    tests += [[[1, [[10000, 10000]]], [no_solve]]]
    tests += [[[1, [[10000, 1]]], [no_solve]]]
    tests += [[[1, [[901, 8101]]], [no_solve]]]
    tests += [[[1, [[900, 8100]]], ["9" * 100]]]
    tests += [[[1, [[456, 3456]]], ["2677777777777777777777777788888888888888888888888888888888888"]]]
    tests += [[[3, [[9, 81], [2, 4], [20, 40]]], ["9", "2", "2" * 10]]]
    tests += [[[4, [[9, 81], [12, 9], [6, 10], [7, 9]]], ["9", no_solve, "1122", '111112']]]
    tests += [[[3, [[1, 1], [2, 4], [5, 25]]], ["1", "2", '5']]]
    tests += [[[1, [[808, 6464]]], [no_solve]]]
    tests += [[[4, [[50, 100], [60, 120], [200, 400], [202, 404]]], ["2"*25, "2" * 30,"2"*100, no_solve]]]
    tests += [[[1, [[100, 100]]], ["1" * 100]]]
    tests += [[[1, [[456, 4081]]], [no_solve]]]
    tests += [[[1, [[456, 4080]]], ["888999999999999999999999999999999999999999999999999"]]]
    tests += [[[1, [[456, 2120]]], ["1334444444444444444444444444444444444445555555555555555555555555555555555555555555555555555555555555"]]]

    return tests

if _TEST_:
    import time
    start = time.time()
    print('Start precalc')

max_s1 = 901
max_s2 = 8101
total_border = 6885450
cnt_pred = bytearray(total_border)
dig_pred = bytearray(total_border)


def get_pos(s1: int, s2: int) -> int:
    return int((s1 - 1) * max_s2 + (s2 - 1) - (s1 + 1) * (s1) / 2) + 1

for s1 in range(10):
    s2 = s1 ** 2
    cnt_pred[get_pos(s1, s2)] = 1
    dig_pred[get_pos(s1, s2)] = s1

for s1 in range(1, max_s1):
    for s2 in range(s1, max_s2):
        pos = get_pos(s1, s2)
        if cnt_pred[pos] and cnt_pred[pos] > 0 and cnt_pred[pos] < 100:
            for digit in range(1, 10):
                new_s1 = s1 + digit
                new_s2 = s2 + digit ** 2
                if new_s2 >= max_s2:
                    break
                if new_s1 >= max_s1:
                    break
                new_pos = get_pos(new_s1, new_s2)
                if not cnt_pred[new_pos] or cnt_pred[new_pos] >= cnt_pred[pos] + 1:
                    cnt_pred[new_pos] = cnt_pred[pos] + 1
                    dig_pred[new_pos] = digit
if _TEST_:
    end = time.time()
    print("It took", end - start, "seconds!")

def solve_single(s1: int, s2: int) -> str:
    if s1 >= max_s1 or s2 >= max_s2 or s2 < s1:
        if _TEST_:
            return no_solve
        else:
            sys.stdout.write(no_solve + '\n')
            return
    

    cur_cnt = cnt_pred[get_pos(s1, s2)]
    if not cur_cnt or cur_cnt > 100:
        if _TEST_:
            return no_solve
        else:
            sys.stdout.write(no_solve + '\n')
            return

    ret = [0] * 10
    while s1 != s2:
        pos = get_pos(s1, s2)
        ret[dig_pred[pos]] += 1
        s1 -= dig_pred[pos]
        s2 -= dig_pred[pos] ** 2

    ret[1] += s1

    if _TEST_:
        ans = ""
        for i in range(10):
            ans += str(i) * ret[i]
        
        return ans
    else:       
        for i in range(10):
            sys.stdout.write(str(i) * ret[i])
        sys.stdout.write('\n')
        return
    
def solve(_input):
    _, a = _input
    return [solve_single(s1, s2) for s1, s2 in a]
    
if _TEST_:
    for idx, (test, answer) in enumerate(get_tests()):
        # mem.reset()
        ret = solve(test)
        ret = [s for s in ret]
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
    solve(_input)
        