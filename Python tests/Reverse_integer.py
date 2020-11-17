#Given a 32-bit signed integer, reverse digits of an integer.

#Assume we are dealing with an environment that could only store integers within the 32-bit
#signed integer range: [−2**31,  2**31 − 1]. For the purpose of this problem,
#assume that your function returns 0 when the reversed integer overflows.

a = 423456112
b = 0
count = 0

print("\na: ",a,", type of a: ",type(a))

digits = [int(d) for d in str(a)]  #creating a list of of the digits of a
print("\ndigits lenght: ",len(digits), ", digits  type: ",type(digits),"\n")

for i in digits:

    factor = 10**count
    b = b + ( digits[count] * (10**count) )
    count=count+1
    #print("count: " ,count)


print("b: ",b,", type of b: ",type(b))

