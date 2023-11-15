# GPROF
&emsp;&emsp;GPROF is a code profiler. There are three steps to use GPROF to profile code:

1. Compile: ```gcc -Og -pg write_read.c -o test```
2. Excute: ```./test``
3. Profile: ```gprof test```

&emsp;&emsp;Excution will generate a `gmon.out` file, then we use `gprof` to analysis it.

&emsp;&emsp;It generates a report, there is the main part:
```
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
 79.54      8.59     8.59    10000   859.00   859.00  cumsum1
 20.46     10.80     2.21    10000   221.00   221.00  cumsum2

...

granularity: each sample hit covers 4 byte(s) for 0.09% of 10.80 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.00   10.80                 main [1]
                8.59    0.00   10000/10000       cumsum1 [2]
                2.21    0.00   10000/10000       cumsum2 [3]
-----------------------------------------------
                8.59    0.00   10000/10000       main [1]
[2]     79.5    8.59    0.00   10000         cumsum1 [2]
-----------------------------------------------
                2.21    0.00   10000/10000       main [1]
[3]     20.5    2.21    0.00   10000         cumsum2 [3]
-----------------------------------------------

```