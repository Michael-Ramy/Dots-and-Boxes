#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include "conio2.h"

int x,y,z,k,counter=0,doubleBoxes,remainingLines,flag,pvc2,VIP,limits,uncoun=0,recoun=0,load_save=0,fload,time_diff,n_load,ticks;
char *grid[12][12]= {{"  "," 1 "," 2 "," 3 "," 4 "," 5 "," 6 "," 7 "," 8 "," 9 ","10 "," 11 "},
                    {"1  ","o","     ","o","     ","o","     ","o","     ","o","     ","o"},
                    {"2  "," ","     "," ","     "," ","     "," ","     "," ","     "," "},
                    {"3  ","o","     ","o","     ","o","     ","o","     ","o","     ","o"},
                    {"4  "," ","     "," ","     "," ","     "," ","     "," ","     "," "},
                    {"5  ","o","     ","o","     ","o","     ","o","     ","o","     ","o"},
                    {"6  "," ","     "," ","     "," ","     "," ","     "," ","     "," "},
                    {"7  ","o","     ","o","     ","o","     ","o","     ","o","     ","o"},
                    {"8  "," ","     "," ","     "," ","     "," ","     "," ","     "," "},
                    {"9  ","o","     ","o","     ","o","     ","o","     ","o","     ","o"},
                    {"10 "," ","     "," ","     "," ","     "," ","     "," ","     "," "},
                    {"11 ","o","     ","o","     ","o","     ","o","     ","o","     ","o"}
                    };
int check[12][12]= {{1,1,1,1,1,1,1,1,1,1,1,1},{1,1,0,1,0,1,0,1,0,1,0,1},{1,0,0,0,0,0,0,0,0,0,0,0},
                   {1,1,0,1,0,1,0,1,0,1,0,1},{1,0,0,0,0,0,0,0,0,0,0,0},{1,1,0,1,0,1,0,1,0,1,0,1},
                   {1,0,0,0,0,0,0,0,0,0,0,0},{1,1,0,1,0,1,0,1,0,1,0,1},{1,0,0,0,0,0,0,0,0,0,0,0},
                   {1,1,0,1,0,1,0,1,0,1,0,1},{1,0,0,0,0,0,0,0,0,0,0,0},{1,1,0,1,0,1,0,1,0,1,0,1}
                   };
typedef struct{
int po1;
int po2;
int seq;
}point;
point pointss[61];

typedef struct{
char name[10];
int score;
int move;
}player;
player p1,p2;
time_t start_t,end_t;

    FILE * f1;
    FILE * f2;
    FILE * f3;

    char n[]="aaaaa";

void mainMenu();
void game();
void selectSize();
void mode();
void names();
void takeNames(char name1[]);
void printat();
void player_moves();
void printarray();
void take_check_put();
void takePoints(char n[],int m);
void putLines(int x,int y,int k);
void tick();
void checkBox(int i,int j);
void checkBoxes();
void calculateScore();
void computerTurn();
void aicomputer();
void goxy(int m,int n);
void cleanInput(int m,int n);
void undo();
void redo();
void resetGame();
void ranking();
void endGame();
void save();
void load();
void item_save();
void item_load();

int main()
{
    mainMenu();

 }

void game()
{
    time(&start_t);
    while (remainingLines>=0)
    {
        printat();
        if (remainingLines==0)
        {
            if (load_save==1){
                if (n_load==1){
                    f1=fopen("save1.txt","w");
                    fprintf(f1,"");
                    fclose(f1);
                }
                else if (n_load==2){
                    f2=fopen("save2.txt","w");
                    fprintf(f2,"");
                    fclose(f2);
                }
                else if (n_load==3){
                    f3=fopen("save3.txt","w");
                    fprintf(f3,"");
                    fclose(f3);
                }
            }
            break;
        }
        take_check_put();
        checkBoxes();
        calculateScore();
    }
}
void printat(){
    int i=0;
    if(VIP==1){
        i=-6;
    }
        goxy(0,1+i);
        printf("Score :");
        goxy(0,2+i);
        printf("Moves :");
        textcolor(9);
        goxy(10,0+i);
        printf("%s",p1.name);
        goxy(13,1+i);
        printf("%d",p1.score);
        goxy(13,2+i);
        printf("%d",p1.move);
        textcolor(12);
        goxy(20,0+i);
        printf("%s",p2.name);
        goxy(23,1+i);
        printf("%d",p2.score);
        goxy(23,2+i);
        printf("%d",p2.move);
        textcolor(7);
        printf("\n\nRemaining lines: %d\n",remainingLines);
        tick();
        player_moves();
        printarray();
        if(remainingLines!=0){
        if(VIP==1){
            i=12;
        }
        goxy(25+i,12-i/2);
        printf("Enter line's row and line's column");
        goxy(25+i,13-i/2);
        printf("'U' for undo & 'R' for redo");
        goxy(25+i,14-i/2);
        printf("'S' to save");
        goxy(25+i,15-i/2);
        printf("'ESC' to exit");
        goxy(0,17);
}}
void player_moves(){
            if (counter%2==0){
                    textcolor(9);
            printf("\t\n\n  %s",p1.name);
            printf("'s turn\n\n");
        }
        else{
                textcolor(12);
            printf("\t\n\n  %s's turn\n\n",p2.name);
        }
}
void printarray(){
    int i,j;
        for(i=0; i<=limits; i++)
        {
            for(j=0; j<=limits; j++)
            {
                if((check[i][j]==2||check[i][j]==4)){
                    if(check[i][j]==2){
                    textcolor(9);
                    printf("%c%c%c%c%c",219,219,219,219,219);
                }
                    else if(check[i][j]==4){
                    textcolor(12);
                    printf("%c%c%c%c%c",219,219,219,219,219);
                }}
                else if(i==pointss[uncoun-1].po1&&j==pointss[uncoun-1].po2){
                    textcolor(14);//to change the color of the last line put
                    printf("%s",grid[i][j]);
                }
                else{
                        textcolor(7);//light gray(white)
                printf("%s",grid[i][j]);}
            }
            printf("\n");
        }
}
void take_check_put(){
        flag=0;
        while (flag==0)
        {
            if (pvc2==1){
            if (counter%2==0){
                char n[]="aaaaa";
                    takePoints(n,0);
            if(n[0]==69){
                continue;
            }
            if(n[0]==66){
                continue;
            }
            if(n[1]==-35){
            x=n[0];
            }
            else{
            x=n[0]*10+n[1];}
            if(n[4]==-35){
            y=n[3];
            }
            else{
            y=n[3]*10+n[4];}}

            else aicomputer();}
            else{
            char n[]="aaaaa";
                    takePoints(n,0);
            if(n[0]==69){
                continue;
            }
            if(n[0]==66){
                continue;
            }
            if(n[1]==-35){
            x=n[0];
            }
            else{
            x=n[0]*10+n[1];}
            if(n[4]==-35){
            y=n[3];
            }
            else{
            y=n[3]*10+n[4];}
            }
            z=x+y;
            k=(z==3)||(z==5)||(z==7)||(z==9);
            if(VIP==1){
                k=k||(z==11)||(z==13)||(z==15)||(z==17)||(z==19)||(z==21);
            }
            k=k&&(x<=limits)&&(y<=limits);
            if (check[x][y]==1&&k)
            {
                cleanInput(0,17);
                printf("The line already exists,please pick another one\n");
                continue;
            }
            if (k==0){
                cleanInput(0,17);
                printf("Invalid line\n");
        }
        putLines(x,y,k);
                        }
}
void takePoints(char n[],int m){
   int f=0;
   if(m==5){
    while(n[m]!=-40||n[m]!=-35){
            cleanInput(m,18);
        n[m]=getche()-48;
        if(n[m]==-35){
        break;
        }
        else if(n[m]==-40){
            n[m-1]='a';
            takePoints(n,m-1);
            break;
        }
    }
   }
   else {
    if(m==2){
        printf(" ");
        m++;
    }
    if(m==0){
        n[m+1]='a';
        while (n[m]<0||n[m]>9){
            cleanInput(m,18);
        n[m]=getche()-48;
        if(n[m]==67){
            system("cls");
            save();
            exit(0);
        }
        if(n[m]==69&&(uncoun>0)){
            undo();
                while(counter%2==1&&pvc2){
                undo();}
            break;
        }
        if (n[m]==66&&(recoun>0)){
                redo();
                while(counter%2==1&&pvc2){
                    redo();
                }
                break;}
        if(n[m]==-21){
            exit(0);
        }
        }
        if(n[m+1]=='a'&&n[m]!=69&&n[m]!=66){
            takePoints(n,m+1);
        }}
       else if(m==3){
            n[m+1]='a';
            while (n[m]<0||n[m]>9){
            cleanInput(m,18);
        n[m]=getche()-48;
        if(n[m]==-21){
            exit(0);
        }
        if (n[m]==-40&&m!=0){
                if(m==3){
                    m--;
                }
                n[m-1]='a';
            takePoints(n,m-1);
            f=1;
        break;
        }
        }
        if(f==0){
        if(n[m+1]=='a'){
            takePoints(n,m+1);
        }}}
    else {
        n[m+1]='a';
        while ((n[m]<0||n[m]>9)&&(n[m]!=-35)){
            cleanInput(m,18);
        n[m]=getche()-48;
        if(n[m]==-21){
            exit(0);
        }
        if (n[m]==-40&&m!=0){
                n[m-1]='a';
            takePoints(n,m-1);
            f=1;
            break;
        }
        }
        if(f==0){
        if(n[m]==-35){
            goxy(m,18);
        }
        if(n[m+1]=='a'&&n[4]!=-35){
            takePoints(n,m+1);
        }
    }}}
}
void putLines(int x,int y,int k){
 if (y%2==0&&k)
            {
                grid[x][y]="-----";
                check[x][y]=1;
                if (counter%2==0){
                    p1.move++;
                }
                else {p2.move++;}
                counter++;
                remainingLines--;
                system("cls");
                flag=1;
                pointss[uncoun].po1=x;
                pointss[uncoun].po2=y;
                uncoun++;
                recoun=0;
                pointss[uncoun].seq=0;
            }
            else if (x%2==0&&k)
            {
                grid[x][y]="|";
                check[x][y]=1;
                if (counter%2==0){
                    p1.move++;
                }
                else {p2.move++;}
                counter++;
                remainingLines--;
                system("cls");
                flag=1;
                pointss[uncoun].po1=x;
                pointss[uncoun].po2=y;
                uncoun++;
                recoun=0;
                pointss[uncoun].seq=0;
            }
}
void tick(){
    time(&end_t);
    ticks=difftime(end_t, start_t);
    if (load_save==0){
        time_diff=difftime(end_t,start_t);
    }
    else if(load_save==1){
        ticks+=time_diff;
    }
    int sec=ticks%60;
    int min=ticks/60;
    printf("Time=%d:%s%d\n",min,(sec<10)? "0":"",sec);
    return;
}
void checkBox(int i,int j){
        if((counter-1)%2==0)
        {
            if (check[i-1][j]&&check[i][j-1]&&check[i+1][j]&&check[i][j+1]==1)
            {
                if(check[i][j]==0){
                check[i][j]=2;
                doubleBoxes++;}
            }
            else {check[i][j]=0;}
        }
        else if (check[i-1][j]&&check[i][j-1]&&check[i+1][j]&&check[i][j+1]==1)
            {
                if(check[i][j]==0){
                check[i][j]=4;
                doubleBoxes++;}
            }
        else {check[i][j]=0;}
}
void checkBoxes(){
        doubleBoxes=0;
        int m,n,b;
        if(VIP==0){
            b=4;
        }
        else {
            b=10;
        }
        for (m=2;m<=b;m=m+2){
            for(n=2;n<=b;n=n+2){
                checkBox(m,n);
            }
        }

    if (doubleBoxes!=0){
        counter++;
        pointss[uncoun].seq=1;
    }
}
void calculateScore(){
    int i,j;
    p1.score=0;
    p2.score=0;
    for(i=0;i<=limits;i++){
        for(j=0;j<=limits;j++){
            if(check[i][j]==2){
                p1.score++;
            }
            else if(check[i][j]==4){
                p2.score++;
            }
        }
    }
}
void aicomputer(){//our AI :)
        int m,n,b,aidone=0;
        if(VIP==0){
            b=4;
        }
        else {
            b=10;
        }
        for (m=2;m<=b;m=m+2){
            for(n=2;n<=b;n=n+2){
               if ((check[m-1][n]&&check[m][n-1]&&check[m+1][n])==1&&check[m][n]==0){
                x=m;
                y=n+1;
                aidone=1;
               }
               else if ((check[m-1][n]&&check[m][n-1]&&check[m][n+1])==1&&check[m][n]==0){
                x=m+1;
                y=n;
                aidone=1;
               }
               else if ((check[m-1][n]&&check[m][n+1]&&check[m+1][n])==1&&check[m][n]==0){
                x=m;
                y=n-1;
                aidone=1;
               }
               else if ((check[m][n-1]&&check[m+1][n]&&check[m][n+1])==1&&check[m][n]==0){
                x=m-1;
                y=n;
                aidone=1;
               }
            }
        }
    if(aidone==0){
        computerTurn();
    }
}
void computerTurn(){
    int b;
    if(VIP==0){
        b=5;
    }
    else{
        b=11;
    }
    x=(((rand()+time(0))%b)+1);
    y=(((rand()+time(0))%b)+1);
}
void undo(){
    remainingLines++;
    uncoun--;
    check[pointss[uncoun].po1][pointss[uncoun].po2]=0;
    if ((pointss[uncoun].po2)%2==0){
        grid[pointss[uncoun].po1][pointss[uncoun].po2]="     ";
    }
    else if((pointss[uncoun].po1)%2==0){
        grid[pointss[uncoun].po1][pointss[uncoun].po2]=" ";
    }
    if (pointss[uncoun+1].seq==1){
    if(counter%2==1){
        p2.move--;
    }
    if(counter%2==0){
        p1.move--;
    }
    }
    else {
        if(counter%2==1){
        p1.move--;
    }
    if(counter%2==0){
        p2.move--;
    }
    counter--;}
    system("cls");
    checkBoxes();
    calculateScore();
    printat();
    recoun++;
}
void redo(){
    remainingLines--;
    check[pointss[uncoun].po1][pointss[uncoun].po2]=1;
    if ((pointss[uncoun].po2)%2==0){
        grid[pointss[uncoun].po1][pointss[uncoun].po2]="-----";
    }
    else if((pointss[uncoun].po1)%2==0){
        grid[pointss[uncoun].po1][pointss[uncoun].po2]="|";
    }
    if (pointss[uncoun+1].seq==1){
    if(counter%2==1){
        p2.move++;
    }
    if(counter%2==0){
        p1.move++;
    }
    counter--;}
    else {
        if(counter%2==1){
        p2.move++;
    }
    if(counter%2==0){
        p1.move++;
       }
    counter++;}
    system("cls");
    uncoun++;
    checkBoxes();
    calculateScore();
    printat();
    recoun--;

}
void goxy(int m,int n){
    int b=0;
    if (VIP==1){
        b=6;
    }
COORD coord;
coord.X=m;
coord.Y=n+b;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void cleanInput(int m,int n){
int clearlines;
goxy(m,n);
for(clearlines=0;clearlines<5;clearlines++){
printf("                                                                                ");}
goxy(m,n);
}
void names(){
    int d=0;
if (pvc2==1){
        textcolor(9);
    printf("\nPlayer 1 name: ");
    strcpy(p1.name,"");
    takeNames(p1.name);
    p1.name[0]=toupper(p1.name[0]);
    strcpy(p2.name,"Computer");
}
else {
    while(d==0){
    textcolor(9);
    printf("\nPlayer 1 name: ");
    takeNames(p1.name);
    p1.name[0]=toupper(p1.name[0]);
    textcolor(12);
    printf("Player 2 name: ");
    takeNames(p2.name);
    p2.name[0]=toupper(p2.name[0]);
    d=strcmp(p1.name,p2.name);
    if(d==0){
        cleanInput(0,0);
        textcolor(7);
        printf("Players can't have the same name!");
    }
    }
}
system("cls");
}
void takeNames(char name1[]){
    int i,b=0;
    if(VIP==1){
        b=-6;
    }
    strcpy(name1,"          ");
    for(i=0;i<10;i++){
        if(i==9){
            while(name1[i]!=13||name1[i]!=8){
                cleanInput(i+15,1+b);
                name1[i]=getche();
                if(name1[i]==13){
                    name1[i]='\0';
                    break;
                }
                else if(name1[i]==8){
                    name1[i-1]='\0';
                    name1[i]='\0';
                    i--;
                    break;
                }
            }
        }
        if(i<9){
        while (name1[i]<97||name1[i]>122){
            if(name1[i]==8&&i!=0){
                name1[i]='\0';
                i--;
            }
            cleanInput(i+15,1+b);
            name1[i]=getche();
            if(i!=0&&name1[i]==13){
                name1[i]='\0';
            break;
        }
        }
        if(name1[i]=='\0'){
            break;
        }}
    }
}
void selectSize(){
    int temp=0;
    int v;
    if (load_save==0){
    while (temp==0){
    printf("1) 2 x 2\n2) 5 x 5\n");
    v=getche();
    switch (v-48){
    case (1): VIP=0;temp++;limits=5;remainingLines=12;break;
    case (2): VIP=1;temp++;limits=11;remainingLines=60;break;
    case (-40): system("cls");mainMenu();break;
    default:system("cls");printf("Wrong input please choose again\n\n");
        }}
    }
    else if(load_save==1){
        if(VIP==0){
            limits=5;
        }
        else if(VIP==1){
            limits=11;
        }
    }
    system("cls");
}
void mode(){
    int v;
    int temp=0;
    if(load_save==0){
    while (temp==0){

    printf("1) 1 Player\n2) 2 Players\n");
    v=getche();
    switch (v-48){
    case (1): pvc2=1;temp++;break;
    case (2): pvc2=0;temp++;break;
    case (-40):system("cls");selectSize();break;
    default:system("cls");printf("Wrong input please choose again\n\n");
        }
    }
    system("cls");
    names();
}}
void mainMenu(){
    int temp=0,i,v;
    VIP=0;
    for(i=0;i<49;i++){
            printf("\xB2");
        }
    goxy(0,1);
    printf("%c\t\tDOTS & BOXES\t\t\t%c\n",'\xB2','\xB2');
    for(i=0;i<49;i++){
            printf("\xB2");
        }
    printf("\n%c 1) Start Game\t\t2) Load Game\t\t%c\n%c 3) Ranking\t\t4) Exit (Recommended)\t%c\n",'\xB2','\xB2','\xB2','\xB2');
    for(i=0;i<49;i++){
            printf("\xB2");
        }
        printf("\n");
    while (temp==0){
    v=getche();
    switch (v-48){
    case (1):temp++;fload=1;break;
    case (2):temp++;fload=1;load();break;
    case (3):system("cls");temp=2;ranking();fload=1;exit(0);
    case (4):system("cls");exit(0);
    default:cleanInput(0,6);printf("Wrong input please choose again\n");
        }
    }
    system("cls");
    selectSize();
    mode();
    game();
    endGame();
}
void ranking(){
    int i=0,j,d;
    char x[10];
    typedef struct{
    char name[20];
    int score;
    }prank;
    prank rank[11];
    prank temp;
    FILE *fp;
    fp=fopen("ranking.txt","r");
    fscanf(fp,"%s\n",x);
    while(!feof(fp)){
        fscanf(fp,"%s",rank[i].name);
        fscanf(fp,"  %d\n",&rank[i].score);
        i++;
    }i=i-1;
    fclose(fp);
    j=i;
    for(i=0;i<j;i++){
    d=strcmp(rank[i].name,rank[j].name);
    if(d==0){
        if(rank[i].score>rank[j].score){
            rank[j].score=-999;
        }
        else {
            rank[i].score=-999;
        }
    }
    }
    int noswap=0;
    while(noswap==0){
        noswap=1;
    for(i=0;i<j;i++){
        if(rank[i].score<rank[i+1].score){
            strcpy(temp.name,rank[i].name);
            strcpy(rank[i].name,rank[i+1].name);
            strcpy(rank[i+1].name,temp.name);
            temp.score=rank[i].score;
            rank[i].score=rank[i+1].score;
            rank[i+1].score=temp.score;
            noswap=0;
        }
    }}
    goxy(5,0);
    printf("Ranking\n_________________\n");
    for(i=0;i<10;i++){
            if(rank[i].score<=2||rank[i].score>25){
                break;
            }
        printf("%d)%s\n",i+1,rank[i].name);
    }
    for(i=0;i<10;i++){
            VIP=0;
            goxy(15,i+2);
            if(rank[i].score<=2||rank[i].score>25){
                break;
            }
        printf("%d",rank[i].score);
    }
    j=i;
        fp=fopen("ranking.txt","w");
        fprintf(fp,"Ranking\n");
        for(i=0;i<j;i++){
        fprintf(fp,"%s  %d\n",rank[i].name,rank[i].score);
        }
        fclose(fp);
        j=i;
        goxy(5,j+3);
        for(i=0;i<32;i++){
            printf("\xB2");
        }
        goxy(5,j+4);

        printf("%c1) Main Menu\t   2) Exit  %c\n",'\xB2','\xB2');
        goxy(5,j+5);
        for(i=0;i<32;i++){
            printf("\xB2");
        }
        int temp1=0;
        while(temp1==0){
        goxy(5,j+6);
        i=getche();
        switch(i-48){
        case(1):temp1++;system("cls");resetGame();mainMenu();break;
        case(2):temp1++;system("cls");break;
        default:goxy(5,j+6);printf(" ");printf("Wrong input");}
        }
}
void endGame(){
    int i,temp=0,score;
    VIP=0;
    char winner[15];
    fflush(stdin);
    if (p1.score==p2.score){
        goxy(35,8);
        for(i=0;i<32;i++){
            printf("\xB2");
        }
        goxy(35,9);
        printf("%c\t\tDraw\t\t  %c",'\xB2','\xB2');
        goxy(35,10);
        printf("%c1) Main Menu\t2) Ranking%c\n",'\xB2','\xB2');
        goxy(35,11);
        printf("%c\t\t3) Exit\t\t  %c",'\xB2','\xB2');
        goxy(35,12);
        for(i=0;i<32;i++){
            printf("\xB2");
        }
        while(temp==0){
        goxy(35,13);
        i=getche();
        switch(i-48){
        case(1):temp++;system("cls");resetGame();mainMenu();break;
        case(2):temp++;system("cls");ranking();break;
        case(3):temp++;system("cls");break;
        default:goxy(35,13);printf(" ");printf("Wrong input");}
        }
    }
    else if(pvc2==1&&p2.score>p1.score){
        goxy(35,8);
        for(i=0;i<32;i++){
            printf("\xB2");
        }
        goxy(35,9);
        printf("%c\t\tYou Lose\t  %c",'\xB2','\xB2');
        goxy(35,10);
        printf("%c1) Main Menu\t2) Ranking%c\n",'\xB2','\xB2');
        goxy(35,11);
        printf("%c\t\t3) Exit\t\t  %c",'\xB2','\xB2');
        goxy(35,12);
        for(i=0;i<32;i++){
            printf("\xB2");
        }
        while(temp==0){
        goxy(35,13);
        i=getche();
        switch(i-48){
        case(1):temp++;system("cls");resetGame();mainMenu();break;
        case(2):temp++;system("cls");ranking();break;
        case(3):temp++;system("cls");break;
        default:goxy(35,13);printf(" ");printf("Wrong input");}
        }
    }
    else{
        if(p1.score>p2.score){
            strcpy(winner,p1.name);
            score=p1.score;
        }
        else{
            strcpy(winner,p2.name);
            score=p2.score;
        }
                goxy(35,8);
        for(i=0;i<32;i++){
            printf("\xB2");
        }
        goxy(35,9);
        printf("%c\t    The winner is\t  %c",'\xB2','\xB2');
        goxy(35,10);
        printf("%c\t\t\t          %c",'\xB2','\xB2');
        goxy(35,11);
        printf("%c1) Main Menu\t2) Ranking%c\n",'\xB2','\xB2');
        goxy(35,12);
        printf("%c\t\t3) Exit\t\t  %c",'\xB2','\xB2');
        goxy(35,13);
        for(i=0;i<32;i++){
            printf("\xB2");
        }
        delay(3000);
        goxy(50,10);
        printf("%s",winner);
        fflush(stdin);
        FILE * fp;
        fp=fopen("ranking.txt","a");
        fprintf(fp,"%s  %d\n",winner,score);
        fclose(fp);
        while(temp==0){
        goxy(35,14);
        i=getche();
        switch(i-48){
        case(1):temp++;system("cls");resetGame();mainMenu();break;
        case(2):temp++;system("cls");ranking();break;
        case(3):temp++;system("cls");break;
        default:goxy(35,14);printf(" ");printf("Wrong input");}
        }
    }
}
void resetGame(){
    int i,j,k;
    counter=0;
    uncoun=0;
    p1.move=0;
    p2.move=0;
    p1.score=0;
    p2.score=0;
    load_save=0;
    for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            k=i+j;
            if(k==3||k==5||k==7||k==9||k==11||k==13||k==15||k==17||k==19||k==21){
                if(i%2==0&&j%2==1&&i>0&&j>0){
                    grid[i][j]=" ";
                    check[i][j]=0;
                }
                else if(i%2==1&&j%2==0&&i>0&&j>0){
                    grid[i][j]="     ";
                    check[i][j]=0;
                }
            }
            else if (i%2==0&&j%2==0&&i>0&&j>0){
                check[i][j]=0;
            }
        }
    }
}
void save(){
    char c;
    FILE * f1;
    FILE * f2;
    FILE * f3;
    system("cls");
    printf("chose the file you want to save in\n1) file 1\n2) file 2\n3) file 3\n");
    c=getche();
    c=c-48;
    int i=0;
    if(VIP==1){
        i=-6;
    }
    while(!(c>0&&c<=3)){
        cleanInput(0,4+i);
        printf("Please try again!\n");
        c=getche();
        c=c-48;
    }
    switch (c){
    case 1:f1=fopen("save1.txt","wb");
            item_save(f1);
            break;
    case 2:f2=fopen("save2.txt","wb");
            item_save(f2);
            break;
    case 3:f3=fopen("save3.txt","wb");
            item_save(f3);
            break;
    }
}
void item_save(FILE *f){
    int i,j;
    time_diff=ticks;
    fprintf(f," %s %d %d ",p1.name,p1.score,p1.move);
    fprintf(f," %s %d %d ",p2.name,p2.score,p2.move);
    fprintf(f," %d %d %d %d %d %d %d ",remainingLines,counter,VIP,pvc2,recoun,uncoun,time_diff);
    for(i=0;i<12;i++)
    {
        for(j=0;j<12;j++)
        {
            fprintf(f,"%d ",check[i][j]);
        }
    }
    for(i=0;i<60;i++)
    {
        fprintf(f," %d %d %d ",pointss[i].po1,pointss[i].po2,pointss[i].seq);
    }
    fclose(f);
}
void load()
{
    char c;
    system("cls");
    printf("Choose the file you want to continue\n1) file 1\n2) file 2\n3) file 3\n");
    if(fload==0)
    {
        printf("Error! No file found\n");
    }
    c=getche();
    n_load=c-48;
    while(!((n_load>0&&n_load<=3)||n_load==-40))
    {
        cleanInput(0,4);
        printf("Please try again!\n");
        c=getche();
        n_load=c-48;
    }
    switch (n_load)
    {
    case 1:
        f1=fopen("save1.txt","rb");
        item_load(f1);
        break;
    case 2:
        f2=fopen("save2.txt","rb");
        item_load(f2);
        break;
    case 3:
        f3=fopen("save3.txt","rb");
        item_load(f3);
        break;
        case -40:system("cls");mainMenu();
    }
}
void item_load(FILE * f){
    int i,j,d;
    char l[5]="0",k[5]="0";
    fscanf(f,"%c",l);
    d=memcmp(k,l,1);
    if (f==NULL){
        fload=0;
        load();
    }
    else if(d==0){
        fload=0;
        load();
    }
    else{
    load_save=1;
    fload=1;
    fscanf(f," %s %d %d ",p1.name,&p1.score,&p1.move);
    fscanf(f," %s %d %d ",p2.name,&p2.score,&p2.move);
    fscanf(f," %d %d %d %d %d %d %d ",&remainingLines,&counter,&VIP,&pvc2,&recoun,&uncoun,&time_diff);
    for(i=0;i<12;i++)
    {
        for(j=0;j<12;j++)
        {
            fscanf(f,"%d ",&check[i][j]);
        }
    }
    for(i=0;i<60;i++)
    {
        fscanf(f," %d %d %d ",&pointss[i].po1,&pointss[i].po2,&pointss[i].seq);
    }
    fclose(f);
    for(i=0;i<12;i++)
    {
        for(j=0;j<12;j++)
        {
            if(check[i][j]==1){
                if(i+j==3||i+j==5||i+j==7||i+j==9||i+j==11||i+j==13||i+j==15||i+j==17||i+j==19||i+j==21){
                    if(i%2==0&&j!=0&&i!=0){
                        grid[i][j]="|";
                    }
                    else if(i%2==1&&j!=0&&i!=0){
                        grid[i][j]="-----";
                    }
                }
            }
        }
    }}
}
/*Color	Numerical Value
BLACK	0
BLUE	1
GREEN	2
CYAN	3
RED	4
MAGENTA	5
BROWN	6
LIGHTGRAY	7
DARKGRAY	8
LIGHTBLUE	9
LIGHTGREEN	10
LIGHTCYAN	11
LIGHTRED	12
LIGHTMAGENTA	13
YELLOW	14
WHITE	15*/
