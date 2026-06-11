# ESP 32 GPS route tracker

This program utilises an ESP-32, a 0.96" OLED screen and a NEO-6M GPS module. To track a users "route" on a walk, trail or hike. It does this by storing the users GPS coordinates every 15, 30, 45 or 60 seconds.
It has been created with ESP-IDF and takes power efficiency into consideration and will include sleep modes when possible.

OOP has been used when creating this, as it was something I wanted to learn a bit more about especially on embedded systems, this goes hand-in-hand with ESP-IDF's modular file structure where features can be split
into components.

## What I want for this in the future
- Sleep efficiency
- Displaying the route in 3D space on an external webpage
