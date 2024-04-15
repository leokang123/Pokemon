#pragma once 

#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncursesw/curses.h>
#include <wchar.h>
#include <locale.h>
#include <pthread.h>
#include <time.h>

// 효과음 
#define TEXTSOUND               "../assets/effectSound/text.wav"
#define ARROWSOUND              "../assets/effectSound/arrow.wav"

// 공격 효과음 
#define ICESOUND1               "../assets/effectSound/attack/ice1.wav"
#define ICESOUND2               "../assets/effectSound/attack/ice2.wav"
#define FIRESOUND1              "../assets/effectSound/attack/fire1.wav"
#define FIRESOUND2              "../assets/effectSound/attack/fire2.wav"
#define WATERSOUND1             "../assets/effectSound/attack/water1.wav"
#define WATERSOUND2             "../assets/effectSound/attack/water2.wav"
#define GRASSSOUND1             "../assets/effectSound/attack/grass1.wav"
#define GRASSSOUND2             "../assets/effectSound/attack/grass2.wav"
#define NORMALSOUND1            "../assets/effectSound/attack/normal1.wav"
#define NORMALSOUND2            "../assets/effectSound/attack/normal2.wav"
#define THUNDERSOUND1           "../assets/effectSound/attack/thunder1.wav"
#define THUNDERSOUND2           "../assets/effectSound/attack/thunder2.wav"
#define ROCKSOUND1              "../assets/effectSound/attack/rock1.wav"
#define ROCKSOUND2              "../assets/effectSound/attack/rock2.wav"

// 울음 효과음 
#define CRYSOUND1               "../assets/effectSound/cry/cry1.wav"
#define CRYSOUND2               "../assets/effectSound/cry/cry2.wav"
#define CRYSOUND3               "../assets/effectSound/cry/cry3.wav"
#define CRYSOUND4               "../assets/effectSound/cry/cry4.wav"
#define CRYSOUND5               "../assets/effectSound/cry/cry5.wav"
#define CRYSOUND6               "../assets/effectSound/cry/cry6.wav"
#define CRYSOUND7               "../assets/effectSound/cry/cry7.wav"
#define CRYSOUND8               "../assets/effectSound/cry/cry8.wav"
#define CRYSOUND9               "../assets/effectSound/cry/cry9.wav"
#define CRYSOUND10              "../assets/effectSound/cry/cry10.wav"
#define CRYSOUND11              "../assets/effectSound/cry/cry11.wav"
#define CRYSOUND12              "../assets/effectSound/cry/cry12.wav"

// 부가 게임 효과음 
#define GETITEMSOUND            "../assets/effectSound/etc/getitem.wav"
#define LEVELUPSOUND            "../assets/effectSound/etc/levelup.wav"
#define HEALSOUND               "../assets/effectSound/etc/heal.wav"
#define RESTOREHEALTHSOUND      "../assets/effectSound/etc/restorehealth.wav"
#define FLEESOUND               "../assets/effectSound/etc/flee.wav"
#define THROWBALLSOUND          "../assets/effectSound/etc/throwball.wav"
#define WAITINGCAUGHTSOUND      "../assets/effectSound/etc/waitingcaught.wav"
#define CAUGHTSOUND             "../assets/effectSound/etc/caught.wav"
#define POPPOKEMONSOUND         "../assets/effectSound/etc/poppokemon.wav"
#define SUCCESSCAUGHTSOUND      "../assets/effectSound/etc/successcaught.wav"
#define HEALTHLOWSOUND          "../assets/effectSound/etc/healthlow.wav"

// 배경음악 
#define TITLESOUND              "../assets/backSound/title.wav"
#define BATTLESOUND             "../assets/backSound/battle.wav"
#define POKECENTERSOUND         "../assets/backSound/pokecenter.wav"
#define POKESHOPSOUND           "../assets/backSound/shop.wav"
#define VICTORYSOUND            "../assets/backSound/victory.wav"
#define FINALBATTLESOUND        "../assets/backSound/finalbattle.wav"
#define CITY1SOUND              "../assets/backSound/city1.wav"
#define CITY2SOUND              "../assets/backSound/city2.wav"
#define CITY3SOUND              "../assets/backSound/city3.wav"
#define HALLOFFAMESOUND         "../assets/backSound/halloffame.wav"
#define ENDINGSOUND             "../assets/backSound/ending.wav"

extern int line;

struct foo {
    char file[100];
    int x;
    float speed;
};

void * singleSound(void * arg);
void * loopSound(void * arg);

