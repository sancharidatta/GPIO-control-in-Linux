#define _GNU_SOURCE 
#include<stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/time.h>
#include <linux/input.h>
#include <math.h>
#include <semaphore.h>
#define MOUSEFILE "/dev/input/event2"   			//Set the mouse event by checking in cat /proc/bus/input/devices

#define step_duration 0.5					//Set the step duration

#define cycle 20						//Set the cycle duration

int rled,gled,bled;

int temp=1;							
int Red,Green,Blue,i;
char buff[256];
int numcycles,on_time,off_time;					

				
int gpio_export(int gpionum)					//Function for exporting gpio pins
{
FILE *fd;
fd=fopen("/sys/class/gpio/export","w");
if(fd == NULL)
{
printf("Error in exporting");
}
fprintf(fd,"%d",gpionum);
fclose(fd);
return 0;
}

int gpio_unexport(int gpionum)					//Function for unexporting the exported pins
{
FILE *fd;
fd=fopen("/sys/class/gpio/unexport","w");
if(fd == NULL)
{
printf("Error in unexporting");
}
fprintf(fd,"%d",gpionum);
fclose(fd);
return 0;
}

void gpio_direc(int gpionum)					//Function for setting the direction of gpio pins to output
{
int fd;
char buf[256];
snprintf(buf,sizeof(buf),"/sys/class/gpio/gpio%d/direction",gpionum);
fd=open(buf,O_WRONLY);
if(fd==-1)
{
//printf("Error in setting the direction");
}
write(fd,"out",3);
close(fd);


}

int gpio_setvalue(int gpionum, int value)			//Function to set the value of gpio pins
{
int fd;

char buf[256];

sprintf(buf,"/sys/class/gpio/gpio%d/direction",gpionum);


fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("Setting value failed");
		return fd;
	}

	if (value)
		write(fd, "1", 1);
	else
		write(fd, "0", 1);

	close(fd);
return 0;

}
int gpio_open(int gpionum)					//Function to open the gpio pins directory
{
int fd;
char buf[256];

sprintf(buf,"/sys/class/gpio/gpio%d/value",gpionum);


fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("Opening failed");
	}
	return fd;
}


int muxing_function(int gpionum, int value)
{
	gpio_export(gpionum);
	gpio_direc(gpionum);
	gpio_setvalue(gpionum, value);

return 0;

}

int gpio_mux(int io)					//Function for muxing of gpio pins
{
	int gpio;
	
                if (io==0)
                        {
                          muxing_function(32,0);
			  gpio=11;

			  }

		if (io==1) 
                     {
                          muxing_function(28,0);muxing_function(45,0);
			  gpio=12;
			  

			 }
		if (io==2)
                        {
                          muxing_function(77,0);muxing_function(34,0);
			  gpio=13;

			  }
		if (io==3)
                       {
                          muxing_function(16,0);muxing_function(76,0);muxing_function(64,0);
			  gpio=14;

			 }
		if (io==4)
                      { 
                          muxing_function(36,0);
			  gpio=6;

			 }
		if (io==5)
                     {
                          muxing_function(18,0);muxing_function(66,0);
			  gpio=0;

			 }
		if (io==6)
                      {
                          muxing_function(20,0);muxing_function(68,0);
			  gpio=1;

			 }
		if (io==7)
                      {
			  gpio=38;

			 }
		if (io==8) {
			  gpio=40;

			 }
		if (io==9)
                   {
                          muxing_function(22,0);muxing_function(70,0);
			  gpio=4;

			 }
		if (io==10)
                    {
                          muxing_function(26,0);muxing_function(74,0);
			  gpio=10;

			 }
		if (io==11)
                   {
                          muxing_function(24,0);muxing_function(44,0);muxing_function(72,0);
			  gpio=5;

			 }
		if (io==12)
                     {
                          muxing_function(42,0);
			  gpio=15;

			 }
		if (io==13) 
                      {
                          muxing_function(46,0);muxing_function(30,0);
			  gpio=7;

			 }
		
return gpio;
                 
}


void *mouse_click(void *arg)				//Function to detect the mouse events
{
     //printf("Here we are");
     int fd;
     struct input_event ie;
     fd=open(MOUSEFILE,O_RDONLY);
     
     while(1)
	read(fd,&ie,sizeof(struct input_event));
        {
	    if(ie.value == 0 && ie.code == 272)          // value =0 means key release
            {
                printf("left mouse click\n");
		temp=0;					 //changing the value of temp to begin the sequence again
		printf("\nvalue of temp=%d\n",temp);               
            }

	    else if(ie.value == 0 && ie.code == 273)
            {
                printf("right mouse click\n");
                temp=0;					//changing the value of temp to begin the sequence again
                printf("\nvalue of temp=%d\n",temp);
		
            }

}return 0;
}


void sequence()						//Function for 7-step sequence
{
printf("Inside the sequence");
while(1)
	{
temp=1;
printf("\nstarting the sequence\n");

	//Red//
	for(i=0;i<numcycles;i++)
	{
	write(Red,"1",1);
	usleep(on_time * 1000);
	write(Red,"0",1);
	usleep(off_time * 1000);
		}
printf("\nInside first step\n");

       if(temp!=1){			//Checking the value of temp and starting the sequence from the beginning if temp is not equal to 1
	sequence()};
	//Green//
	for(i=0;i<numcycles;i++)
	{
	write(Green,"1",1);
	usleep(on_time * 1000);
	write(Green,"0",1);
	usleep(off_time * 1000);
	}
printf("\nInside 2nd step\n");
      if(temp!=1){
	sequence();}
	//Blue//
	for(i=0;i<numcycles;i++)
	{
	write(Blue,"1",1);
	usleep(on_time * 1000);
	write(Blue,"0",1);
	usleep(off_time * 1000);
	}
printf("\nInside 3rd step\n");
 if(temp!=1){
	sequence();}
	//Red & Green//
	for(i=0;i<numcycles;i++)
	{
	write(Red,"1",1);
	write(Green,"1",1);
	usleep(on_time * 1000);
	write(Red,"0",1);
	write(Green,"0",1);
	usleep(off_time * 1000);
	}
printf("\nInside 4th step\n");

 if(temp!=1){
	sequence();}
	//Red & Blue//
	for(i=0;i<numcycles;i++)
	{
	write(Red,"1",1);
	write(Blue,"1",1);
	usleep(on_time * 1000);
	write(Red,"0",1);
	write(Blue,"0",1);
	usleep(off_time * 1000);
	}
printf("\nInside 5th step\n");

 if(temp!=1){
	sequence();}
	//Green & Blue//
	for(i=0;i<numcycles;i++)
	{
	write(Green,"1",1);
	write(Blue,"1",1);
	usleep(on_time * 1000);
	write(Green,"0",1);
	write(Blue,"0",1);
	usleep(off_time * 1000);
	}
printf("\nInside 6th step\n");

 if(temp!=1){
	sequence();}
	//Red,Green & Blue//
	for(i=0;i<numcycles;i++)
	{
	write(Red,"1",1);
	write(Green,"1",1);
	write(Blue,"1",1);
	usleep(on_time * 1000);
	write(Red,"0",1);
	write(Green,"0",1);
	write(Blue,"0",1);
	usleep(off_time * 1000);
	}
printf("\nInside 7th step\n");

 if(temp!=1){
	sequence();}
	}

}
//Function for exporting and setting the direction of the respective gpio pin obtained from muxing the I/O pins//
void ios(int iop1,int iop2,int iop3)
{
rled=gpio_mux(iop1);
gled=gpio_mux(iop2);
bled=gpio_mux(iop3);

gpio_export(rled);
gpio_export(gled);
gpio_export(bled);

gpio_direc(rled);
gpio_direc(gled);
gpio_direc(bled);
}


//Main function//
int main(int argc,char *argv[])
{

int dc,io1,io2,io3;					//Obtain the input values through command line arguments
printf("Enter the input values\n");
dc=atoi(argv[1]);
io1=atoi(argv[2]);
io2=atoi(argv[3]);
io3=atoi(argv[4]);

printf("Input values are %d,%d,%d,%d\n",dc,io1,io2,io3);

if((dc>100)||(dc<0))					//Print error message if dutycycle is not entered in appropriate range//
{
printf("Error in duty cycle");
return 0;
}

if((io1<0)||(io1>13)||(io2<0)||(io2>13)||(io3<0)||(io3>13))	//Print error message if I/O pin numbers are not entered in appropriate range//
{
printf("Error in IO pin number");
return 0;
}


numcycles = (step_duration *1000)/cycle;			//Calculation of iterations, on-time and off-time
on_time = (dc/100) * cycle;
off_time =  (100-dc)/100 * cycle;

ios(io1,io2,io3);
//Printing the gpio/value directory filename into a buffer and opening it and pointing it to "Red", "Green", "Blue"
snprintf(buff,sizeof(buff),"/sys/class/gpio/gpio%d/value",rled);  
Red = open(buff,O_RDONLY | O_WRONLY| O_NONBLOCK);
snprintf(buff,sizeof(buff),"/sys/class/gpio/gpio%d/value",gled);
Green = open(buff,O_RDONLY | O_WRONLY| O_NONBLOCK);
snprintf(buff,sizeof(buff),"/sys/class/gpio/gpio%d/value",bled);
Blue = open(buff,O_RDONLY | O_WRONLY| O_NONBLOCK);


pthread_t mouse;					//thread ID for mouse
void *res;
pthread_create(&mouse,NULL,mouse_click,NULL);		//Mouse thread creation
printf("Mouse thread created \n");			


//7-step sequence function called

sequence();


pthread_join(mouse, &res);
}
