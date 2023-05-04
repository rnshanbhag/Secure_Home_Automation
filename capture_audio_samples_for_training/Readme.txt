ELEN E6908: Embedded AI
Project: Smart Home Automation

Authors: 
 - Rahul Shanbhag (rns2166)
 - Srikanth Chandar (sc5132)
 - Vighnesh Gopal (vvg2113)


Folder structure:

  capture_audio_samples_for_training :- Keyword Sample Collection and Training
  |-- capture_audio_samples_for_training.ino
  |     -> This file contains the Arduino code that uses the Arduino Nano 33 BLE Sense' microphone to gather feature data which is then segregated to csv file created for each individual keyword
  |     -> The microphone is used to collect 64 samples of the keyword which are then used to calculate the RMS value. This is done using the Mic class described in Mic.h
  |-- Mic.h
  |     -> Contains the class Mic which includes functions to detect the audio, sample the audio and calculate the RMS values for the keyword features
  |-- Readme.md 
