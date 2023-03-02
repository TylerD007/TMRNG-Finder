# TMRNG-Finder
Extracts Final Fantasy IX Tetra Master cards from random numbers 
Written in C++
Copyright (C) 2023 Ciro Bogea Fernandes.

TMRNG-Finder makes use of two internal databases from Final Fantasy IX:
1. card_basestats.bin : The 0x1f4 bytes long database on address 0x800121c8 contains the card base stats (attack, defense, magic defense and points).
2. card_decks.bin : The 0x400 bytes long database on address 0x80103c00 contains the list of all opponent's card decks

Due to copyright issues, both databases may not be distributed with this file. You must have access to them by your own. 
Place both files on the same folder where the application is with the above mentioned names.
