# Hinata
A firmware for MOPS·VIDA PM 2.5 Watchdog.

## WARNING
Currently there are NO DFU methods, DO NOT flash it without a debugger.

## Todo
- [ ] LEDs bluetooth control
- [ ] Power management
- [x] PMS UART bluetooth passthrough
- [ ] RTC
- [ ] Reformat PMS sensors data
- [ ] OTA DFU

## Compile

* Edit `Makefile` and replace `SDK_ROOT` to your SDK installation directory.
* Edit your SDK `components/toolchain/gcc/Makefile.posix` or `Makefile.windows` and set to your the gcc path
* `make`

## Flash
If you use STLINKV2, use `make flash`(OpenOCD is needed).  

If you are not using ST-LINKV2, try the following:
```
openocd { YOUR_DEBUGGER_CONFIG } -c 'set WORKAREASIZE 0' -f target/nrf51.cfg
```


