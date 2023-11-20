import sys

a = sys.stdin.read()
lines = a.splitlines(keepends=False)

N, P, X, Y = lines[0].split(" ")
N, P = int(N), int(P)

edges = []
for line in lines[1:1+P]:
    edges.append(line.split(" "))

M = int(lines[1+P])
ours = lines[1+P+1].split(" ")

for edge in edges:
    e = [*edge]
    if e[0] in ours:
        e[0] = e[0] + "o"
    if e[1] in ours:
        e[1] = e[1] + "o"
    print(*e)