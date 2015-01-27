# Notes on working with PRU's

## Setup (see resource links for more info)
* Using Debian 7.5 from beagleboard.org site, install `am335x-pru-package`.
* Enable PRU
    * **Every boot**: `echo bspm_pru > /sys/devices/bone_capemgr.?/slots`
    * Persistent alternative: edit `/boot/uboot/dtbs/am335x-boneblack.dtb`.
      Change `status = "disabled";` to `status = "okay";` under `pruss@4a300000`
      line (see element14 link for how-to use `dtc` command).
    * Verify: `lsmod` should show `uio_pruss` is loaded.
* Test that PRU is setup properly
    * [download](http://mythopoeic.org/source-download/pru-helloworld.tar.gz)
    * Remove `pruss/` prefix from include lines in example.c
    * `make`
    * run with `./example`, wait ~5 seconds and it should complete.
* [Overlay
  setup/usage](http://stackoverflow.com/questions/25388487/beagle-bone-black-pru-device-overlay-for-fast-io-does-not-work)
    * Use kilobaser.com link to generate overlay
    * **Every boot**: enable in slot `echo bspm_pru` >
      /sys/devices/bone_capemgr.?/slots`
    * (NOT WORKING) Alternative: add e.g. `cape_enable=capemgr.enable_partno=bspm_P8_12_16` to
      `/boot/uboot/uEnv.txt`
    * Verify exported by checking slots file
* Disable HDMI to free up GPIO pins on P8_27-P8_46 that support fast mode for
  PRU
    * (NOT WORKING) Uncomment
      `cape_disable=capemgr.disable_partno=BB-BONELT-HDMI,BB-BONELT-HDMI` in
      `/boot/uboot/uEnv.txt`
    * Alternative: remove HDMI capes from `am335x-boneblack.dtb` (see above).

## General notes/gotchas/etc
* Pins in regular GPIO mode can be controlled at around 25 mhz max, pins set to
  PRU GPI or PRU GPO can be controlled at the full 200 mhz speed of the PRU's.
    * In PRU mode, they are controlled through registers R30 (Output) and R31
      (Input).
    * Each PRU can control 16 input and 15 output pins in fast mode.
* **IMPORTANT:** Pins P8.43 and P8.44 are used as a boot mode select, so they
  should be left "open" (untouched) until powered up. **This is not mentioned
  by pinout tables, like Derek Molloy's**.
    ** [TI wiki reference](http://processors.wiki.ti.com/index.php/BeagleBone_in_a_Board_Farm#BBB_Boot_Mode_Control)
* `.bashrc` shortcuts for sanity:
    * `export PINS=/sys/kernel/debug/pinctrl/44e10800.pinmux/pins` to see header
      pin assignments/mode/mux settings.
    * `export SLOTS=/sys/devices/bone_capemgr.?/slots` to set/check loaded cape
      slots (overlays).

## Arduino/Beaglebone algorithm/overview
* General concept: Arduino reads all sensors once, pulses a sync pin to indicate
  that sensor values are about to be sent, and then writes those values via
  serial. The BeagleBone PRU waits until the sync pin is pulsed, then listens to
  serial communication from Arduino. Once the PRU receives enough data, it
  copies it over to RAM and notifies the main ARM (Linux) processor. At this
  point, C++ programs can access the most recent sensor values by reading from
  RAM.
* Arduino loop
    1. Read each sensor value into array of uint16_t's.
    2. Ready to send readings via serial, so pulse sync pin high then low.
    3. For each value, write high byte then low byte over serial.
    4. Repeat.
* Beaglebone PRU
    1. Wait until sync pin is set (high) and then cleared (low), indicating that
      Arduino is about to send a chunk of sensor values. This way we know when
      to start listening.
    2. Read byte from Arduino  -- see readByte macro in source code.
    3. Copy temp register used by readByte macro to correct place in
       `DATA_REG_*`.
    4. Repeat steps 2 and 3 until all values are read.
    5. Copy received data to RAM, which will be read by ARM processor.
    6. Notify ARM CPU using interrupt.
    7. Repeat.

## Resources
* [Mythopoeic: simple setup/hello world](http://mythopoeic.org/bbb-pru-minimal/)
* [Element 14: More in depth setup/example](http://www.element14.com/community/community/designcenter/single-board-computers/next-gen_beaglebone/blog/2013/05/22/bbb--working-with-the-pru-icssprussv2)
* [TI wiki: Linux/C++ side of PRU API](http://processors.wiki.ti.com/index.php/PRU_Linux_Application_Loader_API_Guide)
* [Elinux: PRU info/specs](http://elinux.org/Ti_AM33XX_PRUSSv2)
* Derek Molloy's Header pinout tables (mode, mux, etc)
    * [P8 table](https://github.com/derekmolloy/boneDeviceTree/blob/master/docs/BeagleboneBlackP8HeaderTable.pdf)
    * [P9 table](https://github.com/derekmolloy/boneDeviceTree/blob/master/docs/BeagleboneBlackP9HeaderTable.pdf)
* [Device Tree Overlay and pin mux info](http://derekmolloy.ie/gpios-on-the-beaglebone-black-using-device-tree-overlays/)
