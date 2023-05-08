# Secure Home Automation

This project aims to to implement a smart and secure home automation system using the Arduino Nano 33 BLE Sense. The idea is to use a keyword classification machine learning model to detect certain keywords which prompt the system to perform certain actions. The whole system is secured using a proximity based client-server BLE architecture. 


# Overview

The system contains 3 primary parts:

 - Keyword Detection Model
 - Embedded System Component to Perform Actions
 - BLE based Authentication Feature

## Keyword Detection Model

We have tried two approaches for the keyword audio detection:

First is through an artificial neural network - 
> It first starts by resizing the sample to 32 by 32. Then it is normalized, follows 2 2D convolutions, a 2D maxpooling and dropout. It is then flattened, and run through a Dense ReLu convolution, dropped out and then convoluted one last time. 

The second is a traditional classifier - 
> The methods tried were SVM, Random Forest and Decision Trees. We found the Random Forest implementation to give the best results while being lightweight.

The keywords we trained our model to detect were:

- Light: To create a pattern of colors with the LEDs on the Arduino Nano 33 BLE Sense and flash the pattern.
- Sound: To ring a buzzer connected to the Arduino Nano 33 BLE Sense.
- Fan: To switch on the Servo Motor connected to the Arduino Nano 33 BLE Sense

## Embedded System Component to Perform Actions
In order to capture and analyze sound in real time, we used the omnidirectional digital microphone (MP34DT05) on the Arduino Nano 33 BLE Sense. The PDM library is used to implement this functionality.
> The microphone is used to capture samples for the training data to build the dataset as well as to detect the keyword

The peripherals are connected to the Arduino using a breadboard and jumper cables. The peripherals used are:

- SG90 9G Micro Servo Motor
- PT-1306T Piezo Buzzer
- On-Board Arduino LEDs


## BLE based Authentication Feature


The Arduino Nano 33 BLE Sense has a powerful 2.4 GHz Bluetooth® 5 Low Energy module from u-blox, with an internal antenna. We use two Arduino devices, one acting as the central server and one acting as a peripheral to implement the proximity based security feature.

> The peripheral device contains the model file. The microphone of the peripheral can be accessed only the BLE authentication between the peripheral and central server has been completed. For this example, we have hardcoded the central server to accept the connection request for this specific peripheral. This can be expanded further in the future to control more devices.

# File Structure

The files and folders have been structured in the following way:
- [ble_central_security](https://github.com/rnshanbhag/Secure_Home_Automation/tree/main/ble_central_security "ble_central_security")
> This folder contains the .ino script to accept BLE connection requests and authenticate the peripheral device. The Readme.txt of the folder explains further.
- [ble_peripheral_classify_audio](https://github.com/rnshanbhag/Secure_Home_Automation/tree/main/ble_peripheral_classify_audio "ble_peripheral_classify_audio")
> This folder contains the header file with the microphone related functions, the .h Random Forest Classifier model file and the .ino script to complete BLE authentication, accept voice commands and classify the keyword to perform an action.
- [capture_audio_samples_for_training](https://github.com/rnshanbhag/Secure_Home_Automation/tree/main/capture_audio_samples_for_training "capture_audio_samples_for_training")
> This folder contains the header file with the microphone related functions and the .ino script to collect audio samples and build the training dataset. We collected up to 100 samples of every keyword to build our data set.
- [EmbeddedAI_ML_classifiers.ipynb](https://github.com/rnshanbhag/Secure_Home_Automation/blob/main/EmbeddedAI_ML_classifiers.ipynb "EmbeddedAI_ML_classifiers.ipynb")
> This is our implementation of the traditional ML classifiers for the keywords.
- [EmbeddedAI_NeuralNetworkClassifier.ipynb](https://github.com/rnshanbhag/Secure_Home_Automation/blob/main/EmbeddedAI_NeuralNetworkClassifier.ipynb "EmbeddedAI_NeuralNetworkClassifier.ipynb")
> This is our implementation of the artificial neural network for the keyword detection.
- [README.md](https://github.com/rnshanbhag/Secure_Home_Automation/blob/main/README.md "README.md")

## Authors
- Rahul Shanbhag (rns2166)
- Srikanth Chandar (sc5132)
- Vignesh Gopal (vvg2113)
