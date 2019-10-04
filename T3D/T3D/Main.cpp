// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// main.cpp
//
// Main entry point. Creates and runs a T3DApplication

#include "T3DTest.h"
#include "Tutorial1.h"
#include "ShaderTest.h"
#include "GLTestApplication.h"
#include "tutorial4.h"
#include "AssignmentSweep.h"
#include "dog.h"
#include "tutuorial5.h"

#ifdef main
#undef main
#endif


using namespace T3D;

int main(int argc, char* argv[]){

   
	//T3DApplication *theApp = new Tutorial1();
	//T3DApplication *theApp = new GLTestApplication();
	//T3DApplication *theApp = new ShaderTest();

	//part 1 of assignment  
    //T3DApplication *theApp = new AssignmentSweep();
    //this is my part 2 of assignment
	//T3DApplication *theApp = new dog(); 
	//part 3 and 4, change the line 50 and 51 in tutorial 4, use line 50 is chip in wall and use line 51 is hole in wall 
	T3DApplication *theApp = new tutorial4();
	//T3DApplication *theApp = new tutuorial5();
	theApp->run();
	delete theApp;

	return 0;
}