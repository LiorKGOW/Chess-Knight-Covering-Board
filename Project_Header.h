#ifndef Project_Header

#define Project_Header

#include "Project_Header.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define SIZE_OF_BOARD 5

#define BASE 16

typedef struct MenuChecks
{

    bool startingPointExists;
    bool treeExists;
    bool pathExists;

} menuChecks;

typedef char chessPos[2];

typedef struct _chessPosArray
{
    unsigned int size;
    chessPos *positions;
} chessPosArray;

typedef struct _chessPosCell
{

    chessPos position;
    struct _chessPosCell *next;
} chessPosCell;

typedef struct _chessPosList
{

    chessPosCell *head;
    chessPosCell *tail;
} chessPosList;

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode
{

    chessPos position;
    treeNodeListCell *next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell
{

    treeNode *node;
    struct _treeNodeListCell *next;

} treeNodeListCell;

typedef struct _pathTree
{

    treeNode *root;
} pathTree;

typedef unsigned char BYTE;

/* EX 1 */

chessPosArray ***validKnightMoves();
chessPosArray **chessPosArrayArr(int row);

chessPosArray *possibleMoves(char row, char col);
void checkPoint(chessPos *spot, int *size, char row, char col);

void allocCheck(void *ptr);

void freeAllPossibleMoves(chessPosArray ***board);
void freeAllPossibleMovesRow(chessPosArray **boardRow);
void freePossibleMoves(chessPosArray *boardCell);

/* EX 2 */

void display(chessPosList *lst);

void makeEmptyBoard(int board[][SIZE_OF_BOARD]);
void insertToBoard(int board[][SIZE_OF_BOARD], chessPosList *lst);

void PrintBoard(int board[][SIZE_OF_BOARD]);
void PrintDataLine(int board[], char ch);
void PrintDecoLine();

void adjustXY(int *X, int *Y, chessPos *Point);

void makeEmptyList(chessPosList *lst);
bool isEmptyList(chessPosList *lst);

chessPosCell *createNewNode(chessPos data, chessPosCell *nextNode);
void insertNodeToTail(chessPosList *lst, chessPosCell *newTail);
void removeNode(chessPosList *lst, chessPosCell *saver);

void myFreeList(chessPosList *lst);

/* EX 3 */

pathTree findAllPossibleKnightPaths(chessPos *startingPosition);
treeNode *findAllPossibleKnightPathsHelper(chessPos *startingPosition, chessPosArray ***allPossibleMoves, bool board[]);

void updateNextMoves(treeNode *res, chessPos arr[], int size, bool board[]);

bool isEmptyRoot(treeNode *root);
void makeEmptyRoot(treeNode *root);

void removeTreeNodeListCell(treeNodeListCell *saver);
void insertDataToStartList(treeNode *root, chessPos data);
treeNodeListCell *createNewTreeNode(chessPos data, treeNodeListCell *next);
void insertNodeToStartList(treeNode *root, treeNodeListCell *newHead);
void removeNodeTree(treeNode *lst, treeNodeListCell *saver);

/* EX 4 */

chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree);
void findKnightPathCoveringAllBoardRec(treeNode *root, int *counter, treeNode *visitedLocations, bool *found);

void convertTochessPosList(treeNode *visitedLocations, chessPosList *res);
void insertDataToStartchessPosList(chessPosList *res, chessPos data);
void insertNodeToStartchessPosList(chessPosList *res, chessPosCell *newHead);

void removeNodeFromStart(chessPosList *lst, chessPosCell *toDelete);
void removeTreeCellFromStart(treeNode *visitedLocations, treeNodeListCell *saver);

void myFreeTree(pathTree tree);
void myFreeTreeHelper(treeNode *root);

/* EX 5 */

void saveListToBinFile(char *file_name, chessPosList *pos_list);
void saveListToBinFileHelper(FILE *dest, chessPosCell *head, BYTE arr[], int numOfPoints);

BYTE convertToByte(chessPos *position);

void printToBinFile(FILE *dest, BYTE arr[], int size);
void setByteArray(BYTE arr[], int size);

int listLen(chessPosList *lst);

void fileCheck(FILE *fp);

/* EX 6 */

int checkAndDisplayPathFromFile(char *file_name);

void getListFromBinArray(BYTE *arr, int size, chessPosList *lst);

void convertToNodeAndInsertToList(BYTE *arr, int i, chessPosList *lst);
void insertDataToTail(chessPosList *lst, chessPos data);

bool checkLegalMoves(chessPosList *lst);
bool checkPossibleMove(chessPosArray *possibleMoves, chessPos position);

int fileCheck2(FILE *fp);

/* EX 7 */

void initiateGame(int choice);

void printMenu();

bool validChoice(int choice);
void StartingPointDoesnotExist(int *choice);

char *getFileName();

void resultAnalyzer(int res);
bool validLocation(chessPos position);

#endif Project_Header
