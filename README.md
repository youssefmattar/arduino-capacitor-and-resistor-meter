# arduino-capacitor-and-resistor-meter
arduino code to measure capacitance and resistance

in this code the arduino determines the component is capacitor or resistor and measures it.


theory we can deduce it is a capaitor or resistor from average rate of change of voltage with respect to time

since q = c * v

therefore q varies directly with v. so if voltage changes it is a capacitor.


theory of reading resistance:

<img src="https://github.com/youssefmattar/arduino-capacitor-and-resistor-meter/assets/70612293/2fe6f538-1b6e-4bc9-8c69-dabdcb91330b" width="250" height="250">

since V = I * R

R = Vr / I  --> 1

Vr = 5 - 10000 * I

I = ( 5 - Vr)/10000 --> 2

therefore R = Vr/( (5-Vr) / 10000 ).




The capacitance code was taken from 
https://www.circuitbasics.com/how-to-make-an-arduino-capacitance-meter/
