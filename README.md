# IntroductionToRobotics
Third year course of Faculty of Mathematics and Computer Science. <br>
Working with Arduino UNO. <br>
Code and pictures.

<details>
<summary> Homework 1 </summary>

#### Components
RGB LED (1 minimum), potentiometers (3 minimum), resistors and wires (per logic). <br>

#### Task
Use a separat potentiometer in controlling each of thecolor of the RGB led (Red,Green andBlue). The control must be donewithdigital electronics (aka you must read the value of the potentiome-ter with Arduino, and write a mapped value to each of the pins connectedto the led). <br>

#### Setup
![Arduino](https://user-images.githubusercontent.com/98409275/197863773-b0e5a4f0-5706-4698-9eda-f89ea92e1ea4.jpeg)
<br>

#### DEMO
Here is the demo https://youtu.be/b0MgJnrOVkQ

#### [CODE](https://github.com/beatricedoncea2000/IntroductionToRobotics/blob/main/homework1/3%20Potentiometers%20and%201%20RGB%20Led.ino)
</details>

<details>
<summary> Homework 2 </summary>

#### Requirements
Building the traffic lights for a crosswalk using 2 LEDs to represent the traffic lights for pedestrians (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green). The traffic lights simulator will start once the button is pressed, following these states:
- State 1: (default, reinstated after state 4 ends): green light for cars, red light for people, no sounds. Duration: indefinite, changed bypressing the button.
- State 2: (initiated by counting down 10 seconds after a button press): the light should be yellow for cars, red for people and no sounds. Duration: 3 seconds.
- State 3: (iniated after state 2 ends): red for cars, green for people and a beeping sound from the buzzer at a constant interval. Duration: 10 seconds.
- State 4: (initiated after state 3 ends): red for cars, blinking green for people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state 3. Duration: 5 seconds.

Pressing the button in any other state than state 1 will have no effect.  

#### Components
5 leds, 1 button, 1 buzzer, wires, resistors

#### Setup
![WhatsApp Image 2022-11-01 at 11 27 05 PM](https://user-images.githubusercontent.com/98409275/199347387-c540be45-1927-46b8-8253-08d5da2a716b.jpeg)
![WhatsApp Image 2022-11-01 at 11 27 06 PM](https://user-images.githubusercontent.com/98409275/199347410-1804e76b-1683-4aab-a1a8-920544941541.jpeg)

#### DEMO
Here is the demo https://youtu.be/kpoi5BEdz3E

#### [CODE](https://github.com/beatricedoncea2000/IntroductionToRobotics/blob/main/homework2/Traffic%20lights%20for%20a%20crosswalk.ino)
</details>



<details>
<summary> Homework 3 </summary>

#### Requirements
Use the joystick to control the position of the segment and ”draw” on the display. The movement between segments should be natural (meaning they should jump from the current positiononly to neighbors, but without passing through ”walls”). The system has the following states:
- State 1 (default, but also initiated after a button press in State 2): Current position blinking. Can use the joystick to move from one position to neighbors.   Short pressing the button toggles State2. Long pressing the button in state 1 resets the entire display byturning all the segments OFF and moving the current position to the decimal point.
- State 2 (initiated after a button press in State 1): The current segment stops blinking, adopting the state of the segment before selection (ON or OFF). Toggling the X (or Y, you chose) axis should change the segment state from ON to OFF or from OFF to ON. Clicking the joystick should save the segment state and exit back to state 1.

#### Components
1 7-segment display, 1 joystick, resistors and wires (per logic). <br>

#### Setup
<details> 
<summay> See here the setup </summary>
![Arduino1](https://user-images.githubusercontent.com/98409275/200699584-a387199d-5cb3-4836-b188-112d6db299d0.jpeg)
![Arduino2](https://user-images.githubusercontent.com/98409275/200699594-7b7fc85f-85de-4864-bbf7-3c4c4773a0d3.jpeg)
</details>

#### DEMO
Here is the demo https://youtu.be/tZOO9YyoJVY

#### [CODE](https://github.com/beatricedoncea2000/IntroductionToRobotics/blob/main/homework3/Draw%20on%20a%207-segment%20display%20with%20a%20joystick.ino)
</details>
