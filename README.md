# DMX_Ledring_eyes
A Platform IO in visual studio code project to control a ledring via DMX. An Arduino Uno controls two ledrings that represents eyes. 
* The eyes blink with a delay. The blink starts with fading out the upper and lower leds of the ring, moving to the center. At the end all leds are black. Timing of this blink can be controlled in constants. 
* The color of the eyes can be controlled via 3 DMX channels (rgb). The first channel can be configured in the DMXSTART constant. 
The DMX part is based on https://github.com/mathertel/DMXSerial/blob/master/examples/DmxSerialNeoPixels/DmxSerialNeoPixels.ino


![eyes](https://user-images.githubusercontent.com/64959016/232061237-7592270f-a86d-4ec6-a4ca-3f90ca64905e.png)
