from random import randint
from os import system

system("rm tests/in")

datain = "tests/in"
dataout="tests/out{0}"

cmd = f"./tests/{{0}} <{datain} >{dataout}"

pg1 = "nl"

pg2 = "k"

n=randint(1, 25*2)
q=randint(0, 50)

N = n

ls = []
op = []

for i in range(n):
    ls.append(randint(1, 40))

for i in range(q):
    o = randint(1, 2)
    op.append((o, randint(1, n)))
    if o == 2:
        n += 1
    if o == 3:
        n -= 1

with open(datain, "a") as f:
    f.write(f"{N} {q}\n")
    for i in ls:
        f.write(f"{i} ")
    f.write("\n")
    for (a, b) in op:
        f.write(f"{a} {b}\n")

system(cmd.format(pg1))
system(cmd.format(pg2))
