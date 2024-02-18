# One Left Game


## Protocols

### To Start Game

Read 255 Bytes to have name.

### After Game Startup
Read 1° Byte as Command Type:

If CommandType 

1: CHOICE_ONE
```
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     From_X    |    From_Y     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|      To_X     |     To_Y      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

2: CHAT
```
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|              LEN              |   ...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```
So the next LEN bytes will be plain ASCII text.

4: OPTIONS

```
0 1 2 3 4 5 6 7 8
+-+-+-+-+-+-+-+-+
|      OPT      |
+-+-+-+-+-+-+-+-+
```

And OPTIONS as:

1: 


