#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUF_SIZE 50

/*
스킬을 어떻게 구현할지 좀 고민임 
포켓몬 정보txt에서 각각 불러올지 스킬데이터 txt를 따로 불러와서 인데스 번호만 
포켓몬 구조체에 넣어줄지 
후자로 하면 좋은점은 포켓몬 정보 txt에서도 그냥 번호만 적어줘서 레벨마다 배울수 있는 스킬을 정해줄수
있고 유저 정보에도 데리고 있는 포켓몬이 지니고 있는 스킬을 번호로만 전달해도 된다 

*/

typedef struct {
    unsigned int idenNum;
    char type[10];
    char skillName[20];
    unsigned int skillAttack;
    unsigned int skillAvail;        // 스킬 원래 갯수; 남은 갯수는 함수 내부에서 처리할거같음 
} Skill;

typedef struct {
    unsigned int idenNum;        // 포켓몬 도감번호 
    unsigned int level;          // 포켓몬 현재 레벨 
    unsigned int health;         // 포켓몬 피 
    // unsigned int power;       // 포켓몬 최소공격력 그냥 공격력은 스킬공 + 레벨로 측정 
    char pokename[20];           // 포켓몬 이름 
    char type[10];               // 포켓몬 타입 
    unsigned int skillCurNum;    // 현재 배운 스킬 갯수 
    Skill curarr[4];             // 포켓몬 현재 스킬
} PokeData;

/* 
 암만 생각해봐도 도감에 들어갈 포켓몬 정보랑 사용자가 사용할 포켓몬 정보를 
 같은 구조체를 쓰면 먼가 꼬임 (특히 스킬부분)
*/
typedef struct {
    unsigned int idenNum;        // 포켓몬 도감번호 
    unsigned int level;          // 포켓몬 최소 레벨 
    unsigned int health;         // 포켓몬 최소피 
    char pokename[20];           // 포켓몬 이름 
    char type[10];               // 포켓몬 타입 
    unsigned int skillNum;       // 현재 배운 총 갯수 
    int skillarr[10];            // 포켓몬 총 스킬
    // 도감에서는 인트형으로 스킬도감번호를 저장하고 PokeData 불러올때 스킬데이터랑 매핑시킨다 
} PokeGlobalData;

typedef struct _pokeNode{
    PokeGlobalData data;
    struct _pokeNode *next;
    // struct _pokeNode *prev; 필요한가  걍 오름차순으로 정렬할거니까 필요없을듯 
} PokeNode;


typedef struct {
    unsigned int heal;
    unsigned int ball1;
    unsigned int ball2;
    unsigned int ball3;
    unsigned int drug;
} Item;

typedef struct {
    char username[20];
    unsigned int pokenum;
    unsigned int balance;
    unsigned int progress;
    PokeData own[6];
    Item item;
} Userdata;

// 연결리스트를 도감번호만큼 이동해서 노드주소를 반환한다 
PokeNode * getLinkedElem(int idenNum);

const char * getUserData(const char *inputName) {

    // 할당해제하기 귀찮아서 이렇게 씀
    static char userData[500];         // 찾은 유저 정보 
    char *findPointer = NULL;

    char nameBuf[BUF_SIZE] = "<::";    // 파일 읽기 시작/끝 포맷 
    char realName[50] = {0,};          // 실제 이름  ->  입력한 이름과 비교해야함 

    char findBuf[BUF_SIZE] = {0,};     // 버퍼
    int readSize = 0 ;                 

    FILE * data = fopen("../../data/userData/userdata.txt","r");
    if(data == NULL) perror("open error");

    strcat(nameBuf,inputName);
    
    // fread는 '\0'를 안붙어서 나온다 
    while((readSize = fread(findBuf, 1, BUF_SIZE, data)) > 0) {

        // fread는 따로 문자열 종료 처리를 안해준다 
        findBuf[readSize] = '\0'; // 중요
        if((findPointer = strstr(findBuf, nameBuf)) != NULL) {

            // 유저 실제 이름 추출 
            int i = 0;
            while(*(findPointer + i) != '\n') {
                realName[i] = *(findPointer + i);
                i++;
            }
            realName[i] = '\0';
            if(!strcmp(realName,nameBuf)) break;
            findPointer = NULL;
        }
    }
    // 예외처리 
    if (findPointer == NULL) {
        printf("cannot find name\n");
        return NULL;
    }
    // 이름 찾은 첫번째부분으로 파일 포인터 이동 
    fseek(data, (long)(findBuf)-(long)(findPointer)-readSize, SEEK_CUR);

    // <::{username} 뺴고 담기 
    fgets(findBuf,BUF_SIZE-1,data);
    memset(findBuf, 0 , BUF_SIZE);
    // fgets는 '\0'가 붙어서 나온다 
    while(fgets(findBuf,BUF_SIZE-1,data) != NULL) {
        
        findPointer = strstr(findBuf,"<::END");
        if (findPointer != NULL) break;
        strcat(userData,findBuf);
    }
    // printf("Data after %s\n%s\n",nameBuf, userData);
    return userData;
}

char * setUserData() {

}

int * skillParse(char * str) {
    int i = 0;
    char *q, *p;
    int * arr;
    int num;
    p = str;
    q = strsep(&p, ":");
    q = strsep(&p, "/");
    // q 에 스킬 전체 갯수 저장됌 
    num = atoi(q);
    arr = (int * ) malloc(sizeof(int) * num);
    // 스킬목록 + '/'이 q에 저장됌 
    while(num--) {
        int a; 
        q = strsep(&p, " \t/");
        arr[i++] = atoi(q);
        // printf("%d\n",arr[i-1]);
    }
    return arr;
}

// 0렙, 3렙,6렙,9렙,12렙... 레벨에서 3을 나눈 값의 인덱스 스킬을 배울 수 있다 
void setPokeSkills(PokeData *data, int rmskill) {
    if(!rmskill) return;
    
    char buffer[50] = {0,};
    int * arr;
    int idenNum = data->idenNum;
    int num = data->skillCurNum;
    int readLine = idenNum;
    int i = 0;
    PokeGlobalData pokeData = getLinkedElem(idenNum)->data;

    // 이번에 추가될수도있는 포켓몬스킬의 인덱스 번호 
    int skill = data->curarr[num-1].idenNum + 1;
    int newSkill = 0;
    // 포켓몬 목록에서 skill번째 인덱스 스킬식별자를 불러온다 
    // 근데 사실이것도 이미 연결리스트를 만들어놨을거고 
    // 연결리스트에서 pokeData.idenNum을 참조해서 skilldata를 가져오는게 맞다 
    FILE * skillData = fopen("../../data/pokeData/pokemon.txt","r");
    fgets(buffer,BUF_SIZE,skillData);
    readLine = data->idenNum;// atoi(buffer);

    while(readLine--) {
        // 도감번호 포켓몬 타입 최소레벨 150:5/1 3 6 9 11/(스킬목록) 
        fgets(buffer,BUF_SIZE,skillData);  
    }
    printf("%s\n", buffer);

    // 스킬파싱 
    // 근데 pokeData.skillarr 여기에 이미 저장이 되어있어야함 
    // 그니까 아래에 적은 코드는 아마 처음 도감만드는 함수에 필요할듯 
    arr = skillParse(buffer);
    newSkill = (rmskill)? arr[skill] : 0;

    for(i = rmskill-1 ; i < num ; i++){
        // rmskill = 2 이면 인덱스 1 부터 옆으로 스킬식별자를 왼쪽으로 민다(오름차순 정렬)
        data->curarr[i].idenNum = data->curarr[i+1].idenNum;
    }
    data->curarr[i].idenNum = newSkill;
    // 만들어놓은 포켓몬 도감 연결리스트 안에있는 도감 정보로 전체 스킬 정보를 읽어온다 
    // 예를 들어 머 연결리스트의 num번째 인자를 받는 함수가 getLinkedElem(num) 이면 
    free(arr);
    return;
}
int main(void) {
    const char *userData = getUserData("leokang");
    printf("%s\n", userData);
    Skill skill[4] ={};
}