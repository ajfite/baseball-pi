#Baseball-pi

A Baseball scoreboard designed for the Raspberry Pi 3, a work in progress.  Go Mariners.

[Visual mockup of the hardware components](https://goldman60.github.io/baseball-pi/images/Visual%20Mockup.svg)

##Hardware
* 20x4 Character Display (based on the HD44780 controller)
* LEDs (for balls, strikes, out, on base)
* Raspberry Pi3 Model B (Mine runs Ubuntu Mate) - Another type of Pi may work but I'm not testing on any other hardware


##Compiling

Dependencies:
* curlpp
* libxml++-2.6
* libcurl4-openssl
* cmake (written for 3.5, should work under 3.0 if you modify CMakeLists.txt's required version)
* make
* gcc (with C++ packages)

Instructions:

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
