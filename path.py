#####   Manual  Planning    #####
#####     Module 8-9        #####

#####   Command has 4 value _ _ _ _ 1.Box size  2.IN or OUT  3and4 position of shelf
#####   1.Box size --> Big is 1 ; Small is 0
#####   2.IN or OUT --> IN is 1 ; OUT is 0
#####   3.Shelf --> 11,12,13,14,15,16,21,22,23,24,25,26,27,28

#####   Position of Shelf   #####
#[  11  14  ]   [   21  25  ]
#[  12  15  ]   [   22  26  ]
#[  13  16  ]   [   23  27  ]
#               [   24  28  ]


class Path(object):
    def Path(self, cmd):
        #####   Big box    Start at Set Home    -->     BoxBin   -->   Shelf    -->    Set Home
        if cmd == 1111:         #IN Shelf 11    BigBox
            data = [
                
            ]
        elif cmd == 1112:       #IN Shelf 12    BigBox
            data = [
                
            ]
        elif cmd == 1113:       #IN Shelf 13    BigBox
            data = [
                
            ]
        elif cmd == 1114:       #IN Shelf 14    BigBox
            data = [
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 0
                    {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 1
                    {"cmd": "point", "data": [-26.5, -6.5, -27.0, 0.0, 0.0, 128.0]},  # 2
                    {"cmd": "relay", "data": 1}, #3
                    {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 4
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 5
                    {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 6
                    {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 7
                    {"cmd": "point", "data": [105.0, 28.0, -18.0, 0.0, 0.0, 115.0]},  # 8
                    {"cmd": "point", "data": [100.0, 0.0, 2.0, 0.0, 0.0, 100.0]},  # 9
                    {"cmd": "relay", "data": 0},  # 10
                    {"cmd": "point", "data": [100.0, 30.0, -2.0, 0.0, 0.0, 92.0]},  # 11
                    {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 12
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 13
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]}  # 14
            ]
            return data , 15
        elif cmd == 1115:       #IN Shelf 15    BigBox
            data = [
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 0
                    {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 1
                    {"cmd": "point", "data": [-27.5, -6.5, -27.0, 0.0, 0.0, 128.0]},  # 2
                    {"cmd": "relay", "data": 1},
                    {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 4
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 5
                    {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 6
                    {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 7
                    {"cmd": "point", "data": [105.0, 36.0, -45.0, 0.0, 0.0, 130.0]},  # 8
                    {"cmd": "point", "data": [100.0, 20.0, -40.0, 0.0, 0.0, 130.0]},  # 9
                    {"cmd": "point", "data": [100.0, -15.0, -10.0, 0.0, 0.0, 135.0]},  # 10
                    {"cmd": "relay", "data": 0},  # 11
                    {"cmd": "point", "data": [100.0, -5.0, -15.0, 0.0, 0.0, 125.0]},  # 12
                    {"cmd": "point", "data": [105.0, 36.0, -45.0, 0.0, 0.0, 130.0]},  # 13
                    {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 14
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 15
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]}  # 16
                ]
            return data , 17
        elif cmd == 1116:       #IN Shelf 16    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1121:       #IN Shelf 21    BigBox
            data = [
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 0
                    {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 1
                    {"cmd": "point", "data": [-27.5, -6.5, -27.0, 0.0, 0.0, 128.0]},  # 2
                    {"cmd": "relay", "data": 1},
                    {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 4
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 5
                    {"cmd": "point", "data": [80.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 6
                    {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 7
                    {"cmd": "point", "data": [80.0, 28.0, -10.0, 0.0, 0.0, 105.0]},  # 8
                    {"cmd": "point", "data": [80.0, 20.0, -2.0, 0.0, 0.0, 97.0]},  # 9
                    {"cmd": "point", "data": [80.0, 2.0, 10.0, 0.0, 0.0, 97.0]}, # 10
                    {"cmd": "relay", "data": 0},  # 11
                    {"cmd": "point", "data": [80.0, 2.0, 12.0, 0.0, 0.0, 95.0]},  # 12
                    {"cmd": "point", "data": [80.0, 20.0, 3.0, 0.0, 0.0, 95.0]},  # 13
                    {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 14
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 15
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 16
                ]
            return data , len(data)
        elif cmd == 1122:       #IN Shelf 22    BigBox
            data = [
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 0
                        {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 1
                        {"cmd": "point", "data": [-27.5, -6.5, -27.0, 0.0, 0.0, 128.0]},  # 2
                        {"cmd": "relay", "data": 1},
                        {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 4
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 5
                        {"cmd": "point", "data": [80.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 6
                        {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 7
                        {"cmd": "point", "data": [78.0, 40.0, -40.0, 0.0, 0.0, 120.0]},  #8
                        {"cmd": "point", "data": [80.0, 16.0, -22.0, 0.0, 0.0, 119.0]},  #9
                        {"cmd": "point", "data": [82.0, -1.0, -7.0, 0.0, 0.0, 130.0]}, #10
                        {"cmd": "relay", "data": 0},  # 11
                        {"cmd": "point", "data": [82.0, -1.0, -2.0, 0.0, 0.0, 118.0]},  # 12
                        {"cmd": "point", "data": [80.0, 24.0, -20.0, 0.0, 0.0, 114.0]},  # 13
                        {"cmd": "point", "data": [80.0, 15.0, 40.0, 0.0, 0.0, 120.0]},  # 14
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 15
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 16
                    ]
            return data , len(data)
        elif cmd == 1123:       #IN Shelf 23    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1124:       #IN Shelf 24    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1125:       #IN Shelf 25    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1126:       #IN Shelf 26    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1127:       #IN Shelf 27    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1128:       #IN Shelf 28    BigBox
            data = [
                
            ]
            return data , 15

        #####   Small box    Start at Set Home    -->     BoxBin   -->   Shelf    -->    Set Home
        elif cmd == 111:        #IN Shelf 11    SmallBox
            data = [
                
            ]
            return data , 15        
        elif cmd == 112:        #IN Shelf 12    SmallBox
            data = [
                
            ]
            return data , 15        
        elif cmd == 113:        #IN Shelf 13    SmallBox
            data = [

            ]
            return data , 15        
        elif cmd == 114:        #IN Shelf 14    SmallBox
            data = [
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 0
                        {"cmd": "point", "data": [-23.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 1
                        {"cmd": "point", "data": [-25.0, -7.0, -28.0, 0.0, 0.0, 133.0]},  # 2
                        {"cmd": "relay", "data": 1},

                        {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 4
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 5
                        {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 6
                        {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 7
                        {"cmd": "point", "data": [105.0, 28.0, -18.0, 0.0, 0.0, 95.0]},  # 8
                        {"cmd": "point", "data": [100.0, 0.0, 2.0, 0.0, 0.0, 100.0]},  # 9
                        {"cmd": "relay", "data": 0},  # 10

                        {"cmd": "point", "data": [100.0, 30.0, -2.0, 0.0, 0.0, 92.0]},  # 11
                        {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 12
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 13
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]}  # 14
                    ]
            return data , 15
        elif cmd == 115:        #IN Shelf 15    SmallBox
            data = [
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 0
                    {"cmd": "point", "data": [-23.5, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 1
                    {"cmd": "point", "data": [-26.5, -8.0, -28.0, 0.0, 0.0, 130.0]},  # 2
                    {"cmd": "relay", "data": 1},
                    {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 4
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 5
                    {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 6
                    {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 7
                    {"cmd": "point", "data": [105.0, 36.0, -45.0, 0.0, 0.0, 130.0]},  # 8
                    {"cmd": "point", "data": [100.0, 20.0, -40.0, 0.0, 0.0, 130.0]},  # 9
                    {"cmd": "point", "data": [100.0, -15.0, -10.0, 0.0, 0.0, 135.0]},  # 10
                    {"cmd": "relay", "data": 0},  # 11
                    {"cmd": "point", "data": [100.0, -5.0, -15.0, 0.0, 0.0, 125.0]},  # 12
                    {"cmd": "point", "data": [105.0, 36.0, -45.0, 0.0, 0.0, 130.0]},  # 13
                    {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 14
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 15
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]}  # 16
                ]
            return data , 17
        elif cmd == 116:        #IN Shelf 16    SmallBox
            data = [
                
            ]
            return data , 15        
        elif cmd == 121:        #IN Shelf 21    SmallBox
            data = [
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 0
                    {"cmd": "point", "data": [-24.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 1
                    {"cmd": "point", "data": [-24.0, -7.0, -28.0, 0.0, 0.0, 133.0]},  # 2
                    {"cmd": "relay", "data": 1},  # 3
                    {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 4
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 5
                    {"cmd": "point", "data": [80.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 6
                    {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 7
                    {"cmd": "point", "data": [80.0, 28.0, -10.0, 0.0, 0.0, 95.0]},  # 8
                    {"cmd": "point", "data": [80.0, 20.0, -3.0, 0.0, 0.0, 95.0]},  # 9
                    {"cmd": "point", "data": [80.0, 3.0, 7.0, 0.0, 0.0, 110.0]},  # 10
                    {"cmd": "relay", "data": 0},  # 11
                    {"cmd": "point", "data": [80.0, 10.0, 7.0, 0.0, 0.0, 90.0]},  # 12
                    {"cmd": "point", "data": [80.0, 20.0, -3.0, 0.0, 0.0, 95.0]},  # 13
                    {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 14
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 15
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]}  #16
                ]
            return data , len(data)
        elif cmd == 122:        #IN Shelf 22    SmallBox
            data = [
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 0
                        {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 1
                        {"cmd": "point", "data": [-27.5, -6.5, -27.0, 0.0, 0.0, 128.0]},  # 2
                        {"cmd": "relay", "data": 1},
                        {"cmd": "point", "data": [-25.0, 0.0, -15.0, 0.0, 0.0, 120.0]},  # 4
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 5
                        {"cmd": "point", "data": [80.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 6
                        {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 7
                        {"cmd": "point", "data": [78.0, 40.0, -40.0, 0.0, 0.0, 120.0]},  #8
                        {"cmd": "point", "data": [80.0, 16.0, -22.0, 0.0, 0.0, 119.0]},  #9
                        {"cmd": "point", "data": [82.0, -1.0, -7.0, 0.0, 0.0, 130.0]}, #10
                        {"cmd": "relay", "data": 0},  # 11
                        {"cmd": "point", "data": [82.0, -1.0, -2.0, 0.0, 0.0, 118.0]},  # 12
                        {"cmd": "point", "data": [80.0, 24.0, -20.0, 0.0, 0.0, 114.0]},  # 13
                        {"cmd": "point", "data": [80.0, 15.0, 40.0, 0.0, 0.0, 120.0]},  # 14
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 15
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 16
                    ]
            return data , len(data)
        elif cmd == 123:        #IN Shelf 23    SmallBox
            data = [
                
            ]
            return data , 15        
        elif cmd == 124:        #IN Shelf 24    SmallBox
            data = [
                
            ]
            return data , 15        
        elif cmd == 125:        #IN Shelf 25    SmallBox
            data = [
                
            ]
            return data , 15        
        elif cmd == 126:        #IN Shelf 26    SmallBox
            data = [
                
            ]
            return data , 15        
        elif cmd == 127:        #IN Shelf 27    SmallBox
            data = [
                
            ]
            return data , 15        
        elif cmd == 128:        #IN Shelf 28    SmallBox
            data = [
                
            ]
            return data , 15
        #####   Big box    Start at Set Home    -->     Shelf   -->   BoxKel    -->    Set Home
        elif cmd == 1011:       #OUT Shelf 11    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1012:       #OUT Shelf 12    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1013:       #OUT Shelf 13    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1014:       #OUT Shelf 14    BigBox
            data = [
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 15
                        {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 16
                        {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 17
                        {"cmd": "point", "data": [105.0, 28.0, -15.0, 0.0, 0.0, 115.0]},  # 18
                        {"cmd": "point", "data": [100.0, 15.0, -10.0, 0.0, 0.0, 115.0]},  # 19
                        {"cmd": "point", "data": [100.0, -2.0, 0.0, 0.0, 0.0, 88.0]},  # 20  #keep box from shelf 14
                        {"cmd": "relay", "data": 1},  # 21
                        {"cmd": "point", "data": [100.0, 30.0, -5.0, 0.0, 0.0, 95.0]},  # 22
                        {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 23
                        {"cmd": "point", "data": [-160.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 24
                        {"cmd": "point", "data": [-160.0, -8.0, -22.0, 0.0, 0.0, 135.0]},  # 25
                        {"cmd": "relay", "data": 0},  # 26
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]}  # 27
                    ]
            return data , 13
        elif cmd == 1015:       #OUT Shelf 15    BigBox
            data = [
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 17
                    {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 18
                    {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 19
                    {"cmd": "point", "data": [105.0, 36.0, -45.0, 0.0, 0.0, 130.0]},  # 20
                    {"cmd": "point", "data": [100.0, 20.0, -40.0, 0.0, 0.0, 130.0]},  # 21
                    {"cmd": "point", "data": [100.0, -18.0, -10.0, 0.0, 0.0, 125.0]},  # 22
                    {"cmd": "relay", "data": 1},  # 23
                    {"cmd": "point", "data": [100.0, -5.0, -15.0, 0.0, 0.0, 125.0]},  # 24
                    {"cmd": "point", "data": [105.0, 36.0, -45.0, 0.0, 0.0, 130.0]},  # 25
                    {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 26
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 27
                    {"cmd": "point", "data": [-160.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 28
                    {"cmd": "point", "data": [-160.0, 5.0, -20.0, 0.0, 0.0, 120.0]},  # 29
                    {"cmd": "relay", "data": 0},  # 30
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]}  # 31
                ]
            return data , 15
        elif cmd == 1016:       #OUT Shelf 16    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1021:       #OUT Shelf 21    BigBox
            data = [
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 17
                        {"cmd": "point", "data": [80.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 18
                        {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 19
                        {"cmd": "point", "data": [80.0, 28.0, -10.0, 0.0, 0.0, 95.0]},  # 20
                        {"cmd": "point", "data": [80.0, 18.0, -3.0, 0.0, 0.0, 97.0]},  # 21
                        {"cmd": "point", "data": [80.0, 2.0, 10.0, 0.0, 0.0, 97.0]}, # 22
                        {"cmd": "relay", "data": 1}, # 23
                        {"cmd": "point", "data": [80.0, 18.0, -3.0, 0.0, 0.0, 97.0]},  # 24
                        {"cmd": "point", "data": [80.0, 33.0, -10.0, 0.0, 0.0, 95.0]},  # 25
                        {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 26
                        {"cmd": "point", "data": [-160.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 27
                        {"cmd": "point", "data": [-160.0, 5.0, -20.0, 0.0, 0.0, 120.0]},  # 29
                        {"cmd": "relay", "data": 0},  # 30
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]}  # 31
                    ]
            return data , len(data)
        elif cmd == 1022:       #OUT Shelf 22    BigBox
            data = [
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 17
                        {"cmd": "point", "data": [80.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 18
                        {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 19
                        {"cmd": "point", "data": [78.0, 40.0, -40.0, 0.0, 0.0, 120.0]},  # 20
                        {"cmd": "point", "data": [80.0, 16.0, -22.0, 0.0, 0.0, 119.0]},  # 21
                        {"cmd": "point", "data": [82.0, -1.0, -7.0, 0.0, 0.0, 125.0]},  # 22
                        {"cmd": "point", "data": [82.0, 0.0, -10.0, 0.0, 0.0, 115.0]},  # 23
                        {"cmd": "relay", "data": 1},  # 24
                        {"cmd": "point", "data": [80.0, 45.0, -40.0, 0.0, 0.0, 119.0]},  # 25
                        {"cmd": "point", "data": [80.0, 35.0, 40.0, 0.0, 0.0, 120.0]},  # 26
                        {"cmd": "point", "data": [-160.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 27
                        {"cmd": "point", "data": [-160.0, -8.0, -22.0, 0.0, 0.0, 140.0]},  # 28
                        {"cmd": "relay", "data": 0},  # 29
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 30
                    ]
            return data , len(data)
        elif cmd == 1023:       #OUT Shelf 23    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1024:       #OUT Shelf 24    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1025:       #OUT Shelf 25    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1026:       #OUT Shelf 26    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1027:       #OUT Shelf 27    BigBox
            data = [
                
            ]
            return data , 15
        elif cmd == 1028:       #OUT Shelf 28    BigBox
            data = [
                
            ]
            return data , 15

        #####   Small box    Start at Set Home    -->     Shelf   -->   BoxKel    -->    Set Home
        elif cmd == 11:         #OUT Shelf 11    SmallBox
            data = [
                
            ]
            return data , 15       
        elif cmd == 12:         #OUT Shelf 12    SmallBox
            data = [
                
            ]
            return data , 15       
        elif cmd == 13:         #OUT Shelf 13    SmallBox
            data = [
                
            ]
            return data , 15       
        elif cmd == 14:         #OUT Shelf 14    SmallBox
            data = [
                
            ]
            data = [
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 15
                        {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 16
                        {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 17
                        {"cmd": "point", "data": [105.0, 28.0, -15.0, 0.0, 0.0, 100.0]},  # 18
                        {"cmd": "point", "data": [100.0, 15.0, -10.0, 0.0, 0.0, 100.0]},  # 19
                        {"cmd": "point", "data": [100.0, 2.0, 5.0, 0.0, 0.0, 95.0]},  # 20  #keep box from shelf 14
                        {"cmd": "point", "data": [100.0, -2.0, 1.0, 0.0, 0.0, 97.0]},  # 21
                        {"cmd": "relay", "data": 1},  # 22
                        {"cmd": "point", "data": [100.0, 30.0, -5.0, 0.0, 0.0, 95.0]},  # 23
                        {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 24
                        {"cmd": "point", "data": [-160.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 25
                        {"cmd": "point", "data": [-160.0, -8.0, -22.0, 0.0, 0.0, 135.0]},  # 26
                        {"cmd": "relay", "data": 0},  # 27
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]}  # 28
                    ]
            return data , 14
        elif cmd == 15:         #OUT Shelf 15    SmallBox
            data = [
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 17
                    {"cmd": "point", "data": [100.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 18
                    {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 19
                    {"cmd": "point", "data": [105.0, 36.0, -45.0, 0.0, 0.0, 130.0]},  # 20
                    {"cmd": "point", "data": [100.0, 20.0, -40.0, 0.0, 0.0, 130.0]},  # 21
                    {"cmd": "point", "data": [100.0, -18.0, -13.0, 0.0, 0.0, 125.0]},  # 22
                    {"cmd": "relay", "data": 1},  # 23
                    {"cmd": "point", "data": [100.0, -5.0, -15.0, 0.0, 0.0, 125.0]},  # 24
                    {"cmd": "point", "data": [105.0, 36.0, -45.0, 0.0, 0.0, 130.0]},  # 25
                    {"cmd": "point", "data": [105.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 26
                    {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 27
                    {"cmd": "point", "data": [-160.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 28
                    {"cmd": "point", "data": [-160.0, 5.0, -20.0, 0.0, 0.0, 120.0]},  # 29
                    {"cmd": "relay", "data": 0},  # 30
                    {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]}  # 31
                ]
            return data , 15
        elif cmd == 16:         #OUT Shelf 16    SmallBox
            data = [
                
            ]
            return data , 15       
        elif cmd == 21:         #OUT Shelf 21    SmallBox
            data = [
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 17
                        {"cmd": "point", "data": [80.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 18
                        {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 19
                        {"cmd": "point", "data": [80.0, 28.0, -12.0, 0.0, 0.0, 85.0]},  # 20
                        {"cmd": "point", "data": [80.0, 15.0, 0.0, 0.0, 0.0, 95.0]},  # 21
                        {"cmd": "point", "data": [80.0, 3.0, 7.0, 0.0, 0.0, 95.0]},  # 22
                        {"cmd": "relay", "data": 1}, #23
                        {"cmd": "point", "data": [80.0, 15.0, 0.0, 0.0, 0.0, 95.0]},  # 24
                        {"cmd": "point", "data": [80.0, 28.0, -12.0, 0.0, 0.0, 85.0]},  # 25
                        {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 26
                        {"cmd": "point", "data": [-160.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 27
                        {"cmd": "point", "data": [-160.0, 5.0, -20.0, 0.0, 0.0, 120.0]},  # 28
                        {"cmd": "relay", "data": 0},  # 29
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]}  # 30
                    ]
            return data , len(data)
        elif cmd == 22:         #OUT Shelf 22    SmallBox
            data = [
                        {"cmd": "point", "data": [0.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 17
                        {"cmd": "point", "data": [80.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 18
                        {"cmd": "point", "data": [80.0, 30.0, 10.0, 0.0, 0.0, 120.0]},  # 19
                        {"cmd": "point", "data": [78.0, 40.0, -40.0, 0.0, 0.0, 120.0]},  # 20
                        {"cmd": "point", "data": [80.0, 16.0, -22.0, 0.0, 0.0, 119.0]},  # 21
                        {"cmd": "point", "data": [82.0, -1.0, -7.0, 0.0, 0.0, 117.0]},  # 22
                        {"cmd": "point", "data": [82.0, -2.0, -11.0, 0.0, 0.0, 115.0]},  # 23
                        {"cmd": "relay", "data": 1},
                        {"cmd": "point", "data": [80.0, 45.0, -40.0, 0.0, 0.0, 119.0]},  # 25
                        {"cmd": "point", "data": [80.0, 28.0, 40.0, 0.0, 0.0, 120.0]},  # 26
                        {"cmd": "point", "data": [-160.0, 0.0, 40.0, 0.0, 0.0, 120.0]},  # 27
                        {"cmd": "point", "data": [-160.0, -8.0, -22.0, 0.0, 0.0, 140.0]},  # 28
                        {"cmd": "relay", "data": 0},  # 29
                        {"cmd": "point", "data": [0.0, 0.0, 0.0, 0.0, 0.0, 100.0]},  # 30
                    ]
            return data , len(data)
        elif cmd == 23:         #OUT Shelf 23    SmallBox
            data = [
                
            ]
            return data , 15       
        elif cmd == 24:         #OUT Shelf 24    SmallBox
            data = [
                
            ]
            return data , 15       
        elif cmd == 25:         #OUT Shelf 25    SmallBox
            data = [
                
            ]
            return data , 15       
        elif cmd == 26:         #OUT Shelf 26    SmallBox
            data = [
                
            ]
            return data , 15       
        elif cmd == 27:         #OUT Shelf 27    SmallBox
            data = [
                
            ]
            return data , 15       
        elif cmd == 28:         #OUT Shelf 28    SmallBox
            data = [
                
            ]
            return data , 15