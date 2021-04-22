# CESFinalProject

# Running this program:
1. First, you'll need to make an account on MTA's Developer Resources site so you can register to use the API. It's free to use, but they require you to sign up and agree to some terms and conditions, after which you can create an API key. Go here to register: https://api.mta.info/#/signup
2. To create an API key, visit this link (while signed into your MTA Developer account): https://api.mta.info/#/AccessKey
3. Copy the API key and make note of it somewhere, because we'll need it in a minute
4. Run pip install underground to install Underground, a set of Python utilities for the MTA API. The API is pretty difficult to work with and returns a LOT more data than we need, so I'm using Underground's command line utilities in shell scripts (which get called from the Python code) to simplify things. 
5. The shell scripts are set up to call my home station. The 'D26' in the shell scripts is the station ID. It's followed by S or N for south or north.  To set this up for your favorite subway station, start by finding the station ID: run underground findstops[YOUR STOP] with your stop name. For 14th street, you'd use "14 st" for your stop. For Parkside Avenue you'd use "parkside av". More info is available here: https://pypi.org/project/underground/. 
6. Once you have the station ID, replace it in each of the four shell scripts
7. Wire up the hardware according to the pins specified in the .ino code.
8. Make sure to install the LiquidCrystal_I2C and Freenove_ESP32_WS2812 libraries in Arduino IDE
9. Once you've done all of this, the code is ready to run!

# Hardware:
1. ESP32 with breadboard 
2. Several MxF cables
3. LCD1602 Screen
4. Neopixel ring
5. 2 push buttons
6. 1 switch
7. Computer/Raspberry Pi/any other device that has wifi and can run python code

# Other materials
1. Box large enough to contain hardware
2. Paper
3. Tape
4. Scissors
5. Pen

To build the enclosure, measure the LCD screen and Neopixel ring, and cut out holes in the box for each. Also cut a hole to align with the buttons and switch so they're still reachable. Dress up the box with a minimalist paper cover or whatever else floats your boat. Place the screen and neopixels in their spots and tape everything securely.

