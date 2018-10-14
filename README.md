# GPIO-control-in-Linux

Team Members :
1. Bhavana Santhoshi Siga - 1214945459
2. Sanchari Datta - 1215306118


Files :
Source code   : RGBLed_1.c  ;
Makefile      : Makefile    ;
Report        : report.pdf  ;

Prerequisites:
Linux kernel (preferably linux 2.6.19 and above) GNU (preferably gcc 4.5.0 and above)

Obtaining the mouse event : Using cat /proc/bus/input/devices, we can find the mouse event number which will vary for each host.Please check the mouse event of your machine before running the program.

Galileo Set up : The Boot Image is flashed into an SD card and inserted into the Board. A Static IP address is set to the board and a connection is established between the host machine and Galileo. Then the toolchain SDK is downloaded and extracted into a directory on your host machine.

Connection between host and Galileo : We can either use the shell screen to establish communication between the host machine and the Galileo or use Putty. Find the ip address of the  ethernet connection and the Galileo, which can be set according to us by using the command
"ifconfig  enp0s20f6 192.168.1.5  netmask  255.255.0.0  up"

The SDK is extracted to the directory : "/opt/iot-devkit/1.7.2/sysroots"

The code is edited,compiled and run using GCC compiler using the commands gedit(editing), gcc(compiling), ./a.out(running).

Installing GCC compiler :

"sudo apt-get install gcc" - this would install gcc compiler on hostmachine

For compiling on the board, use the command "export ENV_V=GALILEO" and then type "make". For compiling on gcc, you can use the command "make" only.

The code can be found in RGBLed_1.c wherein the code lines are commented to give a description of the functions used.

After setting up the Galileo Board,copy the code from host machine to the board : "scp RGBLed_1 root@192.168.1.5:/home"

Open the shell terminal and navigate to "home" directory and execute: "./RGBLed_1 50 0 1 2"

This implies 50% duty cycle & 0,1,2 are the arduino shield connectors that various LED Pins are connected to i.e(io0 , io1 , io2).

Range of Duty Cycle : 0-100
Range of IO pin numbers :0-13 

Left Click or Right click on mouse would begin the 7-step sequence from the begining.

gedit RGBLed_1.c -- instruction to access the file contents of RGBLed_1.c.
