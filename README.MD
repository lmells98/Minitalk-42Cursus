# Support
Only supports ASCII Characters!
Currently working on Unicode Support...

Tested with valgrind.
- No memory leaks detected.
- All heap blocks freed -- no leaks possible.

# Minitalk-42Cursus

The purpose of this project is to code a small data exchange program using UNIX signals.
We are prohibited to using only one gloabal variable.

- We must create a communication program on the form of a server and a client.
- The server must be launched first, after launch it must display its PID.
- The client must be able to communicate the string sent as a parameter to the server. Once recieved, the server must display it.
- Speed is crucial. If we think it's taking too long, then it probably is too slow.
- The server should be able to recieve several strings in a row from the client, without being restarted.
- Only able to use two signals ```SIGUSR1``` and ```SIGUSR2```.

# How to Use...

- Clone this repository.
- Open 2 terminal windows & change directory ```cd``` of both windows to the cloned repository.
- Run ```make all``` to bould both the server and client executables.
- Run the server ```./server``` in 1 of the windows. The ```process id``` of the server ```<pid>``` will then be prompted.
- In the other window, run the client ```./client```.
- Use:  ```./client <pid> "Your Message Here!"```


Thankyou for taking the time to visit.

Leighton.
