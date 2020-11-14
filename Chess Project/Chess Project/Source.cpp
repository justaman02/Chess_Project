/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <Windows.h>
#include <iostream>
#include <thread>
#include <future>
#include "Board.h"
#include <Mmsystem.h>
#include <mciapi.h>

using std::cout;
using std::endl;
using std::string;


void main()
{
    srand(time_t(NULL));
    Board game("rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR");
    int code = -1;
    Pipe p;
    bool isConnect = p.connect();

    string ans;
    while (!isConnect)
    {
        cout << "cant connect to graphics" << endl;
        cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
        std::cin >> ans;

        if (ans == "0")
        {
            cout << "trying connect again.." << endl;
            Sleep(5000);
            isConnect = p.connect();
        }
        else
        {
            p.close();
            return;
        }
    }


    char msgToGraphics[1024];

    strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0");

	mciSendString("play backroundM.mp3 repeat", NULL, 0, NULL);//play backround music
    p.sendMessageToGraphics(msgToGraphics);   // send the board string

    // get message from graphics
    string msgFromGraphics = p.getMessageFromGraphics();


    while (msgFromGraphics != "quit")
    {
		
        cout << "------ " << msgFromGraphics << endl;

		//crrating string to contain massage from engain
        string from = "";
        from += msgFromGraphics[0];
        from += msgFromGraphics[1];
        cout << from << endl;
        string to = "";
        to += msgFromGraphics[2];
        to += msgFromGraphics[3];
        cout << to << endl;
        code = game.move(from, to);
		
		//cast from int to string
        msgToGraphics[0] = (char)(code + '0');
        msgToGraphics[1] = 0;
		
		//playing super epic sounds
		if (code != 0)
		{
			PlaySound("OOF.wav", NULL, SND_FILENAME | SND_ASYNC);//oof sound
		}
		else
		{
			PlaySound("wow.wav", NULL, SND_FILENAME | SND_ASYNC);//wow sound
		}

        // return result to graphics		
        p.sendMessageToGraphics(msgToGraphics);
       

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}

