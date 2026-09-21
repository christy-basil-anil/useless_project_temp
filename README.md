<img width="1280" height="640" alt="git (1)" src="https://github.com/user-attachments/assets/8920b256-2ba8-4988-b824-5351134eb4bd" />



# Gramophone of jungle

<img  height="640" alt="gramophone" src="gramophone.jpeg" />


## Basic Details
### Team Name: Christy Basil Anil's Team 

### Team Members
- Team Lead: Christy Basil Anil— St.Thomas College, Ranni

  
### Project Description
What if our ancestors skipped the invention of modern technology and went straight to vintage music?
Imagine walking through an ancient jungle and suddenly hearing music coming from a suspiciously advanced wooden box. 

### The Problem (that doesn't exist)
Ancient humans had no Wi-Fi.\
No electricity.\
No Spotify.\
And, most importantly… NO GRAMOPHONE.

For thousands of years, our ancestors were forced to live without listening to music on a giant spinning disc.\
Honestly, unacceptable.

### The Solution (that nobody asked for)
As a responsible descendant with zero respect for historical accuracy, I decided to fix this massive injustice.

I built a gramophone for ancient jungle people.

Because if our ancestors could discover fire, invent tools, and survive wild animals, surely they deserved to sit around a campfire and enjoy some ancient lo-fi beats.

Did they need it? No.\
Did they ask for it? Absolutely not.\
Did I build it anyway? Obviously. 🗿

## Technical Details
### Components Used
- ESP32
- Servo motor
- RFID reader
- RFID card
- Buzzer module
- Cable
- Jumper wire


###  Software used:
- Arduino IDE

## how it work
The Arduino script uses an ESP32 to detect an RFID card inside a leaf which act as the vinyl disc using a RFID reader in the needle arm , read stored musical data from its memory blocks, and play the song through a buzzer while synchronously oscillating a servo motor.

# Code
## Code to store msuic melody in RFID card(vinyl disc)
<a href="vinyl_disc_setup.ino">vinyl_disc_setup.ino</a>

## Pin Connections
| RC522 Module Pin | ESP32 GPIO Pin | 
| :--- | :--- | 
| **VCC** | **3.3V** | 
| **RST** | **GPIO 22** | 
| **GND** | **GND** | 
| **IRQ** | *Unconnected* | 
| **MISO** | **GPIO 19** | 
| **MOSI** | **GPIO 23** | 
| **SCK** | **GPIO 18** |
| **SDA / SS** | **GPIO 5** | 


## full code for the project
<a href="gramophone.ino">gramophone.ino</a>
## Pin Connections

### RFID RC522 Module (SPI)
| RC522 Pin | ESP32 Pin |
|-----------|-----------|
| **SDA (SS)** | GPIO 5 |
| **SCK** | GPIO 18 |
| **MOSI** | GPIO 23 |
| **MISO** | GPIO 19 |
| **RST** | GPIO 22 |
| **GND** | GND |
| **3.3V** | 3.3V |

---

### Servo Motor
| Servo Wire | ESP32 Pin / Power |
|------------|-------------------|
| **Signal (Yellow/Orange)** | GPIO 26 |
| **VCC (Red)** | 5V / VIN |
| **GND (Brown/Black)** | GND |

---

### 3-Pin Passive / Active Buzzer Module
| Buzzer Module Pin | ESP32 Pin / Power |
|-------------------|-------------------|
| **S (Signal)** | GPIO 25 |
| **VCC (+)** | 3.3V / 5V |
| **GND (-)** | GND |
### Project Documentation
For Software:

# Screenshots (Add at least 3)
![Screenshot1](Add screenshot 1 here with proper name)
*Add caption explaining what this shows*

![Screenshot2](Add screenshot 2 here with proper name)
*Add caption explaining what this shows*

![Screenshot3](Add screenshot 3 here with proper name)
*Add caption explaining what this shows*

# Diagrams
![Workflow](Add your workflow/architecture diagram here)
*Add caption explaining your workflow*

For Hardware:

# Schematic & Circuit
![Circuit](Add your circuit diagram here)
*Add caption explaining connections*

![Schematic](Add your schematic diagram here)
*Add caption explaining the schematic*

# Build Photos
![Components](Add photo of your components here)
*List out all components shown*

![Build](Add photos of build process here)
*Explain the build steps*

![Final](Add photo of final product here)
*Explain the final build*

### Project Demo
# Video
[Add your demo video link here]
*Explain what the video demonstrates*

# Additional Demos
[Add any extra demo materials/links]

## Team Contributions
- [Name 1]: [Specific contributions]
- [Name 2]: [Specific contributions]
- [Name 3]: [Specific contributions]

---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0)



