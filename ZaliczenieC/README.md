# Zaliczenie - C
## Data file reference
`dane.bin` is a binary file
### Header
The header is exactly 4 characters, should look like this:
```
ZalC
```
If it doesn't an error should be thrown as the file is considered to be corrupted
### Student data
**lastName**

30 bytes, null terminated. Example:
```c
Kowalski\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0
```
**firstName**

20 bytes, null terminated. Example:
```c
Jan\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0
```
**id**

4 bytes. Example:
```c
01 00 00 00     // equals 1
00 01 00 00     // equals 256
```

**marks[5]**

5 floats, 4 bytes each, for a total of 20 bytes

[Converter](https://www.h-schmidt.net/FloatConverter/IEEE754.html) - **don't forget to reverse the bytes**:
```c
0x406d70a4      // value from the converter
40 6d 70 a4     // split into byte packets
a4 70 6d 40     // reverse the order
```

Example:
```c
00 00 60 40     // equals 3.500
00 00 40 40     // equals 3.000
00 00 20 40     // equals 2.500
00 00 90 40     // equals 4.500
00 00 a0 40     // equals 5.000
```

**avg**

4 bytes float. Example:
```c
a4 70 6d 40     // equals 3.710
```


## Student
### Definition
The structure directly correlates to abovementioned file reference
```c
typedef struct {
	char	lastName[30];
	char	firstName[20];
	int     id;
	float	marks[5];
	float	avg;
} Student;
```