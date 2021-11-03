# Minitalk-42Cursus

The purpose of this project is to code a small data exchange program using UNIX signals.
We are prohibited to using only one gloabal variable.
If we choose to use a global variable, we must justify our choice when defending our code during evaluations

- We must create a communication program on the form of a server and a client.
- The server must be launched first, after launch it must display its PID.
- The client must be able to communicate the string sent as a parameter to the server. Once recieved, the server must display it.
- Speed is crucial. If we think it's taking too long, then it probably is too slow.
- The server should be able to recieve several strings in a row from the client, without being restarted.
- Communication between programs must be performed using only two signals ```SIGUSR1``` and ```SIGUSR2```.

<img width="1207" alt="Screen Shot 2021-11-03 at 3 54 13 PM" src="https://user-images.githubusercontent.com/86273901/140013615-87117748-16a0-44c1-a8bc-e7418c7c9b50.png">

# How to Use...

Mandatory - Supports ASCII Characters.

Bonus     - Supports ASCII Characters & sends a signal back to client upon receiving a message.

- Clone this repository.
- Open 2 terminal windows & change directory ```cd``` of both windows to the cloned repository.
- Run ```make m``` to build both the server ```./server``` and client ```./client``` executables.
- Run ```make b``` to build with the 'bonus' features.
- Run the server ```./server``` in 1 of the windows. The ```process id``` of the server ```<pid>``` will then be prompted.
- In the other window, run the client ```./client```.
- Use:  ```./client <pid> "Your Message Here!"```

# Support

- Mandatory - Supports ASCII Characters.
- Bonus - Supports Unicode Characters

Tested with valgrind.
- No memory leaks detected.
- All heap blocks freed -- no leaks possible.

Thankyou for taking the time to visit.

Leighton.
