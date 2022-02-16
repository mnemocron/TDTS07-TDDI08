//This file was generated from UPPAAL 4.0.6 (rev. 2987), March 2007

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
Why is this not fullfillable? is it not guaranteed that after the initial state, the send_msg state is reached?
*/
SND.M0 --> SND.send_msg

/*
the system is deadlock free
*/
A[] not deadlock
