import math
def g(x):
    if x <= 1:
        return False
    m=int(math.sqrt(x))+1
    for i in range(2, m):
        if x % i == 0:
            return False
    return True

ans = 0
for i in range(1,1000000):
    if g(i):
        ans += i * i
    
print("Flag is cnss:"+str(ans))
