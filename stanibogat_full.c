#include <stdio.h>
#include <stdlib.h>
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
  if (selectedOption == 1)printf("\t\t\033[1;33m  > Play\033[1;0m");
  else printf("\t\t    Play");

  if (selectedOption == 2)printf("\033[1;33m  > Exit\033[1;0m");
  else printf("    Exit");

  if (selectedOption == 3)printf("\n\n\t\t\033[1;33m  > Add Question\033[1;0m");
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

int correctAnswer;
  /*************************/
 /*******HINTS STUFF*******/
/*************************/
int is5050used=0;
int removeanswers[4];


void Hint5050(int difficulty, char* answers[], char* ans1, char* ans2, char* ans3, char* ans4){
 int removeans=rand()%4,firstremove=-1;

 while(removeans==correctAnswer-1) removeans=rand()%4;
 if(removeans==0)removeanswers[0]=1;
 if(removeans==1)removeanswers[1]=1;
 if(removeans==2)removeanswers[2]=1;
 if(removeans==3)removeanswers[3]=1;
 firstremove=removeans;
 while(removeans==correctAnswer-1 || removeans==firstremove) removeans=rand()%4;
 if(removeans==0)removeanswers[0]=1;
 if(removeans==1)removeanswers[1]=1;
 if(removeans==2)removeanswers[2]=1;
 if(removeans==3)removeanswers[3]=1;

 is5050used=1;
 updateGameMenu(difficulty, 0, ans1, ans2, ans3, ans4);
}




int displayresults=0; 
int isHintPublicused=0;
int voteans[4];


void HintPublic(int difficulty, char* answers[], char* ans1, char* ans2, char* ans3, char* ans4){
 int correctChance=rand()%100+1;

 int votes[4];
 if(is5050used==0){ 
  while((votes[0]+votes[1]+votes[2]+votes[3])!=100 || votes[0]<votes[1] || votes[1]<votes[2] || votes[2]<votes[3])
  {
   votes[0]=rand()%100+1;
   votes[1]=rand()%100+1;
   votes[2]=rand()%100+1;
   votes[3]=rand()%100+1;
  }
 }else{
  while((votes[0]+votes[1])!=100 || votes[0]<votes[1])
  {
   votes[0]=rand()%100+1;
   votes[1]=rand()%100+1;
  }
 }
 

 int randomselect=0,select1,select2,select3;

 if(difficulty<=3){
   if(correctChance<=80){
   if(is5050used==0){

    voteans[correctAnswer-1]=votes[0];
    randomselect=rand()%3+1;

    while(randomselect==correctAnswer-1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[1];
    select1=randomselect;

    while(randomselect==correctAnswer-1 || randomselect==select1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[2];
    select2=randomselect;

    while(randomselect==correctAnswer-1 || randomselect==select1 || randomselect==select2)randomselect=rand()%3+1;
    voteans[randomselect]=votes[3];

   }else{

    voteans[correctAnswer-1]=votes[0];
    for(int i=0; i<4; i++) if(removeanswers[i]==0 && i!=correctAnswer-1) voteans[i]=votes[1];
    
   }
  }else{
   if(is5050used==0){
    randomselect=rand()%3+1;
    while(randomselect==correctAnswer-1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[0];
    select1=randomselect;

    while(randomselect==select1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[1];
    select2=randomselect;

    while(randomselect==select1 || randomselect==select2)randomselect=rand()%3+1;
    voteans[randomselect]=votes[2];
    select3=randomselect;

    while(randomselect==select1 || randomselect==select2 || randomselect==select3)randomselect=rand()%3+1;
    voteans[randomselect]=votes[3];

   }else{
    
    randomselect=rand()%3+1;
    while(randomselect==correctAnswer-1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[0];
    for(int i=0; i<4; i++) if(removeanswers[i]==0 && i==correctAnswer-1) voteans[i]=votes[1];

    }
   }
   }else if(difficulty<=6){
   if(correctChance<=60){
   if(is5050used==0){

    voteans[correctAnswer-1]=votes[0];
    randomselect=rand()%3+1;

    while(randomselect==correctAnswer-1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[1];
    select1=randomselect;

    while(randomselect==correctAnswer-1 || randomselect==select1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[2];
    select2=randomselect;

    while(randomselect==correctAnswer-1 || randomselect==select1 || randomselect==select2)randomselect=rand()%3+1;
    voteans[randomselect]=votes[3];

   }else{

    voteans[correctAnswer-1]=votes[0];
    for(int i=0; i<4; i++) if(removeanswers[i]==0 && i!=correctAnswer-1) voteans[i]=votes[1];
    
   }
  }else{
   if(is5050used==0){
    randomselect=rand()%3+1;
    while(randomselect==correctAnswer-1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[0];
    select1=randomselect;

    while(randomselect==select1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[1];
    select2=randomselect;

    while(randomselect==select1 || randomselect==select2)randomselect=rand()%3+1;
    voteans[randomselect]=votes[2];
    select3=randomselect;

    while(randomselect==select1 || randomselect==select2 || randomselect==select3)randomselect=rand()%3+1;
    voteans[randomselect]=votes[3];

   }else{
    
    randomselect=rand()%3+1;
    while(randomselect==correctAnswer-1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[0];
    for(int i=0; i<4; i++) if(removeanswers[i]==0 && i==correctAnswer-1) voteans[i]=votes[1];

   }
  }
  }else if(difficulty<=10){
  if(correctChance<=30){
   if(is5050used==0){

    voteans[correctAnswer-1]=votes[0];
    randomselect=rand()%3+1;

    while(randomselect==correctAnswer-1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[1];
    select1=randomselect;

    while(randomselect==correctAnswer-1 || randomselect==select1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[2];
    select2=randomselect;

    while(randomselect==correctAnswer-1 || randomselect==select1 || randomselect==select2)randomselect=rand()%3+1;
    voteans[randomselect]=votes[3];

   }else{

    voteans[correctAnswer-1]=votes[0];
    for(int i=0; i<4; i++) if(removeanswers[i]==0 && i!=correctAnswer-1) voteans[i]=votes[1];
    
   }
  }else{
   if(is5050used==0){
    randomselect=rand()%3+1;
    while(randomselect==correctAnswer-1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[0];
    select1=randomselect;

    while(randomselect==select1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[1];
    select2=randomselect;

    while(randomselect==select1 || randomselect==select2)randomselect=rand()%3+1;
    voteans[randomselect]=votes[2];
    select3=randomselect;

    while(randomselect==select1 || randomselect==select2 || randomselect==select3)randomselect=rand()%3+1;
    voteans[randomselect]=votes[3];

   }else{
    
    randomselect=rand()%3+1;
    while(randomselect==correctAnswer-1)randomselect=rand()%3+1;
    voteans[randomselect]=votes[0];
    for(int i=0; i<4; i++) if(removeanswers[i]==0 && i==correctAnswer-1) voteans[i]=votes[1];

   }
  }
 }


 displayresults=1;
 isHintPublicused=1;
 updateGameMenu(difficulty, 0, ans1, ans2, ans3, ans4);
}





  /*************************/
 /********GAME STUFF*******/
/*************************/
int outoftime=0;

void updateGameMenu(int difficulty, int selectedOption, char* ans1, char* ans2, char* ans3, char* ans4) {
  system("cls");
  printf("\n\n\n\n\n\t\t %d. Vapros Koi veren: \n\n\n",difficulty);
  if(removeanswers[0]==0){  
   if (selectedOption == 1)printf("\t\033[1;33m > A. %s\033[1;0m",ans1);
   else printf("\t   A. %s",ans1);
  }else{
   if (selectedOption == 1)printf("\t\033[1;31m X A.\033[1;0m\t");
   else printf("\t   A.\t");
  }
  if(removeanswers[1]==0){
   if (selectedOption == 2)printf("\t\t\033[1;33m > B. %s\033[1;0m",ans2);
   else printf("\t\t   B. %s",ans2);
  }else{
   if (selectedOption == 2)printf("\t\t\033[1;31m X B.\033[1;0m\t");
   else printf("\t\t   B.\t");
  }
  if(removeanswers[2]==0){
   if (selectedOption == 3)printf("\n\n\t\033[1;33m > C. %s\033[1;0m",ans3);
   else printf("\n\n\t   C. %s",ans3);
  }else{
   if (selectedOption == 3)printf("\n\n\t\033[1;31m X C.\033[1;0m\t");
   else printf("\n\n\t   C.\t");
  }
  if(removeanswers[3]==0){  
   if (selectedOption == 4)printf("\t\t\033[1;33m > D. %s\033[1;0m",ans4);
   else printf("\t\t   D. %s",ans4);
  }else{
   if (selectedOption == 4)printf("\t\t\033[1;31m X D.\033[1;0m");
   else printf("\t\t   D.");
  }
  //Jokeri
  printf("\n\n\n\t\t\tHints: ");
  if (selectedOption == 5){
   if(is5050used==1) printf("\n\n\t\033[1;31m X 50/50\033[1;0m");
   else printf("\n\n\t\033[1;33m > 50/50\033[1;0m"); 
  }else printf("\n\n\t   50/50");

  if (selectedOption == 6){
   if(isHintPublicused==1) printf("\t\033[1;31m X Pomosht ot publika\033[1;0m");
   else printf("\t\033[1;33m > Pomosht ot publika\033[1;0m"); 
  }else printf("\t   Pomosht ot publika");
    
   if(displayresults==1) printf("\n\n\t Rezultati ot publikata: A.%d%% B.%d%% C.%d%% D.%d%%",voteans[0],voteans[1],voteans[2],voteans[3]); 

 
}


int navigateGameMenu(int difficulty, char* answers[], char* ans1, char* ans2, char* ans3, char* ans4) {
  int selectedOption = 1;

  
  updateGameMenu(difficulty,selectedOption, ans1, ans2, ans3, ans4);
  int key;

  time_t startTime=time(NULL);
  time_t currentTime;

  do{
  currentTime=time(NULL);
  key = getch();

  if(key==224) { 
   key = getch();
  
   if(key==80) {
    if(selectedOption == 3) selectedOption=5;
    if(selectedOption == 4) selectedOption=6;

    if(selectedOption == 1) selectedOption=3;
    else if(selectedOption == 2) selectedOption=4;

   }else if(key==72) {
    if(selectedOption == 3) selectedOption=1;
    else if(selectedOption == 4) selectedOption=2;

    if(selectedOption == 5) selectedOption=3;
    if(selectedOption == 6) selectedOption=3;
  
   }else if(key==75) {
    if(selectedOption == 2) selectedOption=1;
    else if(selectedOption == 4) selectedOption=3;
    if(selectedOption == 6) selectedOption=5;

   }else if(key==77) { 
    if(selectedOption == 1) selectedOption=2;
    else if(selectedOption == 3) selectedOption=4;
    if(selectedOption == 5) selectedOption=6;
    }
   updateGameMenu(difficulty,selectedOption, ans1, ans2, ans3, ans4);

  }else if(key==13){
    if((selectedOption==1 && removeanswers[0]==0)
    ||(selectedOption==2 && removeanswers[1]==0)
    ||(selectedOption==3 && removeanswers[2]==0)
    ||(selectedOption==4 && removeanswers[3]==0)
    ||(selectedOption>4)){
    if(selectedOption==5){
     if(is5050used==0){
      Hint5050(difficulty,answers, ans1, ans2, ans3, ans4);
     }
    }else if(selectedOption==6){
     if(isHintPublicused==0){
      HintPublic(difficulty,answers, ans1, ans2, ans3, ans4);
     }
    }else{
     return selectedOption; 
    }
   
   
   }
  }
 }while(currentTime-startTime<30);
 outoftime=1;
 lose();
}

void GameLoop(int difficulty){
  if(difficulty==1)system("start /min stani_bogat.wav");
  else system("start /min vuprosite.wav");

  int playerAnswer;
  //here would be the system to get the question&answers from the file
  char* correctans="tozi";
  char* ans1="tova";
  char* ans2="tuk";
  char* ans3="tuka";
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

  
   playerAnswer=navigateGameMenu(difficulty, answers,answers[0],answers[1],answers[2],answers[3]);
   
   if(playerAnswer==correctAnswer){
    if(difficulty==10){ winner();}
    else{
     system("start /min correct_answer.wav");
     usleep(1250000);
     for(int i=0; i<4; i++){
      removeanswers[i]=0;
      voteans[i]=0;
     }
     outoftime=0;
     difficulty+=1;
     displayresults=0;
     GameLoop(difficulty);
    }
   }
   else{if(outoftime==0)lose();}

}
 
 

  /*************************/
 /******WIN/LOSE STUFF*****/
/*************************/
int win=0;

void winner(){
 win=1;
 int key;
 system("start /min winner.wav");
 system("cls");
 printf("\n\n\n\n\n\n\n\t Ti pobedi!!!!!! stana BOGAT!!!!!!! \n\n\n");
 sleep(20);
 printf("\n\t\t    > Exit?");

 while(key!=13)key = getch(); 
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
 //sleep(9);


 int option,difficulty=1;

 while(win==0){
  option=navigateMainMenu();
  if(option==1)GameLoop(difficulty);
  if(option==2) return 0;
  if(option==3) return 0;
     for(int i=0; i<4; i++){
      removeanswers[i]=0;
      voteans[i]=0;
     }
     outoftime=0;
     is5050used=0;
     isHintPublicused=0;
     difficulty=1;
     displayresults=0;
 }
 return 0;
}