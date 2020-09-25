# Hinata
A firmware for MOPS·VIDA PM 2.5 Watchdog.

# Device
Original device(MOPS·VIDA PM 2.5 Watchdog) information can found in  
https://github.com/NiceLabs/mops-vida-pm-watchdog/tree/master/docs .

## WARNING
Currently there are NO DFU methods, DO NOT flash it without a debugger.

## Todo
- [x] PMS UART bluetooth passthrough
- [x] Reformat PMS sensors data
- [ ] LEDs bluetooth control
- [ ] Device Information service
- [ ] Battery Service
- [ ] Power management
- [ ] RTC

## Known issues
* NO OTA DFU (DUE TO LACK OF SRAM)

## Compile

* Edit `Makefile` and replace `SDK_ROOT` to your SDK installation directory. (SDK Version:12.3.0)
* Edit your SDK `components/toolchain/gcc/Makefile.posix` or `Makefile.windows` and set to your the gcc path
* `make`

## Flash
If you use STLINKV2, use `make flash`(OpenOCD is needed).  

If you are not using ST-LINKV2, try the following:
```
openocd { YOUR_DEBUGGER_CONFIG } -c 'set WORKAREASIZE 0' -f target/nrf51.cfg
```
## Protocol
[protocol-design](doc/protocol-design.md)

