# HeartWave-Project

## Team Members:

Gift Akinpelu  
Nathaniel Enyia  
Dondre Samuels  
Nicholas Veselskiy  

## Delegation of Work:

### Gift Akinpelu
Completed the Sequence Diagrams and did most of the work on the UML diagrams

### Nathaniel Enyia
Completed the Traceability matrix and did half of the use cases

### Dondre Samuels
Did the other half of the use cases, the initial ui setup of the program and first integration with the plotting library

### Nicholas Veselskiy
Asssisted with the UML diagrams and completed most of the coding



## Organization of the submission
Under design documentation you will find our design diagrams such as the UML, sequence diagrams etc...

Under HeartWave-Videos you will find some demonstration of our program.

Weekly-Tasking was for our purposes to delegate tasks.

src is where the project source code is along with the HistoryData which is stored in the file named as such.


## Organization of the code

We have 6 main classes: Settings, DataSource, HeartWave, Record, MainWindow, HistoryManager.

**Their roles are as follows:**

- ### Settings 
    - is an entity class used to store the current settings of the application

- ### Record 
    - is an entity class meant to represent a session and thus contains the nessesary information to record one in the history of the device

- ### HistoryManager 
    - is a class which handles storing the Records on the disk and loading them from the disk

- ### MainWindow 
    - is a large class which handles ui interactions including pressing buttons and controlling the menus

- ### HeartWave 
    - represents the internals of the device and handles processing new data controlling the session and publishing the information to the history manager when a session finishes

- ### DataSource 
    - will generate datapoints for the graph when you ask for some