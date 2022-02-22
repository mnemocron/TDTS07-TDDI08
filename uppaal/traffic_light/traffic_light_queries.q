//This file was generated from UPPAAL 4.0.6 (rev. 2987), March 2007

/*
lights on perpendicular directions must not simultaneously be green.
*/
A[] not ((N.GREEN or S.GREEN) and (W.GREEN or E.GREEN))

/*
If car car arrives at N, the car will eventually get green
*/
N.car --> N.GREEN

/*
If car car arrives at S, the car will eventually get green
*/
S.car --> S.GREEN

/*
If car car arrives at E, the car will eventually get green
*/
E.car --> E.GREEN

/*
If car car arrives at W, the car will eventually get green
*/
W.car --> W.GREEN

/*
A computational path exists for N to turn green
*/
E<> N.GREEN

/*
A computational path exists for S to turn green
*/
E<> S.GREEN

/*
A computational path exists for E to turn green
*/
E<> E.GREEN

/*
A computational path exists for W to turn green
*/
E<> W.GREEN

/*

*/
A[] not deadlock
