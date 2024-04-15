#pragma once

#include "progress.h"

void learnSkill(PokeData * pokemon);

void levelup(PokeData * pokemon);

void initPokemon(PokeData * pokemon, PokeList * list, int sel);

void setPokemon(PokeData * pokemon, PokeList * list, int sel, int learned, int curlevel, int *arr);

PokeData * setRandomPoke(PokeList * list, int idenNum0, int idenNum1, int skillnum, int type);

int throwBall(PokeData* poke, int type);

int useSkill(Skill *skill, PokeData * enemy);

void skillSound(Skill *skill, struct foo * arg2);

int catchPokemmon(Userdata *user, PokeData *poke, int innersel, struct foo * arg2);

void randomCry(struct foo * arg2);

void randomCity(struct foo * arg);

int story0(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2);

int story1(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2);

int story2(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2);

int story3(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2);

int story4(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2);

int story5(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2);

int story6(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2);

void mainStoryLine(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2);
