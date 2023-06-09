#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


  /*************************/
 /*****MAIN MENU STUFF*****/
/*************************/

char Logo[25][50] = {
    "                     .........                    ",
    "               .....................              ",
    "           ...... .....................           ",
    "         .... . ..:.       :^..::.... ....        ",
    "       :.. ..:.::  .~    ~?:    ~  .:.. ..:.      ",
    "     .:.  .:. .J    ^Y  .!     !7     .:. ..:     ",
    "    :. ..:.   .P    :B       ^J7   .^:..:.  .:    ",
    "   :. ..^      ^    JJ    ^J?~    :^::...~. ..^   ",
    "  .: ..^...^!!.     #^   ?B.             ::.  .:  ",
    "  ^.  :~.    .JJ    ^G7  B?  :??77~^::^^^  ^   :. ",
    "  :.^~7.J~.  . 7P... ^J?:~ :5G^ .:^.!!! .. ~7~^.: ",
    " .:~&7! .&YJ?#: &Y#Y &~B#@BBP!^JY #.P7 :P#..#Y~.^ ",
    " .::P??  P 7:^Y P !!.&:7Y57PJY!:J75 J~ ??B7 G7..: ",
    "  ^ ..~   .^!!77~^^7P7  Y   5Y    .5~     :~^.... ",
    "  :.  .: ^.     .:::   :@   ~#.    ?J^.   !^ . ^  ",
    "   ^.. :^.            ^P?    B:      ::...^.. :.  ",
    "   .:.. :^::^~!!   ^??~.    ~P    ?^     :.. .:   ",
    "     :.  .:.      J7        ?J    !7   ::. .:.    ",
    "      :.. ..:.   ^~    .J~  .J.   ~: .:.  .:.     ",
    "        :.. ..:....  .^!.     :..^^... ....       ",
    "          .... ... ..::. ......::.. .....         ",
    "             ....... .................            ",
    "                 .................                ",
    "                                                  ",
    "                                                  "
};

void Startup(){

 system("start /min intro.wav");

  usleep(800000);
  for(int i=0; i<25; i++){
   for(int j=0; j<50; j++){
    printf("%c",Logo[i][j]);
   }

   printf("\n");
   usleep(35000);
  }
 
}

void updateMainMenu(int selectedOption) {
  system("cls");

   for(int i=0; i<25; i++){
    for(int j=0; j<50; j++){
     printf("%c",Logo[i][j]);
    }
   printf("\n");
  }

  if (selectedOption == 1)printf("\t\t  > Play");
  else printf("\t\t    Play");

  if (selectedOption == 2)printf("  > Exit");
  else printf("    Exit");

  if (selectedOption == 3)printf("\n\n\t\t  > Add Question");
  else printf("\n\n\t\t    Add Question");
}

int navigateMainMenu() {

 int selectedOption = 1;
 int key;

 updateMainMenu(selectedOption);

 while (1) {
  key = getch(); 

  if(key==224) { 
   key = getch();

   if(key==80) {
    selectedOption=3;
    updateMainMenu(selectedOption);

   }else if(key==75 || key==72) {
    selectedOption=1;
    updateMainMenu(selectedOption);

   }else if(key==77) { 
    selectedOption=2;
    updateMainMenu(selectedOption);
    }

  }else if(key==13)return selectedOption;
 }


}

  /*************************/
 /*******HINTS STUFF*******/
/*************************/
int correctAnswer, is5050used=0;
int removeans1=0,removeans2=0,removeans3=0,removeans4=0;


void Hint5050(char* answers[], char* ans1, char* ans2, char* ans3, char* ans4){
 int removeans=rand()%4,flag=-1,firstremove=-1;

 for(int i=0; i<4; i++){
  if(strcmp(answers[i],ans1)==0 && i==correctAnswer-1) flag=0;
  if(strcmp(answers[i],ans2)==0 && i==correctAnswer-1) flag=1;
  if(strcmp(answers[i],ans3)==0 && i==correctAnswer-1) flag=2;
  if(strcmp(answers[i],ans4)==0 && i==correctAnswer-1) flag=3;
 }

 while(removeans==flag) removeans=rand()%4;
 if(removeans==0)removeans1=1;
 if(removeans==1)removeans2=1;
 if(removeans==2)removeans3=1;
 if(removeans==3)removeans4=1;
 firstremove=removeans;
 while(removeans==flag || removeans==firstremove) removeans=rand()%4;
 if(removeans==0)removeans1=1;
 if(removeans==1)removeans2=1;
 if(removeans==2)removeans3=1;
 if(removeans==3)removeans4=1;
 is5050used=1;
 updateGameMenu(0, ans1, ans2, ans3, ans4);
}




  /*************************/
 /********GAME STUFF*******/
/*************************/
int difficulty=1;
void updateGameMenu(int selectedOption, char* ans1, char* ans2, char* ans3, char* ans4) {
  system("cls");
  printf("\n\n\n\n\n\t\t %d. Vapros koi e gamer: \n\n\n",difficulty);
  if(removeans1==0){  
   if (selectedOption == 1)printf("\t > A. %s",ans1);
   else printf("\t   A. %s",ans1);
  }else{
   if (selectedOption == 1)printf("\t X A.\t");
   else printf("\t   A.\t");
  }
  if(removeans2==0){
   if (selectedOption == 2)printf("\t\t > B. %s",ans2);
   else printf("\t\t   B. %s",ans2);
  }else{
   if (selectedOption == 2)printf("\t\t X B.\t");
   else printf("\t\t   B.\t");
  }
  if(removeans3==0){
   if (selectedOption == 3)printf("\n\n\t > C. %s",ans3);
   else printf("\n\n\t   C. %s",ans3);
  }else{
   if (selectedOption == 3)printf("\n\n\t X C.\t");
   else printf("\n\n\t   C.\t");
  }
  
  if(removeans4==0){  
   if (selectedOption == 4)printf("\t\t > D. %s",ans4);
   else printf("\t\t   D. %s",ans4);
  }else{
   if (selectedOption == 4)printf("\t\t X D.");
   else printf("\t\t   D.");
  }
  //Jokeri
  printf("\n\n\n\t\t\t  Hints: ");
  if (selectedOption == 5){
   if(is5050used==1) printf("\n\n\t X 50/50");
   else printf("\n\n\t > 50/50"); 
  }else printf("\n\n\t   50/50");
}

int navigateGameMenu(char* answers[], char* ans1, char* ans2, char* ans3, char* ans4) {
  int selectedOption = 1;

  
  updateGameMenu(selectedOption, ans1, ans2, ans3, ans4);
  int key;

  time_t startTime=time(NULL);
  time_t currentTime;

  do{
  currentTime=time(NULL);
  key = getch();

  if(key==224) { 
   key = getch();
  
   if(key==80) {
    if(selectedOption == 3 || selectedOption == 4) selectedOption=5;

    if(selectedOption == 1) selectedOption=3;
    else if(selectedOption == 2) selectedOption=4;

   }else if(key==72) {
    if(selectedOption == 3) selectedOption=1;
    else if(selectedOption == 4) selectedOption=2;

    if(selectedOption == 5) selectedOption=3;
  
   }else if(key==75) {
    if(selectedOption == 2) selectedOption=1;
    else if(selectedOption == 4) selectedOption=3;

   }else if(key==77) { 
    if(selectedOption == 1) selectedOption=2;
    else if(selectedOption == 3) selectedOption=4;
    }
   updateGameMenu(selectedOption, ans1, ans2, ans3, ans4);

  }else if(key==13){
    if((selectedOption==1 && removeans1==0)
    ||(selectedOption==2 && removeans2==0)
    ||(selectedOption==3 && removeans3==0)
    ||(selectedOption==4 && removeans4==0)
    ||(selectedOption>4)){
    if(selectedOption==5){
     if(is5050used==0){
      Hint5050(answers, ans1, ans2, ans3, ans4);
     }
    }else{
     return selectedOption; 
    }
   
   
   }
  }
 }while(currentTime-startTime<30);
 lose();
}

void GameLoop(int difficulty){
  if(difficulty==1)system("start /min stani_bogat.wav");
  else system("start /min vuprosite.wav");

  int playerAnswer;
  //here would be the system to get the question&answers from the file
  char* correctans="gamer";
  char* ans1="game";
  char* ans2="gaming";
  char* ans3="games";
  char* answers[4]={NULL};

  int ansrand=rand()%4;
  answers[ansrand]=correctans;
  correctAnswer=ansrand+1;

  ansrand=rand()%4;
  while(answers[ansrand]!=NULL)ansrand=rand()%4;
  answers[ansrand]=ans1;

  ansrand=rand()%4;
  while(answers[ansrand]!=NULL)ansrand=rand()%4;
  answers[ansrand]=ans2;

  ansrand=rand()%4;
  while(answers[ansrand]!=NULL)ansrand=rand()%4;
  answers[ansrand]=ans3;

  
   playerAnswer=navigateGameMenu(answers,answers[0],answers[1],answers[2],answers[3]);
   
   if(playerAnswer==correctAnswer){
    if(difficulty==10){ winner();}
    else{
     system("start /min correct_answer.wav");
     usleep(1250000);
     removeans1=0;
     removeans2=0;
     removeans3=0;
     removeans4=0;
     difficulty+=1;
     GameLoop(difficulty);
    }
   }
   else{lose();}

}
 
 

  /*************************/
 /******WIN/LOSE STUFF*****/
/*************************/
int win=0;

void winner(){
 win=1;
 system("start /min winner.wav");
 system("cls");
 printf("\n\n\n\n\n\n\n\t Ti pobedi!!!!!! stana BOGAT!!!!!!! \n\n\n");
 sleep(20);
 printf("\n\t\t    > Exit?");
 getchar();
}


void lose(){
 system("start /min game_over.wav");
 sleep(3);
 system("cls");
}



  /*************************/
 /**********MAIN***********/
/*************************/

int main() {
 srand(time(NULL));
 Startup();
 sleep(9);


 int option;

 while(win==0){
  option=navigateMainMenu();
  if(option==1)GameLoop(difficulty);
  if(option==2) return 0;
  if(option==3) return 0;
 }
 return 0;
}