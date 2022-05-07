
#### Research ####

##### Resources

- About input in Linux
    - https://www.kernel.org/doc/Documentation/input/input.txt
- About /dev/input
    - https://thehackerdiary.wordpress.com/2017/04/21/exploring-devinput-1/

#### Input Devices 

In Linux, all input devices are located within the /dev/input directory. Each device is configured to have event handlers that are present within this library. To see which events belong to which device, analyze the by-id or proc/bus/input/devices file.

#### The keyboard

/dev/input/

event2: contains keyboard data
event3-event5 also related to keyboard

mouse1 and event 6: mouse data
event7-event9 also related to mouse


#### Interrupts

Whenever something is to be done by a processor, the command is sent via a signal called an interrupt, telling the processor to stop what it is currently doing to address it, suspending what the processor is currently doing. Keyboard and mouse inputs are served as interrupts.

Interrupt signals are emitted by hardware or software.

ISR (Interrupt Service Routine): I/O devices have one bus control line that is dedicated to the purpose of sending interrupts

Handling an IRQ
1. Devices raise an IRQ
2. Processor interrupts the program currently being executed
3. Device is informed that its request has been recognized and the device deactivates the request signal
4. The requested action is performed
5. An interrupt is enabled and the interrupted program is resumed


#### I/O with Files

Three classes are provided to perform output and input of charactors to and from files: ofstream (write), ifstream (read), and fstream (read and write). These classes are derived directly or indirectly from the classes istream and ostream.
