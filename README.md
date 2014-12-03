reflow-toaster
==============

A toaster oven repurposed for reflow soldering


I helped a couple friends move out of their apartment. My payment? An old toaster oven. While I do enjoy mmmmm toasted foods, I found myself just using a toaster, regular oven, or cast-iron skillet to cook. The hand-me-down toaster oven was not being used whatsoever. After reading about cheap alternatives for reflow ovens, I decided to repurpose the ol' toaster oven for reflow soldering. I prototyped a heating element control system using an MSP430 launchpad, an ADS1118 thermocouple booster pack, and a solid state relay. Using a PWM output on the microcontroller, the relay is toggled ON/OFF at different frequencies to increase/decrease the rate of temperature change.

I found some solder paste, and implemented a timer-based algorithm to emulate the solder profile. The algorithm adjusted PWM based on an oven_state and an elapsed_time.
- Pre-heat
- Soak
- Reflow
- Cool
- Stop (sound alarm)

Solder profile graph.

Demo results are TBD.

main.c is located in reflow-toaster\sbac121a\430BOOST-ADS1118-SFT\ADS1118_LaunchPad_CCS5.3 directory.

