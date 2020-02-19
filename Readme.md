# About

This is a program for the [ESP32](https://circuits4you.com/2018/12/31/esp32-devkit-esp32-wroom-gpio-pinout/) to behave like a Thurstmaster T300 wheel rim.

**Why:** This software will allow for customised maps and macros to automate settings such as setting ERS Mode/Fuel Mix etc.

# Documentation

Thrustmaster Wheelbase cable pinout (PS/2 connector, also known as mini-Din 6pin female):

![PS/2 Female DIN](images/Female_DIN.jpg)

**Imortant:** Thrustmaster base sends 3v3 to the ESP. Do not send power to it. 3v3 logic levels are used.

| PIN # | Wire Colour | Function | Notes                                                       |
| ----- | ----------- | -------- | ----------------------------------------------------------- |
| 1     | Green       | not used |
| 2     | Blue        | Ground   |
| 3     | White       | MISO     | Mmaster in, slave out. Used to send data to the base        |
| 4     | Yellow      | SS       | Slave select/Chip select When low, we can send data to MISO |
| 5     | Red         | CLK      | Clock impulses                                              |
| 6     | Black       | Power    | +3.3                                                        |

<br><br>
ESP -> T300

| ESP Pin | Wire Colour | Function          | Female PS/2 Pin # |
| ------- | ----------- | ----------------- | ----------------- |
| GND     | Blue        | Ground            | 2                 |
| 32      | White       | MISO              | 3                 |
| 34      | Yellow      | Chip/Slave Select | 4                 |
| 35      | Red         | Clock             | 5                 |
| 3v3     | Black       | Ground            | 6                 |

# Button Mappings

Button mappings (we send 8 bytes to wheelbase, the first 3/8 bytes matter, only 15 bits are used for buttons)

## Byte 1

| Bit Index | Default Flag | Notes    |
| --------- | ------------ | -------- |
| 0         | 1            | Constant |
| 1         | 1            | Constant |
| 2         | 0            | Constant |
| 3         | 1            | Constant |
| 4         | 0            | Constant |
| 5         | 0            | Constant |
| 6         | 0            | Constant |
| 7         | 1            | Constant |

## Byte 2

| Bit Index | Default Flag | Name       | Notes                         |
| --------- | ------------ | ---------- | ----------------------------- |
| 8         | 1            | N/A        | Constant                      |
| 9         | 1            | Cross      | Set to zero to "Press" button |
| 10        | 1            | Circle     | Set to zero to "Press" button |
| 11        | 1            | Square     | Set to zero to "Press" button |
| 12        | 1            | Options    | Set to zero to "Press" button |
| 13        | 1            | R1/Gear Up | Set to zero to "Press" button |
| 14        | 1            | Triangle   | Set to zero to "Press" button |
| 15        | 1            | R2         | Set to zero to "Press" button |

## Byte 3

| Bit Index | Default Flag | Name         | Notes                         |
| --------- | ------------ | ------------ | ----------------------------- |
| 16        | 1            | Share        | Constant                      |
| 17        | 1            | PS           | Set to zero to "Press" button |
| 18        | 1            | D-pad Down   | Set to zero to "Press" button |
| 19        | 1            | L1/Gear Down | Set to zero to "Press" button |
| 20        | 1            | D-dad Right  | Set to zero to "Press" button |
| 21        | 1            | D-pad Left   | Set to zero to "Press" button |
| 22        | 1            | D-pad Up     | Set to zero to "Press" button |
| 23        | 1            | L2           | Set to zero to "Press" button |

# Thanks to

Taras I ([Blog](https://rr-m.org/blog/))
