#Given a 32-bit signed integer, reverse digits of an integer.

#Assume we are dealing with an environment that could only store integers within the 32-bit
#signed integer range: [−2**31,  2**31 − 1]. For the purpose of this problem,
#assume that your function returns 0 when the reversed integer overflows.

a = 423456112
digits_b=[]
count = 1

print("\na: ",a," a  type: ",type(a))
#int_str =str(a)

digits = [int(d) for d in str(a)]  #creating a list of of the digits of a
print("\ndigits lenght: ",len(digits), "digits  type: ",type(digits),"\n")

length = len(digits)

for i in digits:
    #print("count: ",count)
    print(digits[len(digits)-count])
    digits_b.append(digits[len(digits)-count])
    digits_2 = digits[len(digits)-i] 
    
    factor = 10**count
    #b = +prev + digits[len(digits)-count]* (10**count)
    count=count+1
    #digits_b =

print("\n",digits[0], "type: ", type(digits[0]))
print("\nb: ",digits_b)



#print(digits_2)
#for i in digits:
        

#lenght = len(int_str)

#for i in 

#print(int_str.split(,lenght))


#if int < 2**32:

    



    #for j in nums:              #2
     #   if index_2 != index_1:              #3 (if)
        
    




    
