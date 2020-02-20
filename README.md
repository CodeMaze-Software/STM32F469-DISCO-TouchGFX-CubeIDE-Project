# STM32F469-DISCO-TouchGFX-CubeIDE-Project

Basic project for further development of applications based on STM32F469DISCO and CUBE IDE. Just download the repository, attach the project to the CUBE IDE workspace.  Application The program performs basic activities, namely:  
- input from the user in the form of two buttons  
- displaying the counter value on the screen  
- sending data via UART 

Peripherals (i.e GPIO, UART) are configured in presenter.cpp when entering the screen. Peripheral executing (sending via UART, Tick LED blinking) is implemented in the file model.cpp 
The application can be used as a template for further work for users interested in GUI applications with Touch GFX and Cube IDE.
