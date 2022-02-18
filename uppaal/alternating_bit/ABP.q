//This file was generated from UPPAAL 4.0.6 (rev. 2987), March 2007

/*

*/
E<> CHAN.C1

/*

*/
E<> CHAN.C0

/*

*/
E<> SND.send_m1

/*
there exists at least one way where a message is sent
*/
E<> SND.send_m0

/*

*/
E<> RCV.rcv_m1

/*
there exists at least one way where a message is received
*/
E<> RCV.rcv_m0

/*

*/
SND.send_m0 --> RCV.rcv_m0

/*
the system is deadlock free
*/
A[] not deadlock
