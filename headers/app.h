#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

//#include "./audio.h"
#include "./window.h"       
#include "./inputs.h"



/****** Application *****/

class Application 
{

	public:

		static Application* s_instance;
		
		//Audio* m_audioMgr;
		Inputs* m_inputMgr;

		std::thread m_window_thread;	
			
		Application()
		{

			//m_audioMgr = new Audio();
			m_inputMgr = new Inputs;
		
	
		//new thread for window / gui
		
			std::thread m_window_thread(&InitializeWindow /* , , , etc... */); 
			m_window_thread.join();
	
		}
	   ~Application()
	   {
			//delete m_audioMgr;
			delete m_inputMgr;
			//delete s_instance;
			//std::terminate();

			Log::write("Application terminated");
	   };

};