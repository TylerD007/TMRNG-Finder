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

#ifndef TMRNG_H
#define TMRNG_H

#ifdef _MSC_VER
#pragma once
#endif //_MSC_VER

#include <stdio.h>//for sprintf
#include <vector>

#define ARROW_NONE 		0x00
#define ARROW_UP 		0x01
#define ARROW_UP_RIGHT 		0x02
#define ARROW_RIGHT 		0x04
#define ARROW_DOWN_RIGHT 	0x08
#define ARROW_DOWN 		0x10
#define ARROW_DOWN_LEFT 	0x20
#define ARROW_LEFT 		0x40
#define ARROW_UP_LEFT 		0x80
#define ARROW_ALL	 	0xFF

#define CARD_GOBLIN		0x0
#define CARD_FANG 		0x1
#define CARD_SKELETON 		0x2
#define CARD_FLAN 		0x3
#define CARD_ZAGHNOL 		0x4
#define CARD_LIZARD_MAN 	0x5
#define CARD_ZOMBIE 		0x6
#define CARD_BOMB 		0x7
#define CARD_IRONITE 		0x8
#define CARD_SAHAGIN 		0x9
#define CARD_YETI 		0xA
#define CARD_MIMIC 		0xB
#define CARD_WYERD 		0xC
#define CARD_MANDRAGORA 	0xD
#define CARD_CRAWLER 		0xE
#define CARD_SAND_SCORPION 	0xF
#define CARD_NYMPH 		0x10
#define CARD_SAND_GOLEM 	0x11
#define CARD_ZUU 		0x12
#define CARD_DRAGONFLY 		0x13
#define CARD_CARRION_WORM 	0x14
#define CARD_CERBERUS 		0x15
#define CARD_ANTLION 		0x16
#define CARD_CACTUAR 		0x17
#define CARD_GIMME_CAT 		0x18
#define CARD_RAGTIME_MOUSE 	0x19
#define CARD_HEDGEHOG_PIE 	0x1A
#define CARD_RALVUIMAGO 	0x1B
#define CARD_OCHU 		0x1C
#define CARD_TROLL 		0x1D
#define CARD_BLAZER_BEETLE	0x1E
#define CARD_ABOMINATION 	0x1F
#define CARD_ZEMZELETT 		0x20
#define CARD_STROPER 		0x21
#define CARD_TANTARIAN 		0x22
#define CARD_GRAND_DRAGON 	0x23
#define CARD_FEATHER_CIRCLE 	0x24
#define CARD_HECTEYES 		0x25
#define CARD_OGRE 		0x26
#define CARD_ARMSTRONG 		0x27
#define CARD_ASH		0x28
#define CARD_WRAITH 		0x29
#define CARD_GARGOYLE 		0x2A
#define CARD_VEPAL 		0x2B
#define CARD_GRIMLOCK 		0x2C
#define CARD_TONBERRY 		0x2D
#define CARD_VETERAN 		0x2E
#define CARD_GARUDA 		0x2F
#define CARD_MALBORO 		0x30
#define CARD_MOVER		0x31
#define CARD_ABADON 		0x32
#define CARD_BEHEMOTH		0x33
#define CARD_IRON_MAN 		0x34
#define CARD_NOVA_DRAGON	0x35
#define CARD_OZMA 		0x36
#define CARD_HADES 		0x37
#define CARD_HOLY 		0x38
#define CARD_METEOR 		0x39
#define CARD_FLARE		0x3A
#define CARD_SHIVA 		0x3B
#define CARD_IFRIT		0x3C
#define CARD_RAMUH 		0x3D
#define CARD_ATOMOS 		0x3E
#define CARD_ODIN 		0x3F
#define CARD_LEVIATHAN 		0x40
#define CARD_BAHAMUT		0x41
#define CARD_ARK 		0x42
#define CARD_FENRIR		0x43
#define CARD_MADEEN		0x44
#define CARD_ALEXANDER 		0x45
#define CARD_EXCALIBUR_II 	0x46
#define CARD_ULTIMA_WEAPON 	0x47
#define CARD_MASAMUNE 		0x48
#define CARD_ELIXIR 		0x49
#define CARD_DARK_MATTER 	0x4A
#define CARD_RIBBON 		0x4B
#define CARD_TIGER_RACKET 	0x4C
#define CARD_SAVE_THE_QUEEN 	0x4D
#define CARD_GENJI 		0x4E
#define CARD_MYTHRIL_SWORD	0x4F
#define CARD_BLUE_NARCISS 	0x50
#define CARD_HILDA_GARDE_3 	0x51
#define CARD_INVINCIBLE 	0x52
#define CARD_CARGO_SHIP 	0x53
#define CARD_HILDA_GARDE_1 	0x54
#define CARD_RED_ROSE 		0x55
#define CARD_THEATER_SHIP 	0x56
#define CARD_VILTGANCE 		0x57
#define CARD_CHOCOBO 		0x58
#define CARD_FAT_CHOCOBO 	0x59
#define CARD_MOG 		0x5A
#define CARD_FROG 		0x5B
#define CARD_OGLOP 		0x5C
#define CARD_ALEXANDRIA 	0x5D
#define CARD_LINDBLUM 		0x5E
#define CARD_TWIN_MOONS 	0x5F
#define CARD_GARGANT 		0x60
#define CARD_NAMINGWAY		0x61
#define CARD_BOCO 		0x62
#define CARD_AIRSHIP 		0x63

typedef BYTE CARD[6], *LPCARD;

class SearchedCardModule
{
	private:
	CARD card;
	FILE* file;
	
	public:
	SearchedCardModule(BYTE card_id, BYTE card_arrows, const char* file_name)
	{
		card[0]=card_id; card[1]=card_arrows;card[2]=0;card[3]=0;card[4]=0;card[5]=0;		
		file=NULL;				
		file=fopen(file_name,"r");
		
		if (file)
		{
			fclose(file);
			remove(file_name);
		}		
		
		file=fopen(file_name, "a+");
	}
	
	~SearchedCardModule()
	{
		fclose(file);
	}
	
	public:		
	LPCARD GetCard(){return card;}
	FILE* GetFile(){return file;}	
};

struct Database
{
	BYTE card_base_stats[0x1f4];//The 0x1f4 bytes long database on address 0x800121c8 contains the card base stats (attack, defense, magic defense and points). When the card game module is loaded, the database is copied to address 0x80103800	
	BYTE card_decks[0x400];//The 0x400 bytes long database on address 0x80103c00 contains the list of all opponent's card decks
	BYTE card_arrow_values[0x8];//The database on address 0x801ff948 contains the card arrows base values
	
	Database()
	{
		LoadDatabase(card_base_stats,0x1f4,"card_basestats.bin");
		LoadDatabase(card_decks,0x400,"card_decks.bin");
		BYTE buffer[8]={ARROW_UP,ARROW_UP_RIGHT,ARROW_RIGHT,ARROW_DOWN_RIGHT,ARROW_DOWN,ARROW_DOWN_LEFT,ARROW_LEFT,ARROW_UP_LEFT};		
		memcpy(card_arrow_values,buffer,0x8*sizeof(BYTE));		
	}
	
	bool LoadDatabase(BYTE* buffer, SIZE_T size, const char* file_name)
	{
		FILE* file=NULL;
		file=fopen(file_name,"rb");
		if (!file) return false;		
		fread(buffer, sizeof(BYTE), size, file);
		fclose(file);
		return true;
	}
	
};

class TMRNG
{
	private:		
	DWORD rng;	//[0x2c94]=0x24040001	
	CARD card;
	BYTE player_id;//0x801ffe18
	BYTE special_byte;//0x801ffe28
	
	//searched cards list
	std::vector<SearchedCardModule*> searched_cards_list;

	//REGISTERS
	DWORD v0,v1,a0,a1,a2,s0,s1,s2;
	DWORD64 hilo; //high-low register used for multiplication
	
	//DATABASES
	static Database* database;			
	
	public:
	TMRNG(): rng(0x24040001), player_id(0x0), special_byte(0x0)
	{
		if (!database){database=new Database;}
	} 	
			
	inline void NextRNG() //function 0x80062b3c --> bfc02200
	{
		rng=rng*0x41c64e6d+0x3039;
		v0=(rng>>0x10) & 0x7fff;
	}
	
	inline void PreviousRNG()
	{
		rng=rng*0xeeb9eb65+0xfc77a683;
	}
	
	inline void NextRNGDeprecated() //function 0x80062b3c --> 1fc04338
	{
		rng=rng*0x41c64e6d + 0x6072;	
		v0=(rng>>0x11);
	}
	
	public:
	
	void SetPlayerID(BYTE player_id){this->player_id=player_id;}
	void AddSearchedCard(BYTE card_id, BYTE card_arrows, const char* file_name){searched_cards_list.push_back(new SearchedCardModule(card_id,card_arrows,file_name));}
		
	void SearchGameCards()
	{			
		if (searched_cards_list.size()==0) return;
		
		LPCARD searched_card=NULL;		
		
		for(DWORD search_rng=0;search_rng!=0xffffffff;search_rng++)
		{
			rng=search_rng;						
			SetCardID();
			
			for (int count=0;count<searched_cards_list.size();count++)
			{
				searched_card=searched_cards_list[count]->GetCard();
				
				if (card[0]==searched_card[0])
				{
					SetCardAttributes();
					
					if ( (card[1]==searched_card[1]) && (card[2]>=searched_card[2]) && (card[4]>=searched_card[4]) && (card[5]>=searched_card[5]))	 
					{
						rng=search_rng;
						for (int count=0;count<34;count++)
						{
							PreviousRNG();
						}
			
					rewind(searched_cards_list[count]->GetFile());
					fprintf(searched_cards_list[count]->GetFile(),"%08X | %08X | %02X | %02X | %02X | %02X | %02X | %02X\n", search_rng, rng, card[0], card[1], card[2], card[3], card[4], card[5]);
					memcpy(searched_card,card,sizeof(CARD));			
		
					}
					
					break;				
				}		
			}
			
		}
	}
	
	void SearchOverworldCard(BYTE card_id, BYTE card_arrows, const char* file_name)
	{
		SearchedCardModule searched_cards_list(card_id,card_arrows,file_name);
		LPCARD searched_card=NULL;
		
		SetCardID(card_id);
		
		for(DWORD search_rng=0;search_rng!=0xffffffff;search_rng++)
		{
			rng=search_rng;	
			searched_card=searched_cards_list.GetCard();
			SetCardAttributes();
			
			if ( (card[1]==searched_card[1]) && (card[2]>=searched_card[2]) && (card[4]>=searched_card[4]) && (card[5]>=searched_card[5]))	 
			{			
				rng=search_rng;
			
				rewind(searched_cards_list.GetFile());
				fprintf(searched_cards_list.GetFile(),"%08X | %08X | %02X | %02X | %02X | %02X | %02X | %02X\n", search_rng, rng, card[0], card[1], card[2], card[3], card[4], card[5]);
				memcpy(searched_card,card,sizeof(CARD));
			}
			
		}
		
	}
	
	inline void SetCardID(BYTE card_id)
	{
		card[0]=card_id;
	}
	
	inline void SetCardID() //function 0x800aebb4
	{
	
		//NextRNG();//0x80aebd0
		
		//800aec18: function SetCard start
		//--------------------------------
		NextRNG(); //0x800aec3c
		
		v1=(v0 & 0xff); //800aec44
		
		if 		(v1<0x14)	a0=0x0;
		else if (v1<0x28)	a0=0x1;
		else if (v1<0x3c)	a0=0x2;
		else if (v1<0x50)	a0=0x3;
		else if (v1<0x64)	a0=0x4;
		else if (v1<0x78)	a0=0x5;
		else if (v1<0x8c)	a0=0x6;
		else if (v1<0xa0)	a0=0x7;
		else if (v1<0xb4)	a0=0x8;
		else if (v1<0xc8)	a0=0x9;
		else if (v1<0xdc)	a0=0xa;
		else if (v1<0xf0)	a0=0xb;
		else if (v1<0xfc)	a0=0xc;
		else if (v1<0xfe)	a0=0xd;
		else if (v1<0xff)	a0=0xe;
		else				a0=0xf;		
					
		//800aed00
		v0=player_id;		//player_id (0x801ffe28) is used to find the opponent's deck in database 0x80103c00 
		v1=special_byte;	//if special_byte is not 0, a special routine sets the card_id		
		
		v0=(v0<<0x4)+a0; //index of the card_id on the card decks database		
		a2=database->card_decks[v0];//a2=80103c00[v0]	
		
		if (v1!=0) //800aed18
		{
			NextRNG();			
			hilo= (DWORD64)(v0) * 0x51eb851f;
			v1=(int)(v0) >> (int)0x1f;
			a0=(int)(hilo>>0x20) >> (int)0x5;
			a0-=v1;
			v1=a0<<0x1;
			v1+=a0;
			v1=v1<<0x3;
			v1+=a0;
			v1=v1<<0x2;
			a2=v0-v1;						
		}//0x800aed5c	
		
		v0=0;//v0=[801ff9e0+0x550]	
		
		if (v0!=0) //v0!=s2=0
		{
			v0=0;//v0=[0x801ff9e0+0x54c]
			
			if (v0!=0) //I think this is a kind of safety check, not sure; it won't be used anyways
			{
				card[0]=0xff;card[1]=0xff;card[2]=0xff;card[3]=0xff;card[4]=0xff;				
				return;
			}			
		}
			
		a2=(a2 & 0xff);	
			
		//1. CARD ID | 0x800af3e8			
	
		card[0]=a2; //800af44c		
	}
	
	inline void SetCardAttributes()
	{		
		//2. CARD ATTACK | 0x800af484
		
		v0=(card[0] & 0xff);			
		v1=(v0<<0x2)+v0;		
		v0=database->card_base_stats[v1]; //v0=80103800[v1]
		
		s0=(v0>>0x1);//s0=s1=(v0>>0x1)
		
		if (s0!=0)//800af4a4
		{
			NextRNG();			
			v1=v0 % s0;		
			v1=s0+v1;
			card[2]=v1;
		} //0x800af4f0
		else
		{
			card[2]=0; //800af4f0
		}
			
		//3. CARD DEFENSE | 0x800af4f4
		
		v0=(card[0] & 0xff);		
		v1=(v0<<0x2)+v0;		
		v0=database->card_base_stats[v1+0x2]; //v0=80103800[v1+0x2]			
		
		s0=(v0>>0x1);//s0=s1=(v0>>0x1)

		if (s0!=0)//800af514
		{
			NextRNG();			
			v1=v0 % s0;
			v1=s0+v1;
			card[4]=v1;			
		} //0x800af560
		else
		{
			card[4]=0; //800af560
		}				
	
		//4. CARD MAGIC DEFENSE | 0x800af564
		
		v0=(card[0] & 0xff);		
		v1=(v0<<0x2)+v0;	
		v0=database->card_base_stats[v1+0x3]; //v0=80103800[v1+0x3]
		
		s0=(v0>>0x1);//s0=s1=(v0>>0x1)	
		
		if (s0!=0)//800af584
		{
			NextRNG();			
			v1=v0 % s0;			
			v1=s0+v1;
			card[5]=v1;			
		} //0x800af5d0
		else
		{
			card[5]=0; //800af5d0
		}		
		
		//5. CARD ARROWS | 0x800af5d4
		
		NextRNG();		
		hilo=(DWORD64)v0*0x51eb851f;
		v1=(int)(v0)>>(int)0x1f;
		
		a0=(int)(hilo>>0x20)>>(int)0x5; //800af60c
		a0-=v1;
		v1=a0<<0x1;
		v1+=a0;
		v1=v1<<0x3;
		v1+=a0;
		v1=v1<<0x2;
		a0=v0-v1;
		
		//a1=[0x801ff9e0+0x4c8]=0x1
		//v1=[0x801ff9e0+0x4cc]=0x8
		//a2=[0x801ff9e0+0x4d0]=0x19
		//a3=[0x801ff9e0+0x4d4]=0x1f
		//t0=[0x801ff9e0+0x4d8]=0x12
		//t1=[0x801ff9e0+0x4dc]=0x9
		//t2=[0x801ff9e0+0x4e0]=0x5
		//t3=[0x801ff9e0+0x4e4]	=0x2	
		
		//s2 contains the total ammount of arrows the card will have (0 to 8)		
		if 		(a0<0x01){s2=0;}//a0<a1
		else if (a0<0x09){s2=1;}//a0<a1+v1=0x1+0x8
		else if (a0<0x22){s2=2;}//a0<a1+v1+a2=0x1+0x8+0x19
		else if (a0<0x41){s2=3;}//a0<a1+v1+a2+a3=0x1+0x8+0x19+0x1f
		else if (a0<0x53){s2=4;}//a0<a1+v1+a2+a3+t0=0x1+0x8+0x19+0x1f+0x12
		else if (a0<0x5c){s2=5;}//a0<a1+v1+a2+a3+t0+t1=0x1+0x8+0x19+0x1f+0x12+0x9
		else if (a0<0x61){s2=6;}//a0<a1+v1+a2+a3+t0+t1+t2=0x1+0x8+0x19+0x1f+0x12+0x9+0x5
		else if (a0<0x63){s2=7;}//a0<a1+v1+a2+a3+t0+t1+t2+t3=0x1+0x8+0x19+0x1f+0x12+0x9+0x5+0x2
		else			 {s2=8;}		

		card[1]=0;//800af6b0
		
		if (s2!=0)
		{
			s0=0;
			s1=0; //number of arrows read in loop (max s2)
					
			while(1) //800af6c4
			{
				NextRNG();
				v0=v0 & 0x7;				
				v1=database->card_arrow_values[v0];//the address 0x801ff948 contains the card arrow values				
				
				a0=card[1];						
				v0=a0 | v1;			
				
				if (!(a0 & v1))
				{
					card[1]=v0;
					s1++;	//add number of arrows							
					if (!(s1<s2)) break;						
				}			
					
			}//800af70c
			
		}//800af70c
		
		//6. CARD TYPE | 0x800af70c
		
		v1=(card[0] & 0xff);
		v0=(v1<<0x2)+v1;
		v0=database->card_base_stats[v0+0x1]; //v0=80103800[v0+0x1]
				
		card[3]=v0;		
		NextRNG();//800af720		
		v0=v0 & 0x7f;
		
		if (!(v0))
		{
			card[3]=0x2;			
		}	
	
	}	
	
};

Database* TMRNG::database=NULL;

#endif //TMRNG_H
	
