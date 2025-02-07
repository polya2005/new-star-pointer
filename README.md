# The Star Pointing and Identification Device

This project is the second version of this [first, proof of concept version](https://github.com/polya2005/star-pointer).

## Some background
In the first version's repository, I wrote
> As the name suggests, the device requires these core functionalities:
>
> - Given a choice of star, point the (physical) pointer toward the position of the star in the sky
> - Given the pointer's direction, identify the star it is poining toward
> 
> For the device to be useful, it also needs the way to
>
> - Store the star data (SD Card)
> - Interact with the user (TFT LCD touchscreen)
> - Obtain necessary information for the relevant spherical astronomical calculations (GPS, Magnetometer, and Accelerometer)
> - Rotate the pointer to the desired azimuth and altitude angle (28BYJ-48 stepper motors; will be replaced with a more robust model of stepper motors in the new version)

Then, I listed the hardware used. That brings us to the first updates in this version.

## Changes

### Hardware / electronics
I keep all the choices I made except
- Replacing Arduino Mega with Raspberry Pi Pico,
- Storing the star data in LittleFS instead of a micro SD card,
- Using more robust NEMA17 stepper motors instead of 28BYJ-48 ones (and changing stepper drivers accordingly)
- Removing the IR keyboard in favor of on-screen keyboard, and
- Ordering a professionally made PCB for reliable connections.

### Enclosure
I am also working on a new design to accommodate the new motors and possibly reduce the overall size of the device. As for now, I am not distributing the model files.

### Software
The code is almost a complete rewrite because the original code was poorly structured and because I made some questionable decisions. The new code will be described in the next section. I also switched to PlatformIO.

## Project structure
This project follows the standard PlatformIO project structure. Libraries are to be described below.
