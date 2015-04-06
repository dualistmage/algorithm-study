#!/usr/bin/env python

switches = [
    (0, (0, 1, 2)),
    (1, (0, 2, 14, 15)),
    (2, (3, 7, 9, 11)), 
    (3, (3, 14, 15)),
    (4, (4, 10, 14, 15)),
    (5, (4, 5, 7, 14, 15)),
    (6, (0, 4, 5, 6, 7)),
    (7, (1, 2, 3, 4, 5)),
    (8, (6, 7, 8, 10, 12)),
    (9, (3, 4, 5, 9, 13))
]

""" sort switch by maxClock """
switches = [ (switchNo, clockNoList) for switchNo, clockNoList in sorted(switches, key=lambda switchInfo : len(switchInfo[1]), reverse=True) ]

sampleMaxCount = int(raw_input())

for sampleNo in range(sampleMaxCount):
    #inStr = "12 9 3 12 6 6 9 3 12 9 12 9 12 12 6 6" 
    inStr = raw_input()
    clockStates = [ int(term)/4 for term in inStr.strip().split() ]
    switchList = []
    
    while True:
        """ check complete? """
        if sum(clockStates) == (3*16):
            break

        """ clock eval """
        for swichNo, clockNoList in sorted( switches, key=lambda switchInfo : (sum([ clockStates[clockNo] for clockNo in switchInfo[1]])/float(len(switchInfo[1]))) ):
            """ switch click!!! """
            for clockNo in clockNoList:
                clockStates[clockNo] += 1
                if clockStates[clockNo] == 4:
                    clockStates[clockNo] = 0
            #print '*' * 60
            #print clockStates, swichNo, sum(clockStates)
            switchList.append( swichNo )
            break

    print len(switchList)
