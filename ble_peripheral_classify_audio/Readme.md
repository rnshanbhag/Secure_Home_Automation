# Smart Home Automation
# ELEN E6908: Embedded AI


## Folder structure:

### ble_peripheral_classify_audio :- BLE Peripheral Arduino folder
  - ble_peripheral_classify_audio.ino
  > This file contains the Arduino code that sets up the Arduino Nano 33 BLE Sense (Module 2) to act as a BLE peripheral device. Module 2 acts a the peripheral device and connects to the BLE cnetral server upon proximity to it. The device ID and MAC address are hardcoded into into the device. Module 2 uses the Arduino's microphone to collect 64 samples of the keyword which are then used to calculate the RMS value. This is done using the Mic class described in Mic.h. Based on the features of the samples, the keyword is identified using the Random Forest Classifier in classifier_randomForest.h
  - Mic.h
  > Contains the class Mic which includes functions to detect the audio, sample the audio and calculate the RMS values for the keyword features
  - classifier_randomForest.h
  > Contains the model generated from the Colab file using MicroML
  - Readme.md 

## Authors: 
 - Rahul Shanbhag (rns2166)
 - Srikanth Chandar (sc5132)
 - Vighnesh Gopal (vvg2113)
