# Miscellaneous setup notes
* Beaglebone distribution: Debian 7.5
* Build system setup: install scons and gcc-4.7, fix gcc symlinks
    * `apt-get update && apt-get install gcc-4.7 scons`
    * `rm /usr/bin/gcc /usr/bin/g++`
    * `ln -s /usr/bin/gcc-4.7 /usr/bin/gcc`
    * `ln -s /usr/bin/g++-4.7 /usr/bin/g++`
