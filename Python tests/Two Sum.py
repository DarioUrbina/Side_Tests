nums = [3,3]
target = 6
index_1 = 0
index_2 = 0
stop = 0

for i in nums:                  #1
    for j in nums:              #2
        if index_2 != index_1:              #3 (if)
            shoot = i+j
            if shoot == target: #4 (if)
                stop = 1
                break
        index_2=index_2+1
    if stop == 1:
        print(index_1)
        print(index_2)
        break
    index_1=index_1+1
    index_2=0
    
        
        
    




    
