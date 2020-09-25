# Protocol Design

## Initial connection information (Bluetootch LE)

Device broadcast name: `hinata`

| Type                     | UUID                                   |
| ------------------------ | -------------------------------------- |
| Nordic UART Service      | `6E400001-B5A3-F393-E0A9-E50E24DCCA9E` |
| RX Characteristic        | `6E400002-B5A3-F393-E0A9-E50E24DCCA9E` |
| TX Characteristic        | `6E400003-B5A3-F393-E0A9-E50E24DCCA9E` |

## Packet layout
> Receive Message

|    Offset | Field        | Block size | Note                          |
| --------: | ------------ | ---------- | ----------------------------- |
|      `00` | Magic Header | 1 byte     | `77`                          |
|      `01` | Message Type | 1 byte     | [Message Type](#message-type) |
|      `02` | Payload      |            |                               |
| Last byte | Checksum     | 2 byte     | `sum all`                     |

Payload size: 6 byte

## Message Type
| Value | Note                                                        |
| ----- | ----------------------------------------------------------- |
| `ee`  | Error Packet                                                |
| `77`  | [Measurement Update Packet](#measurement-update-packet)     |

### Measurement Update Packet
| Offset | Field             | Block size | Note      |
| -----: | ----------------- | ---------- | --------- |
|   `02` | PM <sub>1.0</sub> | 2 byte     | 16 bit BE |
|   `04` | PM <sub>2.5</sub> | 2 byte     | 16 bit BE |
|   `06` | PM <sub>10</sub>  | 2 byte     | 16 bit BE |
