# Notes on working with PRU's

## Resources
* [Ultra simple setup/hello world](http://mythopoeic.org/bbb-pru-minimal/)
* [More in depth setup/example](http://www.element14.com/community/community/designcenter/single-board-computers/next-gen_beaglebone/blog/2013/05/22/bbb--working-with-the-pru-icssprussv2)
* [TI wiki: PRU API](http://processors.wiki.ti.com/index.php/PRU_Linux_Application_Loader_API_Guide)
* [Elinux: info/specs](http://elinux.org/Ti_AM33XX_PRUSSv2)
* Header pinout tables (mode, mux, etc)
    * [P8 table](https://github.com/derekmolloy/boneDeviceTree/blob/master/docs/BeagleboneBlackP8HeaderTable.pdf)
    * [P9 table](https://github.com/derekmolloy/boneDeviceTree/blob/master/docs/BeagleboneBlackP9HeaderTable.pdf)
* [Device Tree Overlay and pin mux info](http://derekmolloy.ie/gpios-on-the-beaglebone-black-using-device-tree-overlays/)

## Setup (see resource links for more info)
* Using Debian 7.5 from beagleboard.org site.
* `apt-get install am335x-pru-package` (should be installed by default)
    * Also `git clone https://github.com/beagleboard/am335x_pru_package.git` for
      `example_apps` folder if wanted.
* Enable PRU
    * **Every boot**: `echo BB-BONE-PRU-01 > /sys/devices/bone_capemgr.9/slots`
    * Persistent alternative: edit `/boot/uboot/dtbs/am335x-boneblack.dtb`.
      Change `status = "disabled";` to `status = "okay";` under `pruss@4a300000`
      line (see element14 link for how-to use `dtc` command).
    * Make sure `lsmod` shows `uio_pruss` is loaded.
* Test that PRU is setup properly
    * [download](http://mythopoeic.org/source-download/pru-helloworld.tar.gz)
    * Remove `pruss/` prefix from include lines in example.c
    * `make`
    * run with `./example`, wait ~5 seconds and it should complete.
* [Overlay
  setup/usage](http://stackoverflow.com/questions/25388487/beagle-bone-black-pru-device-overlay-for-fast-io-does-not-work)
    * Use kilobaser.com link to generate overlay
    * **Every boot**: enable in slot i.e. `echo bspm_P8_12_16 >
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

## Controlling GPIO via memory
* [Reference](http://vabi-robotics.blogspot.com/2013/10/register-access-to-gpios-of-beaglebone.html)
* Base GPIO addresses: `0x44E07000` (GPIO0), `0x4804C000` (GPIO1), `0x481AC000`
  (GPIO2), `0x481AF000` (GPIO3)
* GPIO_OE register controls assignment between input or output. Offset (from
  base address) is `0x134`
    * 1 = Input, 0 = Output
    * Example: Setting 28th bit of `0x4804C134` to 0 makes GPIO1_28 (P9_12) an
      output.
* **Important:** GPIO0, 2, and 3 clocks must be enabled in order to work. Export
  any pin on that bank within Linux to do so.
    * E.G. `echo 65 > /sys/class/gpio/export` for GPIO2.
    * Tip: add that line to `/etc/rc.local`.

## General
* Pins in regular GPIO mode can be controlled at around 25 mhz max, pins set to
  PRU GPI or PRU GPO can be controlled at the full 200 mhz speed of the PRU's.
    * In PRU mode, they are controlled through registers R30 (Output) and R31
      (Input).
    * Each PRU can control 16 input and 15 output pins in fast mode.

## .bashrc Shortcuts
    * `export PINS=/sys/kernel/debug/pinctrl/44e10800.pinmux/pins` to see header
      pin assignments/mode/mux settings.
    * `export SLOTS=/sys/devices/bone_capemgr.?/slots`
