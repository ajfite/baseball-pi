---
layout: page
title: About
permalink: /About/
---

Baseball-pi is a Baseball scoreboard designed for the Raspberry Pi 3, a work in progress.  Go Mariners.

[Visual mockup of the hardware components](https://goldman60.github.io/baseball-pi/images/Visual%20Mockup.svg)

[Progress pictures on imgur](http://imgur.com/a/cskun)

## Hardware ##

* 20x4 Character Display (based on the HD44780 controller)
* LEDs (for balls, strikes, out, on base)
* Raspberry Pi3 Model B (Mine runs Ubuntu Mate) - Another type of Pi may work but I'm not testing on any other hardware


## Compiling ##

Dependencies:

* curlpp
* libxml++-2.6
* libcurl4-openssl
* cmake (written for 3.5, should work under 3.0 if you modify CMakeLists.txt's required version)
* make
* gcc (with C++ packages)

Instructions:

1. Execute the BuildandInstall.sh script located in the project source directory
