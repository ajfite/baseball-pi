# Baseball-pi

A Baseball scoreboard designed for the Raspberry Pi 3, a work in progress.  Go Mariners.

* [Visual mockup of the hardware components](https://goldman60.github.io/baseball-pi/images/Visual%20Mockup.svg)

* [Progress pictures on imgur](http://imgur.com/a/cskun)

* [Visit my website for project news and information!](https://ajfite.com/)

* This project is licensed under the MIT License, see license.md for more details.

## Hardware
* 20x4 Character Display (based on the HD44780 controller)
* LEDs (for balls, strikes, out, on base)
* Raspberry Pi3 Model B (Mine runs Ubuntu Mate) - Another type of Pi may work but I'm not testing on any other hardware


## Compiling

#####Dependencies:
* curlpp
* libxml++-2.6
* libcurl4-openssl
* cmake (written for 3.5, should work under 3.0 if you modify CMakeLists.txt's required version)
* make
* gcc (with C++ packages)

##### Instructions:

1. Download the source using your preffered method
2. in the source directory

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Execute the new executable

    ```bash
    ./baseball-pi
    ```

##### Alternatively:

Warning: I am not testing this script for general use, it is mostly for my own convenience.
However I have some confidence it will work on other machines as its relatively simple right now.

1. Download the source code

2. Execute the InstallAndRun.sh file in the source code directory

   ```bash
   ./InstallAndRun.sh
   ```
