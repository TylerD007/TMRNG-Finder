/*
 * TMRNG-Finder - Tetra Master Random Number Generator Finder
 * Written in C++

 * Copyright (C) 2023 Ciro Bogea Fernandes.

 * This library is free software. You can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation;

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

 * Permission to use this software and its documentation *AS IT IS* for any purpose
 * is hereby granted without fee, provided that the above copyright notice appear 
 * in all copies and that both that copyright notice and this permission notice appear
 * in supporting documentation.  It is provided "as is" without express or implied warranty. 
*/

/* IMPORTANT NOTE:
 * TMRNG makes use of two internal databases from Final Fantasy IX:
 * 1. card_basestats.bin : The 0x1f4 bytes long database on address 0x800121c8 contains the card base stats (attack, defense, magic defense and points).
 * 2. card_decks.bin : The 0x400 bytes long database on address 0x80103c00 contains the list of all opponent's card decks
 * Due to copyright issues, both databases may not be distributed with this file. You must have access to them by your own. 
 * Place both files on the same folder where the application as with the above mentioned names.
*/
 
#include <windows.h>
#include "TMRNG.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{

	switch(message) 
	{		
		case WM_DESTROY: break; //PostQuitMessage(0);
	
		case WM_CLOSE:
		{			
			PostQuitMessage(0);
			EndDialog(hWnd, 0);			
		} break;
							
		default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return false; 
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hWnd;
	MSG msg;

	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc;
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);		
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); 
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); 

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	//This first example searches three cards with specific arrow combinations, when playing against Magic Master Thalisa (player id 52)
	//The list with all decks in the game can be found here (subtract 1 for the player_id): 
	//https://finalfantasy.fandom.com/wiki/Final_Fantasy_IX_opponents%27_Tetra_Master_decks
	//The results will be output as a text file in the app folder
	//Each search takes 15 to 20 minutes on a regular machine. We recomend only one search per time.
	TMRNG tmrng;			
	tmrng.SetPlayerID(52);	
	tmrng.AddSearchedCard(CARD_FLARE, ARROW_UP | ARROW_LEFT | ARROW_DOWN_LEFT | ARROW_UP_RIGHT,"flare.txt");
	tmrng.AddSearchedCard(CARD_HOLY, ARROW_RIGHT,"holy.txt");
	tmrng.AddSearchedCard(CARD_METEOR, ARROW_NONE,"meteor.txt");
	tmrng.SearchGameCards();
	
	
			
	//This second example searches the Dark Matter card with all arrows, except the up one, as an overworld reward			
	//Searching overworld cards takes longer than game cards, since the card_id matches for all possible rngs. Again, we strongly advise one search 
	tmrng.SearchOverworldCard(CARD_DARK_MATTER, ARROW_ALL & not(ARROW_UP),"dark_matter.txt");
			
	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","TMRNG-Finder",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		GetSystemMetrics(SM_CXSCREEN)/2-(640/2), 
		GetSystemMetrics(SM_CYSCREEN)/2-(480/2), 
		640, 480, NULL,NULL,hInstance,NULL);		
	
	if(hWnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



	
