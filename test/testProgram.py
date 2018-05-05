#!/bin/python
import sys, os

tradeStore = {}
fp = open(sys.argv[1])
for line in fp.readlines():
    tokens = line.split(",")
    if tokens[1] not in tradeStore:
        tradeStore[tokens[1]] = [tokens[1],1,int(tokens[2]), int(tokens[3]) * int(tokens[2]),int(tokens[3]), int(tokens[0])]
    else:
        array = tradeStore[tokens[1]]
        if array[1] < (int(tokens[0]) - int (array[5])):
            array[1] = (int(tokens[0]) - int (array[5]))
        array[5] = int(tokens[0])
        
        
        array[2] += int(tokens[2])
        array[3] += (int(tokens[3]) * int(tokens[2]))
        if (array[4] < int(tokens[3])):
            array[4] = int(tokens[3])


for key in sorted(tradeStore.keys()):
    array = tradeStore[key]
    print (array[0] + "," + str(array[1]) + "," + str(array[2]) + "," 
        + str(array[3] / array[2]).split(".")[0] + "," + str(array[4]))
    

