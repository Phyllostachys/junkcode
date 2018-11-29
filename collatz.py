import sys

def collatz(n):
    if n % 2 == 0:
        return n / 2
    else:
        return 3*n+1

if len(sys.argv) <= 1:
    print("No args...")
    exit(-1)

a = []
num = int(sys.argv[1])
a.append(num)
while(collatz(num) != 1):
    num = int(collatz(num))
    a.append(num)

num = int(collatz(num))
a.append(num)
print(a)
