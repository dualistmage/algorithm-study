#!/usr/bin/env python

switches = ( 
    (0, 1, 2),
    (0, 2, 14, 15),
    (3, 7, 9, 11), 
    (3, 14, 15),
    (4, 10, 14, 15),
    (4, 5, 7, 14, 15),
    (0, 4, 5, 6, 7),
    (1, 2, 3, 4, 5),
    (6, 7, 8, 10, 12),
    (3, 4, 5, 9, 13)
)

clockToSwitch = {}
for switchNo in range(len(switches)):
    for clockNo in switches[switchNo]:
        if clockToSwitch.has_key(clockNo) == False:
            clockToSwitch[clockNo] = set()
        clockToSwitch[clockNo].add( switchNo )

sample_count = int(raw_input())

for sampleNo in range(sample_count):
    #inStr = "12 9 3 12 6 6 9 3 12 9 12 9 12 12 6 6" 
    inStr = raw_input()
    inputArray = [ int(term)/4 for term in inStr.split() ]
    switchList = []

    switchToClock = {}
    for clockNo in range(len(inputArray)):
        for switchNo in clockToSwitch[clockNo]:
            if switchToClock.has_key(switchNo) == False:
                switchToClock[switchNo] = set()
            switchToClock[switchNo].add(clockNo)

    while True:
        """ check complete? """
        if sum(inputArray) == 48:
            break

        switchClockPosList = [ (switchNo, switchToClock[switchNo]) for switchNo in sorted( switchToClock, key=lambda x : len(switchToClock[x]), reverse=True ) ]
        switchClockInfoList = [ (switchNo, [(clockNo, inputArray[clockNo]) for clockNo in clockPosList]) for switchNo, clockPosList in switchClockPosList ]

        #print '#' * 80
        #for swichNo, clockInfoList in switchClockInfoList:
        #    print swichNo, clockInfoList

        """ clock eval """
        for swichNo, clockInfoList in sorted( switchClockInfoList, key=lambda x : (sum([ clockInfo for clockNo, clockInfo in x[1]])/float(len(x[1]))) ):
            """ clock!!! """
            for clockNo, clockInfo in clockInfoList:
                inputArray[clockNo] = clockInfo+1
                if inputArray[clockNo] == 4:
                    inputArray[clockNo] = 0
            #print '*' * 80
            #print inputArray, sum(inputArray), swichNo
            switchList.append( swichNo )
            break

    #print '#' * 80
    #print inputArray
    #print switchList, len(switchList)
    print len(switchList)
