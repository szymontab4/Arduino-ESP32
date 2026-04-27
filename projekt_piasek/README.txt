Project: Falling Sand
Goal: To create a simple falling sand animation on an OLED screen that reacts to the physical tilt of the device.

Hardware:

ESP32-C3

SSD1306 OLED Display (128x64)

MPU-6050 Sensor

Key Implementation Details:

Direct Sensor Reads: I bypassed standard MPU-6050 libraries and used direct I2C communication to read raw 16-bit integer data. This fixed initialization issues with clone chips and avoided slow floating-point math.

Dynamic Grid Iteration: To prevent sand grains from "teleporting" across the screen in a single frame, the 2D array scanning direction changes dynamically based on the gravity vector (e.g., scanning bottom-to-top when gravity pulls down).

Smooth Flow Logic: Instead of moving rigidly, the tilt angle is mapped to a probability percentage. A random number generator determines if a grain moves in a given frame, creating a smooth pouring effect like in a real hourglass.

Optimized Rendering: The physics simulation runs on a smaller 64x32 boolean grid to save memory and CPU cycles. It is then scaled up by drawing 2x2 pixel blocks on the 128x64 physical display.
