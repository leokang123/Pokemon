#include "everyheader.h"

void levelup(PokeData * pokemon) {
    pthread_t tid2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    wchar_t *tempbuf = (wchar_t *)malloc(sizeof(wchar_t) * 100);
    struct foo * arg2 = (struct foo *)malloc(sizeof(arg2));

    arg2->x = 0;
    arg2->speed = 3.0f;
    strcpy(arg2->file,LEVELUPSOUND);


    int interface = LINES / 11.0 * 9;
    dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
    pthread_create(&tid2,&attr,singleSound,arg2);
    while(arg2->x != 1) {}
    swprintf(tempbuf,100,L"%ls가 5레벨이 올랐다 !!",pokemon->pokename);
    serialScreen(line++,ST,tempbuf,NORMAL);
    pokemon->level += 5;
    pokemon->fullHealth = pokemon->pokedata.health + (pokemon->level/2.0) * 15;

    visualgetch();
    free(tempbuf);
    free(arg2);
    for(int i = 0 ; i < 2 ; i++) learnSkill(pokemon);
    return ;
}

void learnSkill(PokeData * pokemon) {
    pthread_t tid;
    struct foo * arg2 = (struct foo *)malloc(sizeof(struct foo));
    arg2->x = 0;
    arg2->speed = 1.5f;
    strcpy(arg2->file,GETITEMSOUND);
    Skill * skills = readSkills();

    if(skills == NULL) {
        mvprintw(line++,ST,"error reading skills");
        refresh();
        free(arg2);
        free(skills);
        return; 
    }
    int interface = LINES / 11.0 * 9;
    dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
    int sel = 0, sel2 = 0;
    int max = 0;
    int learnIden = pokemon->point;
    if(learnIden > pokemon->pokedata.skillNum-1){
        serialScreen(line++,ST,L"당신의 포켓몬은 배울수 있는 스킬이 더이상 없습니다.", NORMAL);
        free(skills);
        visualgetch();
        return ;
    }
    
    Skill newSkill = skills[pokemon->pokedata.totalskill[learnIden] - 1];
    
    free(skills);
    wchar_t *tempbuf = (wchar_t *)malloc(sizeof(wchar_t) * 400);
    wmemset(tempbuf,0,400);
    swprintf(tempbuf,400,L"당신의 %ls은(는) %ls을(를) 배울 수 있습니다", pokemon->pokename, newSkill.skillName);
    serialScreen(line++,ST,tempbuf,NORMAL);
    wmemset(tempbuf,0,400);
    swprintf(tempbuf,400,L"%ls-> 데미지: %d, 타입: %ls, 스킬 갯수: %d", newSkill.skillName,newSkill.skillAttack,newSkill.type,newSkill.skillAvail);
    serialScreen(line++,ST,tempbuf,NORMAL);   
    sel = arrowFunc(0, line++,ST,ED,2,L"배운다",L"배우지 않는다");
    pokemon->point += 1;
    if(sel == 1) {
        free(arg2);
        return ;
    }
    if(pokemon->skillLearned >= 4) {
        serialScreen(line++,ST,L"스킬 중 하나를 버려야 합니다",NORMAL);
        line++;
        sel2 = arrowFunc(0, line++,ST,ED,4, pokemon->skillarr[0].skillName, pokemon->skillarr[1].skillName, pokemon->skillarr[2].skillName, pokemon->skillarr[3].skillName);
        line += 1;
        pokemon->skillLearned -= 1;
        mvprintw(line++,ST,"%ls --> %ls", pokemon->skillarr[sel2].skillName, newSkill.skillName);
    }   
    else sel2 = pokemon->skillLearned;
    memcpy(&(pokemon->skillarr[sel2]),&newSkill,sizeof(Skill));
    pokemon->skillLearned += 1;
    pthread_create(&tid,NULL,singleSound,arg2);
    while(arg2->x != 1) {}
    serialScreen(line++,ST,L"새로운 스킬을 배웠습니다 !!",NORMAL);
    napms(300);
    free(tempbuf);
    free(arg2);

}

void initPokemon(PokeData * pokemon, PokeList * list, int sel) {
    pokemon->pokedata = *searchData(list,sel);
    pokemon->skillLearned = 0;
    pokemon->level = 0;
    pokemon->usedHealth = 0;
    pokemon->point = 0;
    pokemon->fullHealth = pokemon->pokedata.health + (pokemon->level/4) * 10;
    memset(pokemon->skillarr,0,sizeof(Skill)*4);
    wmemset(pokemon->pokename,0,40);
    wcscpy(pokemon->pokename,pokemon->pokedata.pokename);
}

void setPokemon(PokeData * pokemon, PokeList * list, int sel, int learned, int curlevel, int *arr) {
    pokemon->pokedata = *searchData(list,sel);
    pokemon->skillLearned = learned;
    pokemon->level = curlevel;

    pokemon->usedHealth = 0;
    pokemon->fullHealth = pokemon->pokedata.health + (pokemon->level/4) * 10;
    wmemset(pokemon->pokename,0,40);
    wcscpy(pokemon->pokename,pokemon->pokedata.pokename);
    int s = 0;
    Skill *skills = readSkills();
    int max = -1;
    // for(int i = 0 ; i < 4; i++) {
    //     mvprintw(line++, ST, "%d",arr[i]);
    // }

    for(int i = 0 ; i < 4 ; i++) {
        if(arr[i] == 0) continue;
        pokemon->skillarr[s++] = skills[arr[i] - 1];
        if(max < skills[arr[i] - 1].idenNum) max = skills[arr[i] - 1].idenNum;
    }
    // for(int i = 0 ; i < s ; i++){
    //     mvprintw(line++,ST,"%ls",pokemon->skillarr[i].skillName);
    // }

    for(int i = 0 ; i < pokemon->pokedata.skillNum ;i++){
        if(max == pokemon->pokedata.totalskill[i]){
            pokemon->point = i + 1;
        }
    }
    free(skills);
}

PokeData * setRandomPoke(PokeList * list, int idenNum0, int idenNum1, int skillnum, int type) {
    PokeData * rand = (PokeData *)malloc(sizeof(PokeData));
    int idenNum = randomInRange(idenNum0, idenNum1);
    PokeGlobalData * data = searchData(list,idenNum);
    int arr[12] = {0,};
    int arr2[10] = {0,};
    int a = 0;
    int b = data->skillNum - 1;
    if(!type) b -= 3;     // 높은 스킬 제한 (스테이지 낮을때);
    srand(time(NULL));
    for(int i = 0 ; i < skillnum ; i++){ 
        a = randomInRange(0,b);
        while(arr[a] >= 1) {
            a = randomInRange(0,b);
        }
        arr[a] += 1;
    }
    a = 0;
    for(int i = 0 ; i < 12 ; i++){
        if(!arr[i]) continue;
        arr2[a++] = searchData(list,idenNum)->totalskill[i];
    }
    setPokemon(rand,list,idenNum,skillnum,data->level,arr2);
    return rand;
}

int throwBall(PokeData* poke, int type) {

    int p = 0;
    if(poke->level > 25) p = 15;
    if(poke->level <= 25) p = 12;
    if(poke->level <= 20) p = 9;
    if(poke->level <= 15) p = 6;
    if(poke->level <= 10) p = 3;
    if(poke->level <= 5) p = 0;

    double hp = (80-p) * ((double)poke->usedHealth / poke->fullHealth);
    int caught = 0;
    // 5렙기준 반피(1/2)  몬스터볼일때 확률 33퍼 20/60, 슈퍼볼 35/60, 하이퍼볼  5/6
    // 5렙기준 딸피(9/10) 몬스터볼일떄 확률 52/60, 슈퍼볼 67/60, 하이퍼볼 72/60
    int pro = randomInRange(0,60);    
    switch (type)
    {
    case 0:
        caught = (pro + hp >= 80)? 1 : 0;
        break;
    case 1:
        caught = (pro + hp >= 65)? 1 : 0;
        break;
    case 2:
        caught = (pro + hp >= 50)? 1 : 0;
        break;
    default:
        break;
    }
    return caught;
}
// 내가 사용한 스킬이 매우 효과적이면 2 보통이면 1 아니면 0 을 반환 
int useSkill(Skill *skill, PokeData * enemy) {
    if(skill->skillAvail <= skill->skillUsed) return -1;
    wchar_t myType[50];
    wchar_t enemType[50];

    skill->skillUsed += 1;
    wcscpy(myType,skill->type);
    wcscpy(enemType,enemy->pokedata.type);
    int type1,type2;

    // 풀 < 불 < 물 < 전기 < 돌  << 노말 
    if(!wcscmp(myType,L"grass")) type1 = 0;
    if(!wcscmp(enemType,L"grass")) type2 = 0;
    if(!wcscmp(myType,L"fire")) type1 = 1;
    if(!wcscmp(enemType,L"fire")) type2 = 1;
    if(!wcscmp(myType,L"water")) type1 = 2;
    if(!wcscmp(enemType,L"water")) type2 = 2;
    if(!wcscmp(myType,L"electric")) type1 = 3;
    if(!wcscmp(enemType,L"electric")) type2 = 3;
    if(!wcscmp(myType,L"rock")) type1 = 4;
    if(!wcscmp(enemType,L"rock")) type2 = 4;
    if(!wcscmp(myType,L"normal")) type1 = 10;
    if(!wcscmp(enemType,L"normal")) type2 = 10;
    // mvprintw(line++,ST,"me: %d they: %d",type1,type2);
    if(type1 == 10 || type2 == 10) return 2;        // normal은 그냥 일반공격 
    if((type1 + 1) % 5  == type2) return 0;         // 최약공
    if((type1 - 1 + 5) % 5 == type2) return 4;      // 최강공
    if((type1 + 2) % 5  == type2) return 1;         // 약공
    if((type1 - 2 + 5) % 5 == type2) return 3;      // 강공
    if(type1 == type2) return 2;                    // 일반공
    // 속성 검사로직 
}

void skillSound(Skill *skill, struct foo * arg2) {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  
    arg2->x = 0;
    arg2->speed = 1.5f;
    wchar_t myType[50];
    wcscpy(myType,skill->type);
    int randNum = randomInRange(0,1);
    if(!wcscmp(myType,L"grass")){
        if(randNum)strcpy(arg2->file,GRASSSOUND1);
        else strcpy(arg2->file,GRASSSOUND2);
    }
    if(!wcscmp(myType,L"fire")){
        if(randNum)strcpy(arg2->file,FIRESOUND1);
        else strcpy(arg2->file,FIRESOUND2);
    }
    if(!wcscmp(myType,L"water")){
        if(randNum)strcpy(arg2->file,WATERSOUND1);
        else strcpy(arg2->file,WATERSOUND2);
    }
    if(!wcscmp(myType,L"rock")){
        if(randNum)strcpy(arg2->file,ROCKSOUND1);
        else strcpy(arg2->file,ROCKSOUND2);
    }
    if(!wcscmp(myType,L"electric")) {
        if(randNum)strcpy(arg2->file,THUNDERSOUND1);
        else strcpy(arg2->file,THUNDERSOUND2);
    }
    if(!wcscmp(myType,L"normal")) {
        if(randNum)strcpy(arg2->file,NORMALSOUND1);
        else strcpy(arg2->file,NORMALSOUND2);
    }
    pthread_create(&tid,&attr,singleSound,arg2);
    while(arg2->x != 10) {}
}
int catchPokemmon(Userdata *user, PokeData *poke, int innersel, struct foo * arg2) {
    pthread_t tid2;                       
    wchar_t * tempbuf = (wchar_t *)malloc(sizeof(wchar_t) * 200);
    wmemset(tempbuf,0,200);
    wchar_t *q = (innersel > 1)? L"하이퍼 볼" : (innersel > 0)? L"슈퍼 볼" : L"몬스터 볼";
    int interface = LINES / 11.0 * 9;

    swprintf(tempbuf,200,L"%ls을 던졌다 !!", q);
    arg2->x = 0;
    arg2->speed = 1.5f;
    strcpy(arg2->file,THROWBALLSOUND);
    pthread_create(&tid2,NULL,singleSound,arg2);
    serialScreen(line++,ST,tempbuf,NORMAL);

    int pro = throwBall(poke, innersel);
    while(arg2->x != 10) {}  // 끝날때까지 기다린느거임 (싱크 맞추는게 아님)
    arg2->x = 0;
    arg2->speed = 1.5f;
    strcpy(arg2->file,WAITINGCAUGHTSOUND);
    pthread_create(&tid2,NULL,singleSound,arg2);
    serialScreen(line,ST,L"....",NORMAL);

    while(arg2->x != 10) { // 끝날때까지 기다리는거임 
        blinkString(L"....",line++);
    }
    if(pro){
        int sel2 = 4;
        arg2->x = 0;
        arg2->speed = 1.5f;
        strcpy(arg2->file,CAUGHTSOUND);
        pthread_create(&tid2,NULL,singleSound,arg2);
        while(arg2->x != 10) {}

        arg2->x = 0;
        arg2->speed = 1.5f;
        strcpy(arg2->file,SUCCESSCAUGHTSOUND);
        line = interface + 2;
        dynamicClear(0,interface + 2,COLS -1 -line);
        pthread_create(&tid2,NULL,singleSound,arg2);
        while(arg2->x != 1) {}

        serialScreen(line++,ST,L"성공적으로 잡았습니다.",NORMAL);
        visualgetch();
        if(user->pokenum >= 4){
            serialScreen(line++, ST, L"이미 네마리의 포켓몬을 지니고 있어 더 지닐수 없습니다",NORMAL);
            serialScreen(line++, ST, L"한마리를 놓아주겠습니까??",NORMAL);
            sel2 = arrowFunc(0,line++,ST,ED,5,user->own[0].pokename,user->own[1].pokename,user->own[2].pokename,user->own[3].pokename,L"아니요");
            dynamicClear(0,interface + 2,COLS -1 -line);
            if(sel2 != 4){
                wmemset(tempbuf,0,200);
                swprintf(tempbuf,200,L"잘가!!  %ls!!", user->own[sel2].pokename);
                serialScreen(line++, ST, tempbuf, NORMAL);
            }
            else {
                serialScreen(line++,ST,L"잡은 포켓몬을 놓아주었다..",NORMAL);
                free(tempbuf);
                return 2;
            }
        }
        else sel2 = user->pokenum;
        wmemset(tempbuf,0,200);
        swprintf(tempbuf,200,L"%ls의 이름을 지어주시겠습니까?(y/n)", poke->pokename);
        serialScreen(line++,ST,tempbuf,NORMAL);

        int sel3 = arrowFunc(0,line++,ST+10,ED/2,2,L"YES",L"NO");
        if(sel3 == 0){
            wchar_t * q = (wchar_t *)inputlenRange();
            wcscpy(poke->pokename,q);
        }
        dynamicClear(0,interface + 2,COLS -1 -line);
        learnSkill(poke);
        user->own[sel2] = *poke;
        wmemset(tempbuf,0,200);
        swprintf(tempbuf,200,L"%ls!! 넌 내꺼야!", user->own[sel2].pokename);
        serialScreen(line++,ST,tempbuf,NORMAL);


        visualgetch();
        free(tempbuf);
        return 1;
    }
    else {
        arg2->x = 0;
        arg2->speed = 2.0f;
        strcpy(arg2->file,POPPOKEMONSOUND);
        q = (innersel > 1)? L"하이퍼 볼" : (innersel > 0)? L"슈퍼 볼" : L"몬스터 볼";
        wmemset(tempbuf,0,200);
        swprintf(tempbuf,200,L"%ls이(가) %ls에서 빠져나왔다 !!", poke->pokename, q);
        pthread_create(&tid2,NULL,singleSound,arg2);
        while(arg2->x != 1) {}
        serialScreen(line++,ST,tempbuf,NORMAL);
        visualgetch();
        free(tempbuf);
        return 0;
    }

}

void randomCry(struct foo * arg2) {
    pthread_t tid;
    arg2->x = 0;
    arg2->speed = 0.1f;
    int sel = randomInRange(1,12);
    switch(sel) {
        case 1:
            strcpy(arg2->file,CRYSOUND1);
            break;
        case 2:
            strcpy(arg2->file,CRYSOUND2);
            break;
        case 3:
            strcpy(arg2->file,CRYSOUND3);
            break;
        case 4:
            strcpy(arg2->file,CRYSOUND4);
            break;
        case 5:
            strcpy(arg2->file,CRYSOUND5);
            break;
        case 6:
            strcpy(arg2->file,CRYSOUND6);
            break;
        case 7:
            strcpy(arg2->file,CRYSOUND7);
            break;
        case 8:
            strcpy(arg2->file,CRYSOUND8);
            break;
        case 9:
            strcpy(arg2->file,CRYSOUND9);
            break;
        case 10:
            strcpy(arg2->file,CRYSOUND10);
            break;
        case 11:
            strcpy(arg2->file,CRYSOUND11);
            break;
        case 12:
            strcpy(arg2->file,CRYSOUND12);
            break;
        default:
            break;
    }
    pthread_create(&tid,NULL,singleSound,arg2);
    while(arg2->x != 1) {}
}

void randomCity(struct foo * arg) {
    arg->x = 10;
    pthread_t tid;
    int a = randomInRange(1,3);
    arg->speed = 2.0f;
    arg->x = 0;
    switch(a) {
        case 1:
            strcpy(arg->file,CITY1SOUND);
            break;
        case 2:
            strcpy(arg->file,CITY2SOUND);
            break;
        case 3:
            strcpy(arg->file,CITY3SOUND);
            break;
        default:
            break;
    }
    pthread_create(&tid,NULL,loopSound,arg);
    return ;
}


int story0(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2) {
    int type = 0;
    PokeData * enemy = setRandomPoke(list,0,5,2,0);
    user->progress = 0;
    // user->item.ball3 = 10;
    type = battlePage(user,NULL,enemy,arg,arg2);
    if(type == 1) user->progress = 1;
    free(enemy);
    return type;
}
int story1(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2) {
    int type = 0;

    Userdata * user2 = (Userdata *)malloc(sizeof(Userdata));
    PokeData * enemy1 = setRandomPoke(list,6,11,3,0);
    PokeData * enemy2 = setRandomPoke(list,6,11,3,0);
    user2->own[0] = *enemy1;
    user2->own[1] = *enemy2;
    user2->pokenum = 2;
    user2->userPoke = 0;
    user->progress = 1;
    // user->item.ball3 = 10;
    type = battlePage(user,user2,NULL,arg,arg2);
    if(type == 1) user->progress = 2;
    free(user2);
    free(enemy1);
    free(enemy2);
    return type;
}
int story2(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2) {
    clear();
    int type = 0;

    Userdata * user2 = (Userdata *)malloc(sizeof(Userdata));
    PokeData * enemy1 = setRandomPoke(list,12,16,3,0);
    PokeData * enemy2 = setRandomPoke(list,12,16,3,0);
    PokeData * enemy3 = setRandomPoke(list,12,16,3,0);
    user2->own[0] = *enemy1;
    user2->own[1] = *enemy2;
    user2->own[2] = *enemy3;
    user2->pokenum = 3;
    user2->userPoke = 0;
    user->progress = 2;
    // user->item.ball3 = 10;
    type = battlePage(user,user2,NULL,arg,arg2);
    if(type == 1) user->progress = 3;
    free(user2);
    free(enemy1);
    free(enemy2);
    free(enemy3);
    return type;
}
int story3(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2) {
    clear();
    int type = 0;

    Userdata * user2 = (Userdata *)malloc(sizeof(Userdata));
    PokeData * enemy1 = setRandomPoke(list,17,21,3,1);
    PokeData * enemy2 = setRandomPoke(list,17,21,3,1);
    PokeData * enemy3 = setRandomPoke(list,17,21,3,1);
    user2->own[0] = *enemy1;
    user2->own[1] = *enemy2;
    user2->own[2] = *enemy3;
    user2->pokenum = 3;
    user2->userPoke = 0;
    user->progress = 3;
    // user->item.ball3 = 10;
    type = battlePage(user,user2,NULL,arg,arg2);
    if(type == 1) user->progress = 4;
    free(user2);
    free(enemy1);
    free(enemy2);
    free(enemy3);
    return type;
}
int story4(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2) {
    clear();
    int type = 0;

    Userdata * user2 = (Userdata *)malloc(sizeof(Userdata));
    PokeData * enemy1 = setRandomPoke(list,22,22,4,1);
    PokeData * enemy2 = setRandomPoke(list,23,23,4,1);
    user2->own[0] = *enemy1;
    user2->own[1] = *enemy2;
    user2->pokenum = 2;
    user2->userPoke = 0;
    user->progress = 4;
    // user->item.ball3 = 10;
    type = battlePage(user,user2,NULL,arg,arg2);
    if(type == 1) {
        user->progress = 5;
        endCredit(list,arg);
    }
    
    free(user2);
    free(enemy1);
    free(enemy2);
    return type;
}
int story5(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2) {
    clear();
    int type = 0;

    PokeData * enemy = setRandomPoke(list,24,24,4,1);
    user->progress = 5;
    type = battlePage(user,NULL,enemy,arg,arg2);
    if(type == 1) user->progress = 6;
    free(enemy);
    return type;


}
int story6(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2) {
    clear();
    int type = 0;

    PokeData * enemy = setRandomPoke(list,25,25,4,1);
    user->progress = 6;
    type = battlePage(user,NULL,enemy,arg,arg2);
    if(type == 1) user->progress = 6;
    free(enemy);
    return type;
}


void mainStoryLine(Userdata* user, PokeList * list, struct foo * arg,struct foo* arg2) {
    serialScreen(line++, ST, L"진행 상황 로드 중 ... ", NORMAL);
    visualgetch();
    int sel = 0;
    int stop = 0;
    int progressNum = user->progress;
    if(progressNum != 0) {
        while(1){
            line= 3;
            serialScreen(line++,ST,L"진행한 챕터 중 하나를 골라주세요",NORMAL);
            line++;
            sel = arrowFunc(1,line++,ST,ED,7,L"Progrees0",L"Progrees1",L"Progrees2",L"Progrees3",L"Progrees4",L"Progrees5",L"Progrees6");
            dynamicClear(1,line,12);
            if(sel <= progressNum) break;
            blinkString(L"진행한 챕터 중 하나를 골라주세요",3);
        }
    }

    switch(sel) {
        case 0:
            stop = menuPage(user,list,story0,arg, arg2);
            if(stop) return ;
        case 1:
            stop = menuPage(user,list,story1,arg, arg2);
            if(stop) return ;
        case 2:
            stop = menuPage(user,list,story2,arg, arg2);
            if(stop) return ;
        case 3:
            stop = menuPage(user,list,story3,arg, arg2);
            if(stop) return ;
        case 4:
            stop = menuPage(user,list,story4,arg, arg2);
            if(stop) return ;
        case 5: 
            stop = menuPage(user,list,story5,arg, arg2);
            if(stop) return ;
        case 6: 
            stop = menuPage(user,list,story6,arg, arg2);
            if(stop) return ;
        default:
            break;
    }
    return ;
}

