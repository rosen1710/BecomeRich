#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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

void PrintLogo(){
 system("start /min intro.wav");
 usleep(700000);
  for(int i=0; i<25; i++){
   for(int j=0; j<50; j++){
    printf("%c",Logo[i][j]);
   }

   printf("\n");
   usleep(35000);
  }
 
}

void updateMenu(int selectedOption) {
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
}

int navigateMenu() {

 int selectedOption = 1;
 int key;

 updateMenu(selectedOption);

 while (1) {
  key = getch(); 

  if(key==224) { 
   key = getch();

   if(key==75) {
    if(selectedOption == 2) selectedOption=1;
    updateMenu(selectedOption);

   }else if(key==77) { 
    if(selectedOption == 1) selectedOption=2;
    updateMenu(selectedOption);
    }

  }else if(key==13)return selectedOption;
 }


}

int main() {

 PrintLogo();
 usleep(10000000);
 
 int option = navigateMenu();

 if(option==1){
  system("start /min stani_bogat.wav");
  usleep(14000000);
 }
 if(option==2)return 0;

 return 0;
}