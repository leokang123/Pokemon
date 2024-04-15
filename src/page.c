#include "everyheader.h"

int startPage (struct foo * arg) {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    arg->x = 0;
    arg->speed = 0.6f;
    strcpy(arg->file,"../assets/effectSound/etc/filmcount.wav");
    pthread_create(&tid,NULL,(void *)loopSound,arg);

    sleep(1);
    line = pokeImage1(++line,(ST+ED)/2 - 34,28);                         // knockon 로고 
    sleep(2);

    dynamicClear(1,0,LINES);
    line = LINES/2 - 10;
    sleep(1);
    line = pokeImage1(++line,(ST+ED)/2 - 34,29);                         // 만든이 
    sleep(2);

    dynamicClear(1,0,LINES);
    line = LINES/2 - 10;
    sleep(1);
    line = pokeImage1(line,(ST+ED)/2 - 34,27);                           // 닌텐도 
    arg->x = 10;                                                       // 노래 종료

    sleep(2);
    arg->x = 0;
    arg->speed = 2.1f;
    strcpy(arg->file,TITLESOUND);
    pthread_create(&tid,NULL,(void *)loopSound,arg);
    dynamicClear(3,line,LINES);
    line = 2;
    sleep(1);


    line = pokeImage1(line,(ST+ED)/2 - 34,26);
    sleep(1);
    line += 1;
    line = pokeImage1(line,(ST+ED)/2 - 34,24);
    sleep(1);
    mvprintw(line++,ST,"Press any key to continue...");
    refresh();

    flushinp(); 
    getch();
    // sleep(2);
    dynamicClear(3,LINES-1,10); // LINE-1 부터 15줄 위로 옮기기
    // sleep(1);
    line += 2;
    int sel = arrowFunc(0,line,ST,ED,2,L"새로하기",L"이어하기");
    dynamicClear(3,LINES-1,LINES); // 다 위로 올림 
    clear();
    // arg->x = 10;
    return sel;
}

Userdata * loadUserPage(struct foo * arg) {
    // pthread_t tid;
    // pthread_attr_t attr;
    // pthread_attr_init(&attr);
    // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    wchar_t * tempbuf = (wchar_t *)malloc(sizeof(wchar_t) * 200);
    /*
        돈 아이템 포켓몬배열 포켓몬수 진행도 이름 설정해야함 
    */
    wchar_t * q;
    Userdata * userData = (Userdata *) malloc(sizeof(Userdata));
    int a = 1;
    while(a){
        line = 2;
        clear();
        serialScreen(line++,ST, L"아이디를 입력해주세요\n",NORMAL);
        refresh();
        q = (wchar_t *)inputlenRange();
        userData = readUserData(q);
        if(userData != NULL) a = 0;
        else {
            serialScreen(line++,ST, L"사용자를 찾을 수 없습니다\n",NORMAL);
            visualgetch();
        }
    }
    swprintf(tempbuf, 200,L"이름: %ls, 자금: %d, 진행 상황: %d",(userData->username), userData->balance, userData->progress);
    serialScreen(line++,ST,tempbuf,NORMAL);
    napms(500);

    free(tempbuf);
    return userData;
}

Userdata * makeUserPage(PokeList * list, struct foo * arg) {
    // pthread_t tid;
    // pthread_attr_t attr;
    // pthread_attr_init(&attr);
    // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // PokeList * list = makeLink();
    wchar_t * tempbuf = (wchar_t *)malloc(sizeof(wchar_t) * 200);
    wmemset(tempbuf,0,200);
    /*
        돈 아이템 포켓몬배열 포켓몬수 진행도 이름 설정해야함 
    */
    Userdata * newUser = (Userdata *) malloc(sizeof(Userdata));
    wchar_t * q;
    int a = 1;
    while(a){
        line = 2; // 2가 초기세팅 
        clear();
        serialScreen(line++,ST, L"아이디를 입력해주세요",NORMAL);
        refresh();
        q = (wchar_t *)inputlenRange();
        wcscpy(newUser->username, q);
        wcscpy(tempbuf, newUser->username);
        newUser->balance = 10000;
        refresh();
        newUser->pokenum = 0;
        newUser->progress = 0;
        memset(&(newUser->item),0,sizeof(Item));
        a = saveUserData(newUser, NEW);
    }
    serialScreen(line++,ST, L"당신께 1만원을 지급했습니다",NORMAL);
    // 일단 우려중이였던게 애초에 더미 데이터를 기반으로 짜다보니 일어나지 않을 상황에대해 걱정했음 
    // 애초에 처음부터 사용자생성하고 데이터를 축적하다보면 Userdata 구조체가 어떤멤버변수는 비어있고 이럴수가 없는데 
    // 비어있는 경우도 생각해서 짜다보니 뭔가 복잡해졌음 
    free(newUser);
    // Userdata * userdata;
    Userdata * userdata = readUserData(tempbuf);
    if(userdata == NULL) {
        printf("NULL\n");
        return NULL;
    }
    wmemset(tempbuf,0,200);
    swprintf(tempbuf,200,L"이름: %ls, 자금: %d, 진행 상황: %d",(userdata->username), userdata->balance, userdata->progress);
    serialScreen(line++,ST,tempbuf,NORMAL);
    // dynamicClear(3, line);
    PokeGlobalData * data[3];
    for(int i = 0 ; i < 3 ; i++) {
        data[i] = searchData(list,i); // 이미 리스트에서 할당한 주소만 가져오는거임 
    }
    wchar_t *tempbuf3[3];
    for(int i = 0 ; i < 3 ; i++){
        tempbuf3[i] = (wchar_t *)malloc(sizeof(wchar_t)* 100);
    }
    for(int i = 0 ; i < 3 ; i++){
        swprintf(tempbuf3[i],100,L"%d %ls %ls", data[i]->idenNum, (data[i]->pokename), (data[i]->type));
    }
    serialScreen(line++,ST,L"당신의 여행에 동행할 포케몬을 골라주세요",NORMAL);
    refresh();
    //getch() 갖다 버림  ㅈ같음 그냥
    // wchar_t ch[10];
    // wget_wstr(stdscr,ch);
    int sel = arrowFunc(0, line++,ST,ED,3,tempbuf3[0],tempbuf3[1],tempbuf3[2]);
    for(int i = 0 ; i < 3 ; i++){
        free(tempbuf3[i]);
    }
    line++;
    // 여기도 나중엔 이미 만들어놓은 값에서 주소만 가져오게 할수 있을거같음
    // 근데 일단은 더미 데이터를 활요해야해서 쩔수임
    PokeData * pokemon = &(userdata->own[0]);
    // memcpy((PokeGlobalData *)&(pokemon->pokedata),(PokeGlobalData *)searchData(list,sel),sizeof(PokeGlobalData));
    
    // Pokemon 정보 초기화 안해줬다가 segfault떄문에 3시간동안 고민함 반드시 초기화를 시켜주자 
    initPokemon(pokemon, list, sel);
    userdata->pokenum += 1;
    userdata->userPoke = 0;
    // setPokemon(pokemon, list, sel, 4, 60, (int[]){1, 3, 5, 7});
    pokeImage1(line++,50,pokemon->pokedata.idenNum);

    wmemset(tempbuf,0,200);
    swprintf(tempbuf,200,L"고른 포켓몬: %u %ls %ls", pokemon->pokedata.idenNum, (pokemon->pokedata.pokename), (pokemon->pokedata.type)); 
    serialScreen(line++,ST,tempbuf,NORMAL);
    free(tempbuf);
    mvprintw(line++,ST,"포켓몬 이름을 지으시겠습니까? (y/n)");
    refresh();
    
    sel = arrowFunc(0, line++,ST,ED,2,L"네",L"아니요");
    refresh();
    // line++; // 입력칸을 살리기 위해 있어야댐 ( 입력이랑 line++는 한세트 )
    mvprintw(line++,ST,"%ls",pokemon->pokename);
    refresh();
    if(sel == 0) {
        mvprintw(line++, ST,"포켓몬 이름을 입력해주세요");
        refresh();
        q = inputlenRange();
        wcscpy(pokemon->pokename,q);
        mvprintw(line++,ST,"당신의 %ls 이름은 %ls 입니다", (pokemon->pokedata.pokename), (pokemon->pokename));
        refresh();
    }

    sleep(1);
    line++;
    serialScreen(line++,ST,L"당신에게 몬스터볼 3개와 회복약 2개를 지급했습니다",NORMAL);
    userdata->item.heal += 2;
    userdata->item.ball1 += 3;
    mvprintw(line++,ST,"[몬스터 볼 x %d, 슈퍼 볼 x %d, 하이퍼 볼 x %d, 회복약 x %d]",userdata->item.ball1, userdata->item.ball2, userdata->item.ball3, userdata->item.heal);
    refresh();
    visualgetch();
    levelup(&(userdata->own[0]));
    // dynamicClear(3, LINES - 1,LINES);
    // 배경음악은 루프를 돌고 있기 떄문에 적절한 위치에서 종료를 시켜주고 프로새스를 닫아야 에러가 안남 
    // arg->x = 10;
    // mvprintw(line++,ST,"111111%ls %ls", userdata->own[0].pokename, userdata->username);
    refresh();
    serialScreen(line++,ST,L"현재까지의 내용을 저장합니다 ...",NORMAL);
    saveUserData(userdata,EDIT);
    napms(500);
    return userdata;
    // endRoutine(line);
}

int battlePage(Userdata * user, Userdata* opp, PokeData * enemy, struct foo * arg, struct foo * arg2) {
    clear();
    int arr[4] = {0,};  // 참여한 포켓몬
    pthread_t tid, tid2;
    // struct foo * arg2 = (struct foo *)malloc(sizeof(struct foo));
    arg->x = 10; // 전까지 나오던 배경음악 종료 
    usleep(1000);   // 일단 해줘봐 

    // 배경음악 초기화 
    arg->x = 0;
    strcpy(arg->file,BATTLESOUND);
    arg->speed = 2.2f;

    if(user->progress == 4 || user->progress == 5 ||user->progress == 6)
        strcpy(arg->file,FINALBATTLESOUND);

    wchar_t pokebuf[4][200] = {0,};
    pthread_create(&tid,NULL,(void *)singleSound,arg);
    while(arg->x != 1) {}
    randomScreen();       
    
    // 맨 처음 출전하는 포켓몬 인덱스 
    int randNum = 0;
    // 승패 (0 짐 1 이김 2 도망침)
    int win = 0;
    // 기절한 포켓몬
    int retire = 0;
    int retire2 = 0;
    // 선택지 디폴트 
    int sel = 0;
    int len1 = 0, len2 = 0;
    int innersel = 0;
    int prev1 = 0;
    int prev2 = 0;
    int turn = 1;
    struct battleInter my;
    struct battleInter their;
    line = 2;
   if (opp != NULL) enemy = &(opp->own[opp->userPoke]);

    int interface = LINES / 11.0 * 9;
    my.nameLine = interface - 18;
    my.barLine = interface - 17;
    my.healthLine = interface - 16;

    their.nameLine = line + 2;
    their.barLine = line + 3;
    their.healthLine = line + 4;
    int fshow = 1; 
INIT1:
   staticClear(2,32,ED-60,COLS-1); 
   staticClear(2,10,ST,ED);
    len1 = pokeImage2(2,ED-50,enemy->pokedata.idenNum);
    // mvprintw(line++,ST,"ENEM LEN: %d",len1); // check
INIT2:
    if(fshow){
        staticClear(interface -20,interface,ST,ED-ST/2); 
        len2 = pokeImage1(interface - 20,ST,user->own[user->userPoke].pokedata.idenNum);
        fshow = 0;
    }
    // mvprintw(line++,ST,"HERE1");  
    // refresh();
    line = 2;
    interface = LINES / 11.0 * 9;
    borderLine(line++, ED - len1 - 42, ED - len1 - 2);
    borderLine(their.healthLine + 3, ED - len1 - 42, ED - len1 - 2);
    their.interCol = ED - len1 - 40;
    mvprintw(their.nameLine,their.interCol - 2,"%*s",37,"");
    mvprintw(their.nameLine,their.interCol,"%ls  Lv%d  %ls",enemy->pokename, enemy->level, enemy->pokedata.type);

    borderLine(interface - 20 , ST + len2 + 2, ST + len2 + 42);
    borderLine(my.healthLine + 3, ST + len2 + 2, ST + len2 + 42);
    my.interCol = ST + len2 + 4;
    mvprintw(my.nameLine,my.interCol - 2,"%*s",37,"");
    mvprintw(my.nameLine,my.interCol,"%ls  Lv%d  %ls",user->own[user->userPoke].pokename, user->own[user->userPoke].level, user->own[user->userPoke].pokedata.type);
    refresh();
    // 여기서부터 루프 돌면 될듯 
    arr[user->userPoke] = 1;

    wchar_t tempbuf[100] = {0,};
    PokeData * curPokemon = &(user->own[user->userPoke]);
    randomCry(arg2);
FIRST:
    while(1){
        int healthLeft1 = enemy->usedHealth / (enemy->fullHealth / 25);
        if(healthLeft1 >= 25 ) healthLeft1 = 25;
        move(their.barLine,their.interCol);
        for(int i = 0 ; i < 25 - healthLeft1  ; i++){
            addch(':');
            refresh();
        }
        if(prev1 != healthLeft1){
            for(int i = their.interCol + 25 - prev1; i >= their.interCol + 25 - healthLeft1; i--){
                move(their.barLine,i);
                addch(' ');
                refresh();
                napms(100);
                if(i == their.interCol) break;
            }
        }
        int opnum = 1;
        if(opp != NULL) opnum = opp->pokenum;
        prev1 = healthLeft1;
        mvprintw(their.healthLine,their.interCol , "                 ");
        mvprintw(their.healthLine,their.interCol + 2,"%d / %d", enemy->fullHealth - enemy->usedHealth, enemy->fullHealth);
        mvprintw(their.healthLine + 1,their.interCol + 2, "          Pokemon Left: %d", opnum- retire2);
        int healthLeft2 = curPokemon->usedHealth / (curPokemon->fullHealth / 25);
        if(healthLeft2 >= 25 ) healthLeft2 = 25;
        move(my.barLine,my.interCol);
        for(int i = 0 ; i < 25 - healthLeft2 ; i++){
            addch(':');
            refresh();
        }
        if(prev2 != healthLeft2){
            for(int i = my.interCol + 25 - prev2 ; i >= my.interCol + 25 - healthLeft2; i--){
                move(my.barLine,i);
                addch(' ');
                refresh();
                napms(100);
                if(i == my.interCol) break;
            }
        }
        refresh();
        prev2 = healthLeft2;
        mvprintw(my.healthLine,my.interCol , "                 ");
        mvprintw(my.healthLine,my.interCol + 2,"%d / %d", curPokemon->fullHealth - curPokemon->usedHealth, curPokemon->fullHealth);
        mvprintw(my.healthLine + 1,my.interCol + 2, "          Pokemon Left: %d", user->pokenum - retire);
        // 포획해도 이 조건으로 빠지게 하자 (이겼을때))
        if (enemy->usedHealth >= enemy->fullHealth){
            retire2 += 1;
            randomCry(arg2);
            if(opp == NULL ||( opp->pokenum == retire2)) {
                win = 1;
                break;
            }
            swprintf(tempbuf,100,L"(적) %ls가 기절했다",enemy->pokename);
            serialScreen(line++,ST,tempbuf,NORMAL);
            wmemset(tempbuf,0,100);
            visualgetch();
            swprintf(tempbuf,100,L"(적) 돌어와 %ls!!",enemy->pokename);
            serialScreen(line++,ST,tempbuf,NORMAL);

            while(enemy->usedHealth >= enemy->fullHealth){
                opp->userPoke = (opp->userPoke + 1) % opnum;
                enemy = &(opp->own[opp->userPoke]);
            }

            wmemset(tempbuf,0,100);
            swprintf(tempbuf,100,L"(적) 가랏 %ls!!",opp->own[opp->userPoke].pokename);
            serialScreen(line++,ST,tempbuf,NORMAL);
            dynamicClear(interface-20,ST,20);

            visualgetch();
            turn = !turn;
            goto INIT1;
        }
        // (도망쳤을떄)
        if(win == 2) break;
        if(curPokemon->usedHealth >= curPokemon->fullHealth) {
            retire += 1;
            randomCry(arg2);
            if(user->pokenum == retire) {
                win = 0;
                break;
            }
            swprintf(tempbuf,100,L"%ls가 기절했다",user->own[user->userPoke].pokename);
            serialScreen(line++,ST,tempbuf,NORMAL);
            wmemset(tempbuf,0,100);
            visualgetch();

            swprintf(tempbuf,100,L"돌어와 %ls!!",user->own[user->userPoke].pokename);
            serialScreen(line++,ST,tempbuf,NORMAL);

            while(user->own[user->userPoke].usedHealth >= user->own[user->userPoke].fullHealth)
                user->userPoke = (user->userPoke + 1) % user->pokenum;

            wmemset(tempbuf,0,100);
            swprintf(tempbuf,100,L"가랏 %ls!!",user->own[user->userPoke].pokename);
            serialScreen(line++,ST,tempbuf,NORMAL);
            dynamicClear(interface-20,ST,20);

            visualgetch();
            turn = !turn;
            fshow = 1;
            goto INIT2;
        }
        
        borderLine(interface + 1,ST,ED);
BACK:   

        line = interface + 2;
        dynamicClear(0,line,COLS-1-line+1);
        wchar_t skillbuf[4][200] = {0,};
        wmemset(tempbuf,0,100);
        if(turn){
            for(int i = 0 ; i < curPokemon->skillLearned; i++) {
                swprintf(skillbuf[i],200,L"스킬이름 : %ls (%ls)  공격력: %d (%d/%d)",curPokemon->skillarr[i].skillName, curPokemon->skillarr[i].type, curPokemon->skillarr[i].skillAttack, curPokemon->skillarr[i].skillAvail - curPokemon->skillarr[i].skillUsed, curPokemon->skillarr[i].skillAvail);
            }
            swprintf(tempbuf,100,L"앗 %ls이 나타났다",enemy->pokedata.pokename);
            serialScreen(line++,ST,tempbuf,NORMAL);
            wmemset(tempbuf,0,100);
            serialScreen(line++,ST,L"무엇을 할까?",NORMAL);
            switch(sel = arrowFunc(0,line++,ST,ED/2,4,L"공격 ",L"가방열기",L"교체하기",L"도망치기")) {
                case 0:
                    dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
                    innersel = arrowFunc(1,line++,ST,ED,5,skillbuf[0], skillbuf[1], skillbuf[2], skillbuf[3] , L"뒤로가기");
                    if(innersel >= 0 && innersel <= 3) {
                        dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
                        line = interface + 2;
                        if(innersel > curPokemon->skillLearned - 1){
                            serialScreen(line++,ST,L"스킬이 존재하지 않는다",NORMAL);
                            curs_set(1);
                            flushinp();
                            getch();
                            curs_set(0);
                            goto BACK;
                        }
                        int epro = randomInRange(0,100);
                        int effect = useSkill(&(curPokemon->skillarr[innersel]), enemy);
                        swprintf(tempbuf,100,L"%ls %ls!!!",curPokemon->pokename,curPokemon->skillarr[innersel].skillName);
                        serialScreen(line++,ST,tempbuf,NORMAL);
                        wmemset(tempbuf,0,100);
                        visualgetch();
                        skillSound(&(curPokemon->skillarr[innersel]),arg2);
                        if(epro < 13) {
                            serialScreen(line++,ST,L"적 포켓몬이 공격을 회피했다!",NORMAL);
                            turn = !turn;
                            visualgetch();
                            dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
                            continue;
                        }
                        if(effect == 4) {
                            serialScreen(line++,ST,L"공격이 매우 효과적이었다!!",NORMAL);
                            enemy->usedHealth +=  curPokemon->skillarr[innersel].skillAttack * 1.3 + randomInRange(5,20);
                        }
                        if(effect == 3) {
                            serialScreen(line++,ST,L"공격이 효과적이었다!!",NORMAL);
                            enemy->usedHealth +=  curPokemon->skillarr[innersel].skillAttack * 1.2 + randomInRange(0,20);
                        }
                        if(effect == 2){
                            serialScreen(line++,ST,L"공격이 들어갔다!!",NORMAL);
                            enemy->usedHealth +=  curPokemon->skillarr[innersel].skillAttack * 1.0 + randomInRange(0,15);
                        }
                        if(effect == 1){
                            serialScreen(line++,ST,L"공격효과가 미비하다..",NORMAL);
                            enemy->usedHealth +=  curPokemon->skillarr[innersel].skillAttack * 0.8 + randomInRange(0,10);
                        }
                        if(effect == 0){
                            serialScreen(line++,ST,L"공격효과가 매우 미비하다..",NORMAL);
                            enemy->usedHealth +=  curPokemon->skillarr[innersel].skillAttack * 0.7 + randomInRange(0,5);
                        }
                        if(effect < 0) {
                            serialScreen(line++,ST,L"스킬 가능횟수를 초과했다..",NORMAL);
                            curs_set(1);
                            flushinp();
                            getch();
                            curs_set(0);
                            goto BACK;
                        }
                    }
                    if(innersel == 4) goto BACK;
                    break;
                case 1:
                    swprintf(skillbuf[0], 200, L"몬스터 볼 x %d", user->item.ball1);
                    swprintf(skillbuf[1], 200, L"슈퍼 볼 x %d", user->item.ball2);
                    swprintf(skillbuf[2], 200, L"하이퍼 볼 x %d", user->item.ball3);
                    swprintf(skillbuf[3], 200, L"회복약 x %d", user->item.heal);
                    dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
                    innersel = arrowFunc(1,line++,ST,ED,5,skillbuf[0], skillbuf[1], skillbuf[2], skillbuf[3], L"뒤로가기");
                    dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
                    if(innersel >= 0 && innersel <=2) {
                        if(innersel == 0) {
                            if(user->item.ball1 <= 0){
                                serialScreen(line++,ST,L"몬스터 볼이 부족합니다",NORMAL);
                                visualgetch();
                                goto BACK;
                            }
                            user->item.ball1 -= 1;
                        }
                        if(innersel == 1) {
                            if(user->item.ball2 <= 0){
                                serialScreen(line++,ST,L"슈퍼 볼이 부족합니다",NORMAL);
                                visualgetch();
                                goto BACK;
                            }
                            user->item.ball2 -= 1;
                        }
                        if(innersel == 2) {
                            if(user->item.ball3 <= 0){
                                serialScreen(line++,ST,L"하이퍼 볼이 부족합니다",NORMAL);
                                visualgetch();
                                goto BACK;
                            }
                            user->item.ball3 -= 1;
                        }                                                
                        dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
                        int catch = catchPokemmon(user,enemy,innersel,arg2);
                        if(catch) {
                            enemy->usedHealth = enemy->fullHealth;
                            if(catch == 1 && user->pokenum < 4)user->pokenum += 1;
                        }
                    }
                    if(innersel == 3) {
                        if(user->item.heal <= 0) {
                            serialScreen(line++,ST,L"회복약이 부족합니다",NORMAL);
                            visualgetch();
                            goto BACK;
                        }
                        user->item.heal -= 1;
                        arg2->x = 0;
                        strcpy(arg2->file,RESTOREHEALTHSOUND);
                        arg2->speed = 1.5f;
                        pthread_create(&tid2,NULL,singleSound,arg2);
                        while(arg2->x != 1) {}
                        serialScreen(line++,ST,L"회복약을 사용했습니다 ",NORMAL);
                        int pro= randomInRange(10,40);
                        user->own[user->userPoke].usedHealth -= (60 + pro);
                        if(user->own[user->userPoke].usedHealth < 0) user->own[user->userPoke].usedHealth = 0;
                        turn = !turn;
                        visualgetch();
                        goto FIRST;
                    }
                    if(innersel == 4) goto BACK;
                    break;
                case 2:
                    for(int i = 0 ; i < user->pokenum ;i++) {
                        swprintf(pokebuf[i],200,L"Lv%d %ls (%ls) %d/%d", user->own[i].level, user->own[i].pokename, user->own[i].pokedata.type,user->own[i].fullHealth - user->own[i].usedHealth, user->own[i].fullHealth);
                    }
                    dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
                    int innersel = arrowFunc(1,line++,ST,ED,5,pokebuf[0],pokebuf[1],pokebuf[2],pokebuf[3],L"뒤로가기");
                    dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
                    if(innersel == 4) goto BACK;
                    if(innersel > user->pokenum - 1) {
                        serialScreen(line++,ST,L"해당 포켓몬은 존재하지 않습니다",NORMAL);
                        visualgetch();
                        goto BACK;
                    }
                    if(innersel == user->userPoke) {
                        serialScreen(line++,ST,L"올바르지 않은 대상입니다",NORMAL);
                        visualgetch();
                        goto BACK;
                    }
                    if(user->own[innersel].usedHealth >= user->own[innersel].fullHealth){
                        serialScreen(line++,ST,L"더이상 전투에 참여할 수 없습니다",NORMAL);
                        visualgetch();
                        goto BACK;
                    }
                    swprintf(tempbuf,100,L"돌어와 %ls!!",user->own[user->userPoke].pokename);
                    serialScreen(line++,ST,tempbuf,NORMAL);
                    wmemset(tempbuf,0,100);
                    user->userPoke = innersel;
                    swprintf(tempbuf,100,L"가랏 %ls!!",user->own[user->userPoke].pokename);
                    serialScreen(line++,ST,tempbuf,NORMAL);
                    turn = !turn;
                    visualgetch();
                    fshow = 1;
                    goto INIT2;
                case 3:
                    dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
                    if((double)randomInRange(0,100) + 20 * ((double)enemy->usedHealth / enemy->fullHealth) < 40) {
                        serialScreen(line++,ST,L"도망치는데 실패했다...",NORMAL);
                        visualgetch();
                        break;
                    }
                    arg->x = 10;
                    win = 2;
                    break;
                default:
                    break;
            }
            turn = !turn;
            sleep(1);
        }
        else {
            int epro = randomInRange(0,100);
            int ensel = randomInRange(1,enemy->skillLearned) - 1;
            // mvprintw(line++,ST,"HERE4 %ls",enemy->skillarr[ensel].skillName);
            int effect = useSkill(&(enemy->skillarr[ensel]), curPokemon);
            swprintf(tempbuf, 100, L"%ls이(가) %ls(%ls)를 사용했다!!", enemy->pokename, enemy->skillarr[ensel].skillName, enemy->skillarr[ensel].type);
            serialScreen(line++,ST,tempbuf,NORMAL);
            wmemset(tempbuf,0,100);
            visualgetch();
            // mvprintw(line++,ST,"HERE5 %d", ensel);  
            refresh();
            skillSound(&(enemy->skillarr[ensel]),arg2);
            // mvprintw(line++,ST,"HERE6");  
            refresh();
            if(epro < 10) {
                serialScreen(line++,ST,L"나의 포켓몬이 공격을 회피했다!",NORMAL);
                turn = !turn;
                visualgetch();
                dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
                continue;
            }
            if(effect == 4) {
                serialScreen(line++,ST,L"공격이 매우 효과적이었다!!",NORMAL);
                curPokemon->usedHealth +=  enemy->skillarr[ensel].skillAttack * 1.3 + randomInRange(5,20);
            }
            if(effect == 3) {
                serialScreen(line++,ST,L"공격이 효과적이었다!!",NORMAL);
                curPokemon->usedHealth +=  enemy->skillarr[ensel].skillAttack * 1.2 + randomInRange(0,20);
            }
            if(effect == 2){
                serialScreen(line++,ST,L"공격이 들어갔다!!",NORMAL);
                curPokemon->usedHealth +=  enemy->skillarr[ensel].skillAttack * 1.0 + randomInRange(0,15);
            }
            if(effect == 1){
                serialScreen(line++,ST,L"공격효과가 미비하다..",NORMAL);
                curPokemon->usedHealth +=  enemy->skillarr[ensel].skillAttack * 0.8 + randomInRange(0,10);
            }
            if(effect == 0){
                serialScreen(line++,ST,L"공격효과가 매우 미비하다..",NORMAL);
                curPokemon->usedHealth +=  enemy->skillarr[ensel].skillAttack * 0.7 + randomInRange(0,5);
            }
            if(effect < 0) {
                serialScreen(line++,ST,L"스킬 가능횟수를 초과했다..",NORMAL);
                visualgetch();
            }
            turn = !turn;
            sleep(1);
        }
        dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
    }
    line = interface + 2;
    dynamicClear(0,interface + 2,LINES-1-(interface + 2)+1);
    int endType = 0;
    switch(win) {
        case 0:
            arg->x = 10;
            user->balance -= 1500;
            if(user->balance < 0) user->balance = 0;
            serialScreen(line++,ST,L"나의 모든 포켓몬이 쓰러졌다..",NORMAL);
            visualgetch();
            serialScreen(line++,ST,L"돈을 1500원 잃었다..",NORMAL);
            visualgetch();
            serialScreen(line++,ST,L"(포켓몬 센터로 이송된다)",NORMAL);
            arg2->x = 10;
            dynamicClear(1,2,LINES);
            endType = 0;
            break;
        case 1:
            arg->x = 10;
            randNum = randomInRange(500,3000);
            user->balance += 1000 + randNum;
            usleep(1000);
            arg->x = 0;
            strcpy(arg->file,VICTORYSOUND);
            arg->speed = 2.5f;
            pthread_create(&tid2,NULL,loopSound,arg);
            wmemset(tempbuf,0,100);
            swprintf(tempbuf,100,L"%ls이(가) 쓰러졌다 !!",enemy->pokename);
            serialScreen(line++,ST,tempbuf,NORMAL);
            visualgetch();
            wmemset(tempbuf,0,100);
            swprintf(tempbuf,100,L"%d원을 얻었다 !!",1000 + randNum);
            serialScreen(line++,ST,tempbuf,NORMAL);
            visualgetch();
            int a = 0;
            
            while(a < 4){
                if(arr[user->userPoke]) {
                    levelup(&(user->own[user->userPoke]));
                }

                user->userPoke = (user->userPoke + 1) % 4;
                a++;
            }
            endType = 1;
            dynamicClear(1,2,LINES);
            clear();
            break;
        case 2:
            arg->x = 0;
            arg->speed = 2.5f;
            strcpy(arg->file,FLEESOUND);
            pthread_create(&tid,NULL,singleSound,arg);
            user->balance -= 1000;
            if(user->balance < 0) user->balance = 0;
            serialScreen(line++,ST,L"성공적으로 도망쳤다",NORMAL);
            visualgetch();
            serialScreen(line++,ST,L"1000원을 잃었다..",NORMAL);
            visualgetch();
            arg2->x = 10;
            endType = 2;
            dynamicClear(1,2,LINES);
            break;
        default:
            break;
    }
    
    arg->x = 10;
    return endType;

}

void healCenter(Userdata * user,struct foo * arg,struct foo * arg2) {
    pthread_t tid,tid2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int sel = 0;
    arg2->x = 0;
    arg2->speed = 2.3f;
    strcpy(arg2->file,HEALSOUND);

    arg->x = 10;
    napms(100);
    arg->x = 0;
    arg->speed = 2.2f;
    strcpy(arg->file,POKECENTERSOUND);
    pthread_create(&tid,&attr,loopSound,arg);
    clear();
    mvprintw(2, ST, "[포켓몬 센터]");
    line = 4;
    refresh();
    while(arg->x != 1){}
    serialScreen(line++,ST,L"포켓몬 센터에 오신걸 환영합니다",NORMAL);
    visualgetch();
    line++;
    serialScreen(line++,ST,L"포켓몬들을 치료하시겠습니까? ",NORMAL);
    line++;
    sel = arrowFunc(0,line++,ST+4,(ST+ED)/4+4,2,L"예",L"아니요");
    line++;
    if(sel == 1){
        serialScreen(line++,ST,L"안녕히 가세요",NORMAL);
        visualgetch();
        arg->x = 10;
        return ;
    }
    refresh();
    for(int i = 0 ; i < user->pokenum; i++){
        user->own[i].usedHealth = 0;
        mvprintw(line++,ST,"%ls 치료완료",user->own[i].pokename);
        mvprintw(line++,ST,"---------------------");
        refresh();
        for(int j = 0 ; j < user->own[i].skillLearned ; j++){
            user->own[i].skillarr[j].skillUsed = 0;
            mvprintw(line++,ST,"%ls 준비완료",user->own[i].skillarr[j].skillName);
            refresh();
        }
        mvprintw(line++,ST,"%*s",30,"");
    }
    refresh();
    arg->x = 10;
    pthread_create(&tid2,NULL,singleSound,arg2);
    while(arg2->x != 1) {}
    sleep(2);
    serialScreen(line++,ST,L"치료가 완료되었습니다 !!",NORMAL);
    visualgetch();
    napms(100);
    arg2->x = 10;
    return ;
}

void pokeShop(Userdata * user,struct foo * arg, struct foo * arg2) {
    pthread_t tid,tid2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    arg->x = 10;
    napms(100);
    arg->x = 0;
    arg->speed = 2.1f;
    strcpy(arg->file,POKESHOPSOUND);
    pthread_create(&tid,&attr,loopSound,arg);

    arg2->x = 0;
    arg2->speed = 1.5f;
    strcpy(arg2->file,GETITEMSOUND);

    int arr[4] = {200,500,1500,3000};
    int sel = 0;
    long num = 0;
    wchar_t tempbuf[200] = {0,};
BACK:
    clear();
    mvprintw(2, ST, "[상점]");
    line = 4;
    mvprintw(line,ST+30,"내 잔고: %d 원", user->balance);
    refresh();
    wmemset(tempbuf,0,200);
    sel = arrowFunc(1,line++,ST,ED,5,L"회복약(200원)",L"몬스터볼(500원)",L"슈퍼볼(1500원)",L"하이퍼볼(3000원)",L"나가기");
    line += 5;
    if(sel == 4) {
        line += 2;
        serialScreen(line++, ST,L"안녕히 가세요",NORMAL);
        visualgetch();
        arg->x = 10;
        return ;
    }
    serialScreen(line,ST,L"살 갯수(1~99,뒤로가기(0)):",NORMAL);
    wmemset(tempbuf,0,200);
    wget_wstr(stdscr,tempbuf);
    num = wcstol(tempbuf, NULL, 10);
    line++;
    if(num == 0) goto BACK;
    if(num <= -1 || num > 99) {
        serialScreen(line++,ST,L"유효하지 않은 입력",NORMAL);
        visualgetch();
        goto BACK;
    }
    if(user->balance - num * arr[sel] < 0) {
        serialScreen(line++,ST,L"잔액이 부족합니다",NORMAL);
        visualgetch();
        goto BACK;
    }
    user->balance -= num * arr[sel];

    pthread_create(&tid2,&attr,singleSound,arg2);
    while(arg2->x != 1) {}
    switch(sel) {
        case 0:
            user->item.heal += num;
            break;
        case 1:
            user->item.ball1 += num;
            break;
        case 2:
            user->item.ball2 += num;
            break;
        case 3:
            user->item.ball3 += num;
            break;
    }
    serialScreen(line++,ST,L"구매 완료!",NORMAL);
    mvprintw(line++,ST,"남은 잔고: %d", user->balance);
    visualgetch();
    goto BACK;
}   

void showPokeIden(PokeList * list) {
    int sel = 0, sel2 = 0;
    int num = 0;
    int page = 0;
    Skill * skills = readSkills();
    wchar_t tempbuf[5][200] = {0,};
    
    refresh();
    for(int i = 0 ; i < 5; i++) {
        PokeGlobalData * data = searchData(list,i);
        swprintf(tempbuf[i],100,L"%d) %ls (%ls)",data->idenNum,data->pokename,data->type);
    }
BACK:
    clear();
    mvprintw(4,ED - 50, "[상성]");
    mvprintw(6,ED - 50, "grass < fire < water < electric < rock < grass ...");
    mvprintw(8,ED - 50,"normal타입은 모두 일반 공격 ");
    mvprintw(9,ED-50,"상성간 두 칸차이는 조금의 우위, 한칸 차이는 큰 우위를 지닌다");

    mvprintw(2, ST, "[포켓몬 도감]");
    line = 4;
    mvprintw(line+8,ST+10,"%d 페이지", page+1);
    refresh();
    sel = arrowFunc(1,line,ST,ED,8,tempbuf[0],tempbuf[1],tempbuf[2],tempbuf[3],tempbuf[4], L"전페이지",L"다음페이지",L"나가기");
    if(sel >= 0 && sel <= 4) {
        num = page * 5 + sel;
        PokeGlobalData * data = searchData(list,num);
        line = pokeImage1(line++,ST-1,num);
        line = 5;
        mvprintw(line++,ST + 70,"이름: %ls / 타입: %ls",data->pokename,data->type);
        line++;
        mvprintw(line++,ST+ 70,"<스킬>");
        line++;
        refresh();
        for(int i = 0 ; i < data->skillNum;i++){
            Skill skdata = skills[data->totalskill[i] - 1];
            mvprintw(line++,ST+ 70,"%ls (%ls) / 공격력: %d 횟수: %d",skdata.skillName,skdata.type,skdata.skillAttack, skdata.skillAvail);
        }
        refresh();
        visualgetch();
        goto BACK;
    }
    if(sel == 5) {
        if(page == 0){
            serialScreen(line++ + 10,ST,L"뒤로 갈 페이지가 없습니다",NORMAL);
            visualgetch();
            goto BACK;
        }
        page -= 1;
        for(int i = 0 ; i < 5; i++) {
            PokeGlobalData * data = searchData(list,5*page+i);
            wmemset(tempbuf[i],0,200);
            swprintf(tempbuf[i],200,L"%d) %ls (%ls)",data->idenNum,data->pokename,data->type);
        }
        goto BACK;
    }
    if(sel == 6) {
        if(page == 4){
            serialScreen(line++ + 10,ST,L"앞으로 갈 페이지가 없습니다",NORMAL);
            visualgetch();
            goto BACK;
        }
        page += 1;
        for(int i = 0 ; i < 5; i++) {
            PokeGlobalData * data = searchData(list,5*page+i);
            wmemset(tempbuf[i],0,200);
            swprintf(tempbuf[i],200,L"%d) %ls (%ls)",data->idenNum,data->pokename,data->type);
        }
        goto BACK;
    }
    if(sel == 7) {
        free(skills);
        return ;
    }
}

int menuPage(Userdata * user, PokeList * list, int (*ftr)(Userdata *, PokeList*, struct foo*, struct foo*), struct foo * arg, struct foo * arg2){
    // attron(WA_BOLD);
    arg->x = 10;
BACK:
    clear();
    mvprintw(10,ST,"%ls가 현재까지 진행한 상황: %d",user->username, user->progress);
    pokeImage1(2, (ST+ED)/2 - 35, 28);
    if(arg->x != 1) randomCity(arg);
    line = 15;
    int type = 0;
    int sel2 = 0;
    refresh();
    int sel = arrowFunc(0,line++,ST,ED,7,L"모험", L"상점", L"센터", L"도감",L"출전순서",L"저장", L"나가기");
    switch (sel) {
        case 0:
            line++;
            serialScreen(line++,ST,L"다음 도전자와 상대하겠습니까?",NORMAL);
            visualgetch();
            line++;
            if(user->progress == 4) {
                serialScreen(line++,ST,L"마지막 전투입니다",NORMAL);
            }
            if(user->progress == 5 || user->progress == 6) {
                serialScreen(line++,ST,L"굉장히 강한 적이 기다리고 있습니다",NORMAL);
            }
            line++;
            sel2 = arrowFunc(0,line++,ST,ED,2,L"예", L"아니요");
            if(sel2) goto BACK;
            type = ftr(user,list,arg,arg2);
            if(type == 2) goto BACK;  // 도망 
            if(type == 1) {
                // attroff(WA_BOLD);
                return 0;
                }   // 승리 
            if(type == 0) {           // 다 기절 
                healCenter(user,arg,arg2);
                goto BACK;
            }
            break;
        case 1:
            pokeShop(user,arg,arg2);
            goto BACK;
        case 2:
            healCenter(user,arg,arg2);
            goto BACK;
        case 3: 
            showPokeIden(list);
            goto BACK;
        case 4:
            line++;
            serialScreen(line++,ST,L"어떤 포켓몬을 먼저 출전시키겠습니까??",NORMAL);
            sel2 = arrowFunc(1,line++,ST,ED,4,user->own[0].pokedata.pokename,user->own[1].pokedata.pokename,user->own[2].pokedata.pokename,user->own[3].pokedata.pokename);
            line += 4;
            if(sel2 >= user->pokenum) {
                serialScreen(line++,ST,L"유효하지 않은 선택입니다",NORMAL);
                visualgetch();
                goto BACK;
            }
            user->userPoke = sel2;
            mvprintw(line++,ST,"%ls이(가) 선택되었습니다.", user->own[sel2].pokedata.pokename);
            refresh();
            visualgetch();
            goto BACK;
        case 5:
            saveUserData(user,EDIT);
            line += 2;
            serialScreen(line++, ST,L"사용자 정보가 저장되었습니다",NORMAL);
            line++;
            mvprintw(line++,ST,"[사용자 정보]");
            mvprintw(line++,ST,"아이디: %ls, 진행도: %d",user->username, user->progress);
            move(line++,ST);
            printw("포켓몬: ");
            for(int i = 0 ; i < user->pokenum;i++){
                printw("%ls(%ls) ",user->own[i].pokename,user->own[i].pokedata.pokename);
            }
            refresh();
            visualgetch();
            goto BACK;
        case 6:
            saveUserData(user,EDIT);
            line += 2;
            serialScreen(line++, ST,L"사용자 정보가 저장되었습니다",NORMAL);
            serialScreen(line++, ST,L"게임을 종료합니다",NORMAL);
            visualgetch();
            return 1;
        default:
            goto BACK;
    }

}

void endCredit(PokeList * list, struct foo * arg) {
    PokeGlobalData * data;
    int num = list->num;
    line = LINES / 2 - 10;
    int col = (ST + ED) / 2 - 27;
    serialScreen(line++, ST, L"정해놓은 모든 포켓몬을 잡았습니다...",SLOW);
    visualgetch();
    serialScreen(line++,ST,L"감사합니다",SLOW);
    visualgetch();
    clear();
    line -= 2;
    arg->x = 10;
    napms(200);
    pthread_t tid;
    arg->speed = 2.1f;
    strcpy(arg->file,ENDINGSOUND);
    pthread_create(&tid,NULL,singleSound,arg);
    while(arg->x != 1){}
    line = pokeImage1(line,col-10,30);

    napms(1000);
    flushinp();
    getch();
    dynamicClear(3,line,LINES);
    clear();
    for(int i = 0 ; i < list->num - 1; i++) {
        line = LINES / 2 - 20;
        data = searchData(list,i);

        line = pokeImage1(line,col,i);       
        line +=  2;
        mvprintw(line++,col-5,"도감번호: %d 이름: %ls 타입: %ls", data->idenNum, data->pokename, data->type);
        refresh();
        napms(500);
        dynamicClear(1,2,LINES-1);
    }
    line = 0;
    data = searchData(list,list->num-1);
    line += pokeImage1(line,col,data->idenNum);
    line++;
    mvprintw(line++,col,"도감번호: %d 이름: %ls 타입: %ls", data->idenNum, data->pokename, data->type);
    refresh();
    napms(300);
    dynamicClear(1,2,LINES-1);
    clear();
    visualgetch();
}