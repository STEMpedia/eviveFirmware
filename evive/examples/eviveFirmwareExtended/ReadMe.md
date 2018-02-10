evive
This firmware is developed for evive [https://evive.cc] It enables the menu based visual interface for Arduino programs.

-Planned updates:
1) Convert Navkey functions to library
2) Try to implement ADE7912 in library mode from functions (Take care of evive oscilloscope
3) isTouched function to located properly

eviveFirmware 1.1.0
-Major Changes
1) In place of full developer mode with all the libraries, functions of inbuilt functionalities accessible to the user all the time, a library sturcture is implemented.
2) Examples are added in library of evive
3) Exit Menu functionality introduced to start the user to run his/her own code defined in the loop of Arduino sketch.
4) Removed evive.ino from the main destination folder. It has been added in eviveFirmwareExtended folder.
5) Added Plot libraries in beta testing mode

-Minor Changes
1) Updated documentation of many libaries
2) Documented examples

eviveFirmware 1.0.4
1) Updated Motor Library to reduce memory usage by changing variables as per required sizes.
2) Added an Examples library "Examples.h". It includes some examples of using TFT display, presicion sensing using ADE7912 IC, TFTSerial Library etc. But if All examples are selected, than it leads to mulfunctioning of Oscilloscope functioning.
	This is disabled by default, but by enabling a macro "
3) Added init(TAB) function in TFT library to adjust color based on RED TAB or GREEN TAB screen.

eviveFirmware 1.0.3 20170729
1) Added TFTSerial Library to enable the user to print any data on TFT screen anywhere in the firmware or user defined functions.
2) Changed variable "lcd" to "tft"