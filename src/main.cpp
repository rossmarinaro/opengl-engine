/******* MAIN ******/

#include "../headers/app.h"
#include "../headers/logs.h"


	bool CoinFlip(void)
	{
		srand(time(NULL)); //reset rand
		float randNum = rand() % 10;
		return randNum >= 6 ? true : false;
	}


	//-------------------------------------- main
	
#undef main

	int main(int argc, char* args[])
	{   
		//Log::write(CoinFlip() == true ? "coin flipped true" : "coin flipped false");
		
		Application* app = new Application();      
		delete app;
		return 0;
		
	}



