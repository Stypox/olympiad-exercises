from random import randint
import sys

N = randint(max(int(sys.argv[1])//2, 3), int(sys.argv[1]))

def myprint(*args, **kwargs):
    print(*args, **kwargs)
    print(*args, file=sys.stderr, **kwargs)

if len(sys.argv) > 2:
    Mmax = int(sys.argv[2])
    M = randint(1, max(min(N*(N-1)//2-1, Mmax), 1))
else:
    M = randint(1, N*(N-1)//2-1)

if len(sys.argv) > 3:
    Wmax = int(sys.argv[3])
else:
    Wmax = None

X = randint(1, N)
while True:
    Y = randint(1, N)
    if Y != X:
        break

myprint(N, M, X, Y)
seenedges = set()
for i in range(M):
    while True:
        a = randint(1, N)
        b = randint(1, N)
        if a != b and a*(N+1)+b not in seenedges:
            if ((a == X and b == Y) or (a == Y and b == X)):
                continue
            seenedges.add(a*(N+1)+b)
            seenedges.add(b*(N+1)+a)

            if Wmax is None:
                myprint(a, b)
            else:
                myprint(a, b, randint(1, Wmax))
            break

ours = randint(2,max(N-1,2))
myprint(ours)
myprint(X,Y,end="",flush=True)
seennodes = set([X,Y])
for i in range(ours-2):
    while True:
        a = randint(1,N)
        if a not in seennodes:
            seennodes.add(a)
            myprint("",a,end="")
            break
myprint()