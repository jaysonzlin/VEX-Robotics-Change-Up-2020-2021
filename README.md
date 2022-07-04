# VEX-Robotics-Change-Up-2020-2021

##Description

<Insert video file here>
![image](https://user-images.githubusercontent.com/52141513/177196633-a2c3347b-325b-4138-a257-567e1f1ff2a7.png)
https://youtu.be/Hxs0q9UoMDQ
  
This is a reupload of VEX Team 92287's code for the 2020-2021 VEX Robotics Competition: Change Up. The code was coded on VEXcode V5 aka C++ with VEX API.   
This code helped team 92287X become VEX Worlds Arts Division Semifinalist and Georgia State Robot Skills Champion.
Additionally, it helped sister team 92287A becom VEX Worlds Engineering Division Quarterfinalist, Georgia State Robot Skills Champion Runner-Ups, and Irwin County Tournament Robot Skills Champion.
Half of the code is dedicated to mapping the robot's motors to controller buttons for the driver control portion of a match.  
Half of the code is dedicated to two autonomous routines: our State Champion and State Runner-Ups 106 point run for the Robot Skills Challenge; our homerow autonomous during the autonmous portion of a match.

## About
Being the only programmer of the two sister teams 92287X and 92287A, I was tasked with programming the Robot Skills and autonomous portion of our robot competition. At this time, I had never programmed, but I understood basic programming concepts. What you see is the result of many hours of self-teaching myself C++ with VEX API, forum browsing for what others in the community had done, and testing the program to work in real-time on a VEX competition field. All of this while still playing a key part in constructing the robot and leading the team. Needless to say, the code isn't the greatest in the world, but it did its job on a team with very little time to spare on anything apart from building the robot.

## Guide to the Code
Files ending in .h are header files for their corresponding .cpp files
106.cpp is a non-functional file containing our State Champion and State Runner-Ups 106 point run for the Robot Skills Challenge; it's meant to be pasted into main.cpp for Robot Skills  
main.cpp is a file based on VEX's own competition template and serves as the place where all the code is run  
opControl.cpp is a file holding controller mappings to motors  
stuff.cpp is a file holding the autonomous functions of the robot  
vex.cpp and robot-config.cpp are VEX files used to enable programming to VEX robots  

## The Robot
Our robot for VEX Change Up used 4 motors at 280 rpm on 3.25 inch wheels for its drivebase. Inside the robot, there were 2 motors used for the robot's rollers with the storing rollers at 600 rpm and the shooting roller at 1800 rpm. Outside the robot, two motors controlled a left and right intake at 600 rpm.
