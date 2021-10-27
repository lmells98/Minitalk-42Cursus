# Minitalk-42Cursus

The purpose of this project is to code a small data exchange program using UNIX signals.
We are prohibited to using only one gloabal variable.

- We must create a communication program on the form of a server and a client.
- The server must be launched first, after launch it must display its PID.
- The client must be able to communicate the string sent as a parameter to the server. Once recieved, the server must display it.
- Speed is crucial. If we think it's taking too long, then it probably is too slow.
- The server should be able to recieve several strings in a row from the client, without being restarted.
- Only able to use two signals ```SIGUSR1``` and ```SIGUSR2```.
