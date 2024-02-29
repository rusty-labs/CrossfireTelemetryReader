# Crossfire/ELRS Telemetry Reader
The project reads Crossfire/ELRS telemetry directly from a Remote Controller via a USB data cable. 

This setup is ideal for an antenna tracker, as it only requires a single board with USB host capabilities to control servos. This board could be a PC, Raspberry Pi, or ESP32-S3.

## Initial Setup
Connect your Radio Controller to PC with a USB data cable

> In EdgeTX
>> Select USB Serial (VCP)
>> 
>> Select Hardware->Serial Port->USB-VCP Telem Mirror

> For Win64
>> Navigate to Windows->Device Manager->COM (Ports & LPT) and find which COM port is used by Remote Controller connection
>> 
>> In the code replace COM port to the found
