#ifndef CONFLICTPAWN_H
#define CONFLICTPAWN_H

class ConflictPawn {

private : 
	int current_position; 
	// Les positions militaires sont
	// de -x jusqu'au x
public :
	ConflictPawn() :current_position(0) {};
	int move(int a = 0) ; 


};
#endif