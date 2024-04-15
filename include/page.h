#pragma once

#include "progress.h"
extern int line;

int startPage (struct foo * arg);

Userdata * loadUserPage(struct foo * arg);

Userdata * makeUserPage(PokeList * list, struct foo * arg);

void showPokeIden(PokeList * list);

void pokeShop(Userdata * user,struct foo * arg, struct foo * arg2);

void healCenter(Userdata * user,struct foo * arg,struct foo * arg2);

int battlePage(Userdata * user, Userdata* opp, PokeData * enemy, struct foo * arg, struct foo * arg2);

int menuPage(Userdata * user, PokeList * list, int (*ftr)(Userdata *, PokeList*, struct foo*, struct foo*), struct foo * arg, struct foo * arg2);

void endCredit(PokeList * list, struct foo * arg);
