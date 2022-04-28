
#### Research ####

##### Resources

- About input in Linux
    - https://www.kernel.org/doc/Documentation/input/input.txt
- About /dev/input
    - https://thehackerdiary.wordpress.com/2017/04/21/exploring-devinput-1/

#### Input Devices 

In Linux, all input devices are located within the /dev/input directory. Each device is configured to have event handlers that are present within this library. To see which events belong to which device, analyze the by-id or proc/bus/input/devices file.

#### Computer Bus

Common pathway through which information is sent from one component to another. The most important busses are the system bus and the I/O or expansion bus.

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


#### Event Support

To add device support we must handle events through the event interface. There are blocking and nonblocking reads. You always get a whole number of input events on a read.

Input event layout:
    struct input_event {        // 24 bytes per package
        struct timeval time;    // 16 bytes
        unsigned short type;    // 2 bytes
        unsigned short code;    // 2 bytes
        unsigned int value;     // 4 bytes
    }                           

- 'time': timestamp of when the event happened
    - Types: EV_REL for relative moment, EV_KEY for a keypress or release, more types are defined at include/uapi/linux/input-event-codes.h
    - Contains the system time
- 'code': the event code
    - Types: REL_X, KEY_BACKSPACE, complete list in include/uapi/linux/input-event-codes.h
- 'value': the value the event carries
    - Types: either relative change for EV_REL, absolute new value for EV_ABS (joysticks), or 0 for EV_KEY for release, 1 for keypress, and 2 for autorepeat
