LiDAR sensors are super expensive, and I had absolutely zero budget for this.
I did have a basic HC-SR04 ultrasonic sensor lying around from an old project.
Usually, you just use these to stop a robot from crashing into a wall,
but I realized if I tracked its motion, I could generate full 3D spatial data.

I manually moved the sensor over my desk setup in a 'lawnmower path'
(sweeping in a straight line, shifting over a bit, and sweeping back) and logged the distances.
I fed that raw data into a Python script and visualized it using Matplotlib.
The final 3D map has some noise spikes because my hands aren't perfectly steady, but the proof of concept completely works.
The next iteration will use servo motors to automate the sweeps for a perfectly clean scan.
____________________________________________________________________________________

Procedure
---------
Nothing much for the connections
just connect the sensor with the esp32 accordingly
and upload the .ino code into the esp through the arduino IDE
once uploaded, it immediatly starts recording values, so keep it ready, or
get ready with your sensor, then hit the reset button, so uk thats when it starts
now move you hand linearly to the right, shift 5cm towards you,
wait for the command in serial monitor
then move again towards the left linearly, repeat the values.
you can change the number of cycles you want accordingly.

here's a reference pic
[Link to linkedin post](https://www.linkedin.com/posts/rahullj_mechatronics-diy-sensors-ugcPost-7446565730931679232-MQMN?utm_source=share&utm_medium=member_desktop&rcm=ACoAADcxhh4BNDJtPVUYGwt4h750sntFPf0CEDA)
