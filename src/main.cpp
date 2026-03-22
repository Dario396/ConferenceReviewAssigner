#include <iostream>
#include "parser/CSVParser.h"

#include <iostream>
#include "parser/CSVParser.h"
#include "ui/Menu.h"
using namespace std;


int main(int argc, char* argv[]) {

    /* Batch mode
     * ./myProg -b input.csv output.csv
     * skips the menu
     * read from input.csv
     * writes to output.csv (ssignments + risk management)
     * send error messages to stderr (std:cerr)
     */
    if (argc == 4 && strcmp(argv[1], "b")) {
        // runBatchMode(argv[2], argv[3]);
        return 0;
    }

    Menu menu;
    menu.run();

    return 0;
}