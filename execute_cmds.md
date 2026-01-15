## FULL COMPILE LINE

> Kill PuTTy, Compile, Run PuTTy, Upload firmware.bin

taskkill //F //IM putty.exe > /dev/null 2>&1 & pio run && nutty @"tinywide" > /dev/null 2>&1 && pio run -t upload

> Same, remove compile success spam (no color when error)

taskkill //F //IM putty.exe > /dev/null 2>&1 & pio run > /dev/null && nutty @"tinywide" > /dev/null 2>&1 && pio run -t upload > /dev/null

> Compile & Upload firmware.bin

pio run && pio run -t upload




## Compile and Upload
pio run && pio run -t upload


## Open Putty (without interrupting terminal):
start putty -load "profile_name"
start putty @"profile_name"
or
putty -load "profile_name" &
putty @"profile_name" &
or
nutty -load "profile_name"
nutty @"profile_name"


#### Profile names:
- tinywide ( 36x7,  baud: 115200)
- tinytall ( 16x16, baud: 115200)
- tinysq   ( 20x20, baud: 115200)

- bigwide  ( 64x48,  baud: 115200)
- bigtall  (128x32,  baud: 115200)
- bigsq    ( 96x96,  baud: 115200)