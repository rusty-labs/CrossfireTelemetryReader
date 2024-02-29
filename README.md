# Crossfire/ELRS Telemetry Reader
Basic project to read Crossfire/ELRS telemetry from serial data

Connect your Radio Controller to PC with a USB data cable

> In EdgeTX
>> Select USB Serial (VCP)
>> 
>> Select Hardware->Serial Port->USB-VCP Telem Mirror

> For Win64
>> Navigate to Windows->Device Manager->COM (Ports & LPT) and find which COM port is used by Remote Controller connection
>> 
>> In the code replace COM port to the found
