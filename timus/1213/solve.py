s = input()

nodes = set()
nodes.add(s)

while True:
    s = input()
    if s == '#':
        break
    v1, v2 = s.split('-')
    nodes.add(v1)
    nodes.add(v2)
        
print(len(nodes) - 1)