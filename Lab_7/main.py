from aetypes import end

from bcx_gen import getBCHcodes

a = input('Enter your message (in Decemal):')  # ishodnoe soobchenie
d = input('Enter your Constructive distance (in Decemal):')
g = getBCHcodes(d)  # poragdauchiy polinom

gbin = bin(g)[2:]  # binary string
gbin = gbin[::-1]  # inverting

# make massage
sum = 0
for i in gbin:
    if i == '1':
        sum = sum ^ a
    a = a << 1

print ('\nOut Answer: ' + bin(sum)[2:] + '\n')

# Receive message
error = 0b0000  # make some error
a = sum + error

gdel = g
temp = int(len(bin(sum)[2:])) - int(len(gbin))
gdel = gdel << temp

test = int(len(bin(sum)[2:]))
test = pow(2, test - 1)

print ('In Answer:'),
for i in range(int(len(gbin)), int(len(bin(sum)[2:]) + 1)):
    if a < test:
        print("0"),
    else:
        a = a ^ (gdel >> (i - int(len(gbin))))
        print (1),
    test = test >> 1
print ("\nRest: " + str(a))
