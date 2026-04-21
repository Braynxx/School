#include <iostream>
#include <string>

void runningFunction(char** cells, int rows, int cols);

void printCells(char** cells, int rows, int cols);

void deleteCells(char** cells, int rows);

void cellProgress(char** cells, int rows, int cols);

int aliveCheck(char** cells, int rows, int cols, int i, int j);

char populationReform(char** cells, int i, int j, int aliveCount);

int main() {
    std::string line;
    int rows = -1;
    int cols = -1;
    char tempGrid[100][100];
    while(std::getline(std::cin, line) && rows < 100) {
        if(rows == -1) {
            cols = line.length();
            rows = 0;   
        }
        if(line[0] != 'O' && line[0] != '.') {
            break;
        } else {
            for(int j = 0; j < cols; j++){
                tempGrid[rows][j] = line[j];
            }
            rows += 1;
        }
    }
    char** cells = new char*[rows];
    for(int i = 0; i < rows; i++){
        cells[i] = new char[cols];
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cells[i][j] = tempGrid[i][j];
        }
    }

    runningFunction(cells, rows, cols);

    deleteCells(cells, rows);

    return 0;
}

void runningFunction(char** cells, int rows, int cols){
    int running = 1;
    char input = 'x';
    while(running == 1){
        if(!(std::cin >> input)){
            running = 0;
            break;
        }
        if(input == 's'){
            cellProgress(cells, rows, cols);
            continue;
        } else if(input == 'p'){
            printCells(cells, rows, cols);
            continue;
        } else if(input == 'x'){
            running = 0;
            break;
        } else {
            running = 0;
            break;
        }
    }
}

void printCells(char** cells, int rows, int cols){
    for(int i = 0; i < cols; i++) {
        std::cout << "|";
    } 
    for(int i = 0; i < rows; i++) {
        std::cout << "\n";
        for(int j = 0; j < cols; j++) {
            std::cout << cells[i][j];
        }
    }
    std::cout << "\n";
    for(int i = 0; i < cols; i++) {
        std::cout << "|";
    }
    std::cout << "\n"; 
}

void deleteCells(char** cells, int rows){
    for(int i = 0; i < rows; i++){
        delete[] cells[i];
        cells[i] = nullptr;
    }
    delete[] cells;
    cells = nullptr;
}

void cellProgress(char** cells, int rows, int cols){
    int aliveCount = 0;
    char** temp = new char*[rows];
    for(int i = 0; i < rows; i++){
        temp[i] = new char[cols];
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j <cols; j++){
            aliveCount = aliveCheck(cells, rows, cols, i, j);
            temp[i][j] = populationReform(cells, i, j, aliveCount);
        }
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cells[i][j] = temp[i][j];
        }
    }
    deleteCells(temp, rows);
}

int aliveCheck(char** cells, int rows, int cols, int i, int j){
    int count = 0;
    if(i - 1 >= 0 && cells[i - 1][j] == 'O'){
        count++;
    }
    if(i + 1 < rows && cells[i + 1][j] == 'O'){
        count++;
    }
    if(j + 1 < cols && cells[i][j + 1] == 'O'){
        count++;
    }
    if(j - 1 >= 0 && cells[i][j - 1] == 'O'){
        count++;
    }
    if(i - 1 >= 0 && j - 1 >= 0 && cells[i - 1][j - 1] == 'O'){
        count++;
    }
    if(i + 1 < rows && j - 1 >= 0 && cells[i + 1][j - 1] == 'O'){
        count++;
    }
    if(i - 1 >= 0 && j + 1 < cols && cells[i - 1][j + 1] == 'O'){
        count++;
    }
    if(i + 1 < rows && j + 1 < cols && cells[i + 1][j + 1] == 'O'){
        count++;
    }
    return count;
}

char populationReform(char** cells, int i, int j, int aliveCount){
    if(cells[i][j] == 'O'){
        if(aliveCount < 2){
            return '.';
        } else if(aliveCount > 3){
            return '.';
        } else{
            return 'O';
        }
    }
    if (cells[i][j] == '.'){
        if(aliveCount == 3){
            return 'O';
        } else{
            return '.';
        }
    }
    return 'X';
}
