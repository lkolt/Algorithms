## 1769

_TEST_ = False


def get_input():
    return input()

def get_tests():
    tests = [["10123456789", 11]]
    tests += [["1023456789", 11]]
    tests += [["102345678", 9]]
    tests += [["102345678911", 12]]
    tests += [["1", 2]]
    
    return tests
    
def solve(_input):
    s = _input
    max_length = 6
    max_power = 10**(max_length)

    ans = [False] * max_power

    for num_digits in range(1, max_length + 1):
        power = 10**(num_digits - 1)
        # print(f'{power=}')
        num = int(s[:num_digits])
        ans[num] = True
        # print(f'{num=}')
        for digit in s[num_digits:]:
            num = (num % power) * 10 + int(digit)
            ans[num] = True
            # print(num)

    for idx in range(1, max_power):
        if not ans[idx]:
            return idx

    return None
    
if _TEST_:
    for idx, (test, answer) in enumerate(get_tests()):
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