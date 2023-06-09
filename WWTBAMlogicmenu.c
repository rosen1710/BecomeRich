#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void updateMenu(int selectedOption) {
    //paste code from game menu

    if (selectedOption == 3)printf("\t\t  > Add question");
    else printf("\t\t    Add question");

    if (selectedOption == 4)printf("\t\t  > Edit question");
    else printf("\t\t    Edit question");

    if (selectedOption == 5)printf("\t\t  > Remove question");
    else printf("\t\t    Remove question");

}
