//This file was generated from UPPAAL 4.0.6 (rev. 2987), March 2007

/*
there exists at least one way where a message is sent
*/
E<> SND.send_msg

/*
there exists at least one way where a message is received
*/
E<> RCV.M1

/*

*/
SND.send_msg --> RCV.rcv_msg

/*

*/
A[] (CHAN.C0 imply A<> CHAN.C1)

/*
if a message is sent it must be received at some point
*/
A[] (SND.send_msg imply A<> RCV.rcv_msg)

/*
the system is deadlock free
*/
A[] not deadlock
