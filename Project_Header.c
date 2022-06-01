#include "Project_Header.h"

/* EX 1 */

/************************************************************************************************************************
 * validKnightMoves creates and returns the chessPosArray of pointers to chessPosarray.
 */
chessPosArray ***validKnightMoves()
{

    chessPosArray ***board = (chessPosArray ***)malloc(SIZE_OF_BOARD * sizeof(chessPosArray **));

    allocCheck(board);

    int row;

    for (row = 0; row < SIZE_OF_BOARD; row++)
    {

        board[row] = chessPosArrayArr(row);
    }

    return board;
}

/************************************************************************************************************************
 * chessPosArrayArr helps validKnightMoves.
 */
chessPosArray **chessPosArrayArr(int row)
{

    chessPosArray **boardRow = (chessPosArray **)malloc(SIZE_OF_BOARD * sizeof(chessPosArray *));

    allocCheck(boardRow);

    int col;

    for (col = 0; col < SIZE_OF_BOARD; col++)
    {

        boardRow[col] = possibleMoves(row + 'A', col + '1');
    }

    return boardRow;
}

/************************************************************************************************************************
 * possibleMoves finds and returns a chessPosArray of all of the possible moves in each cell.
 */
chessPosArray *possibleMoves(char row, char col)
{

    int size = 0;

    chessPosArray *res = (chessPosArray *)malloc(sizeof(chessPosArray));
    allocCheck(res);

    res->positions = (chessPos *)malloc(8 * sizeof(chessPos));
    allocCheck(res->positions);

    checkPoint(res->positions, &size, row - 2, col - 1); /*UpperLeft*/
    checkPoint(res->positions, &size, row - 2, col + 1); /*UpperRight*/
    checkPoint(res->positions, &size, row - 1, col + 2); /*RightUp*/
    checkPoint(res->positions, &size, row + 1, col + 2); /*RightDown*/
    checkPoint(res->positions, &size, row + 2, col + 1); /*DownRight*/
    checkPoint(res->positions, &size, row + 2, col - 1); /*DownLeft*/
    checkPoint(res->positions, &size, row - 1, col - 2); /*LeftUp*/
    checkPoint(res->positions, &size, row + 1, col - 2); /*LeftDown*/

    chessPos *temp = (chessPos *)realloc(res->positions, size * sizeof(chessPos));
    res->positions = temp;

    allocCheck(res->positions);

    res->size = size;
    return res;
}

/************************************************************************************************************************
 * checkPoint checks if a point given is valid (inside the board).
 */
void checkPoint(chessPos *positions, int *size, char row, char col)
{

    if (row >= 'A' && row <= 'A' + SIZE_OF_BOARD - 1 && col >= '1' && col <= '1' + SIZE_OF_BOARD - 1)
    {
        positions[*size][0] = row;
        positions[*size][1] = col;

        *size = *size + 1;
    }
}

/*************************************************************************************************************************/

void allocCheck(void *ptr)
{
    if (ptr == NULL)
    {
        printf("ERROR! Memory allocation failed, Exiting. \n");
        exit(1);
    }
}

/*************************************************************************************************************************/

void freeAllPossibleMoves(chessPosArray ***board)
{

    int row;

    for (row = 0; row < SIZE_OF_BOARD; row++)
    {

        freeAllPossibleMovesRow(board[row]);
    }

    free(board);
}

/*************************************************************************************************************************/

void freeAllPossibleMovesRow(chessPosArray **boardRow)
{

    int col;

    for (col = 0; col < SIZE_OF_BOARD; col++)
    {

        freePossibleMoves(boardRow[col]);
    }

    free(boardRow);
}

/*************************************************************************************************************************/

void freePossibleMoves(chessPosArray *boardCell)
{

    free(boardCell->positions);
    free(boardCell);
}

/*************************************************************************************************************************/

/* EX 2 */

/************************************************************************************************************************
 * display gets a list of moves, and prints a board which displays the order of the moves.
 */
void display(chessPosList *lst)
{

    chessPosCell *curr = lst->head;
    chessPosCell *saver = NULL;

    int currX, currY, index;

    bool Exists[SIZE_OF_BOARD * SIZE_OF_BOARD];

    if (isEmptyList(lst))
        return;

    /* The list is not empty */

    for (int i = 0; i < SIZE_OF_BOARD * SIZE_OF_BOARD; i++)
        Exists[i] = false;

    while (curr != NULL)
    {

        adjustXY(&currX, &currY, &(curr->position));

        index = currX * SIZE_OF_BOARD + currY;

        if (Exists[index])
        {

            curr = curr->next;

            removeNode(lst, saver);
        }
        else
        {

            Exists[index] = true;

            saver = curr;

            curr = curr->next;
        }
    }

    /* Insert & Print */

    int board[SIZE_OF_BOARD][SIZE_OF_BOARD];

    makeEmptyBoard(board);

    insertToBoard(board, lst);

    PrintBoard(board);

    printf("\n");
}

/*************************************************************************************************************************/

void makeEmptyBoard(int board[][SIZE_OF_BOARD])
{

    int i, j;

    for (i = 0; i < SIZE_OF_BOARD; i++)

        for (j = 0; j < SIZE_OF_BOARD; j++)

            board[i][j] = 0;
}

/************************************************************************************************************************
 * insertToBoard gets the empty board, and a list of moves.
 * the funciton inserts to the board the order of the moves.
 */
void insertToBoard(int board[][SIZE_OF_BOARD], chessPosList *lst)
{

    int currX, currY, counter;

    counter = 1;

    chessPosCell *curr = lst->head;

    while (curr != NULL)
    {

        adjustXY(&currX, &currY, &(curr->position));

        board[currX][currY] = counter;

        counter++;

        curr = curr->next;
    }
}

/*************************************************************************************************************************/

void PrintBoard(int board[][SIZE_OF_BOARD])
{

    int i;

    for (i = -1; i < SIZE_OF_BOARD; i++)
    {

        PrintDecoLine();

        if (i == -1)
            PrintDataLine(board[0], 'A' + i);

        else
            PrintDataLine(board[i], 'A' + i);
    }

    PrintDecoLine();
}

/*************************************************************************************************************************/

void PrintDataLine(int board[], char ch)
{

    int i;

    for (i = -1; i < SIZE_OF_BOARD; i++)
    {

        if (i == -1)
        {

            if (ch == '@')
                printf("|    ");

            else
                printf("|  %c ", ch);
        }
        else
        {

            if (ch == '@')
                printf("| %2d ", i + 1);

            else
            {
                if (board[i] == 0)
                    printf("|    ");
                else
                    printf("| %2d ", board[i]);
            }
        }
    }

    printf("|\n");
}

/*************************************************************************************************************************/

void PrintDecoLine()
{

    int i;

    for (i = 0; i < SIZE_OF_BOARD + 1; i++)
    {

        printf("+----");
    }

    printf("+\n");
}

/*************************************************************************************************************************
 * adjustXY changes the position from char to integer.
 */
void adjustXY(int *X, int *Y, chessPos *Point)
{

    *X = ((*Point)[0]) - 'A';
    *Y = ((*Point)[1]) - '1';
}

/*************************************************************************************************************************/

bool isEmptyList(chessPosList *lst)
{

    return lst->head == NULL;
}

/*************************************************************************************************************************/

void makeEmptyList(chessPosList *lst)
{

    lst->head = lst->tail = NULL;
}

/*************************************************************************************************************************/

chessPosCell *createNewNode(chessPos data, chessPosCell *nextNode)
{

    chessPosCell *node = (chessPosCell *)malloc(sizeof(chessPosCell));

    allocCheck(node);

    node->position[0] = data[0];

    node->position[1] = data[1];

    node->next = nextNode;

    return node;
}

/*************************************************************************************************************************/

void insertNodeToTail(chessPosList *lst, chessPosCell *newTail)
{

    if (isEmptyList(lst))
    {

        lst->head = lst->tail = newTail;
    }
    else
    {

        lst->tail->next = newTail;

        lst->tail = newTail;
    }
}

/************************************************************************************************************************
 * removeNode removes the node from the list.
 * ASSUMPIONS: the list is not Empty.
 */
void removeNode(chessPosList *lst, chessPosCell *saver)
{

    chessPosCell *toDelete = saver->next;

    if (toDelete->next == NULL)
    {

        lst->tail = saver;

        saver->next = NULL;
    }
    else
    {

        saver->next = toDelete->next;
    }

    free(toDelete);
}

/*************************************************************************************************************************/

void myFreeList(chessPosList *lst)
{

    chessPosCell *curr = lst->head;
    chessPosCell *saver = lst->head;

    while (!isEmptyList(lst))

        removeNodeFromStart(lst, lst->head);
}

/*************************************************************************************************************************/

/* EX 3 */

/************************************************************************************************************************
 * findAllPossibleKnightPaths creates and returns the tree of possible paths of the given starting position,
 * with the help of findAllPossibleKnightPathsHelper (this is only an envelope).
 */
pathTree findAllPossibleKnightPaths(chessPos *startingPosition)
{

    pathTree res;
    chessPosArray ***allPossibleMoves = validKnightMoves();

    bool board[SIZE_OF_BOARD * SIZE_OF_BOARD];
    int i;

    for (i = 0; i < SIZE_OF_BOARD * SIZE_OF_BOARD; i++)
    {

        board[i] = false;
    }

    res.root = findAllPossibleKnightPathsHelper(startingPosition, allPossibleMoves, board);

    freeAllPossibleMoves(allPossibleMoves);

    return res;
}

/************************************************************************************************************************
 * findAllPossibleKnightPathsHelper creates and returns the tree of possible paths of the given starting position, (by Recursion).
 */
treeNode *findAllPossibleKnightPathsHelper(chessPos *startingPosition, chessPosArray ***allPossibleMoves, bool board[])
{

    treeNode *res;

    treeNodeListCell *curr = NULL;

    int currX, currY, index;

    res = (treeNode *)malloc(sizeof(treeNode));

    allocCheck(res);

    res->position[0] = (startingPosition[0])[0];
    res->position[1] = (startingPosition[0])[1];

    adjustXY(&currX, &currY, &(res->position));

    index = currX * SIZE_OF_BOARD + currY;

    board[index] = true;

    updateNextMoves(res, allPossibleMoves[currX][currY]->positions, allPossibleMoves[currX][currY]->size, board);
    curr = res->next_possible_positions;

    while (curr != NULL)
    {
        curr->node = findAllPossibleKnightPathsHelper(&(curr->node->position), allPossibleMoves, board);
        curr = curr->next;
    }

    board[index] = false;

    return res;
}

/*************************************************************************************************************************
 * updateNextMoves updates the next possible moves of the given root, after removing the visitedLocations from the original possible moves list.
 */
void updateNextMoves(treeNode *res, chessPos arr[], int size, bool board[])
{

    makeEmptyRoot(res);

    int index, currY, currX;

    for (int i = 0; i < size; i++)
    {

        adjustXY(&currX, &currY, arr[i]);

        index = currX * SIZE_OF_BOARD + currY;

        if (!board[index])
            insertDataToStartList(res, arr[i]);
    }
}

/*************************************************************************************************************************/

bool isEmptyRoot(treeNode *root)
{

    return root->next_possible_positions == NULL;
}

/*************************************************************************************************************************/

void makeEmptyRoot(treeNode *root)
{

    root->next_possible_positions = NULL;
}

/*************************************************************************************************************************
 * the function removes saver->next
 * ASSUMPIONS: saver->next != NULL
 */
void removeTreeNodeListCell(treeNodeListCell *saver)
{

    treeNodeListCell *toDelete = saver->next;

    if (toDelete->next == NULL)
    {

        saver->next = NULL;
    }
    else
    { /* to Delete is in the middle of the list */

        saver->next = toDelete->next;
    }

    free(toDelete);
}

/*************************************************************************************************************************/

void insertDataToStartList(treeNode *root, chessPos data)
{

    treeNodeListCell *newHead = createNewTreeNode(data, NULL);

    insertNodeToStartList(root, newHead);
}

/*************************************************************************************************************************/

treeNodeListCell *createNewTreeNode(chessPos data, treeNodeListCell *next)
{

    treeNodeListCell *Node = (treeNodeListCell *)malloc(sizeof(treeNodeListCell));

    allocCheck(Node);

    treeNode *temp = (treeNode *)malloc(sizeof(treeNode));

    allocCheck(temp);

    (temp->position)[0] = data[0];
    (temp->position)[1] = data[1];

    Node->node = temp;

    Node->node->next_possible_positions = next;

    Node->next = next;

    return Node;
}

/*************************************************************************************************************************/

void insertNodeToStartList(treeNode *root, treeNodeListCell *newHead)
{

    if (isEmptyRoot(root))
    {

        root->next_possible_positions = newHead;
    }
    else
    {

        newHead->next = root->next_possible_positions;

        root->next_possible_positions = newHead;
    }
}

/*************************************************************************************************************************/

void removeNodeTree(treeNode *lst, treeNodeListCell *saver)
{

    /* ASSUMPIONS: the list is not Empty */

    chessPosCell *toDelete = saver->next;

    if (toDelete->next == NULL)
    {

        saver->next = NULL;
    }
    else
    { /* to Delete is in the middle of the list */

        saver->next = toDelete->next;
    }

    free(toDelete);
}

/*************************************************************************************************************************/

/* EX 4 */

/*************************************************************************************************************************
 * findKnightPathCoveringAllBoard envelope function of findKnightPathCoveringAllBoardRec.
 * the function returns in res the list of the moves by their order from the root to the end.
 */
chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree)
{

    chessPosList *res = (chessPosList *)malloc(sizeof(chessPosList));
    allocCheck(res);
    makeEmptyList(res);

    int counter = 0;

    bool found = false;

    treeNode *root = path_tree->root;

    treeNode visitedLocations;
    visitedLocations.next_possible_positions = NULL;

    findKnightPathCoveringAllBoardRec(root, &counter, &visitedLocations, &found);

    /* visitedLocations contains a treeNode root, with the first path (if found == true).  if found == false => return NULL */

    if (found == true)

        convertTochessPosList(&visitedLocations, res);

    else
        return NULL;

    return res;
}

/*************************************************************************************************************************
 * findKnightPathCoveringAllBoardRec finds the first path that covers all of the board, if exists.
 * if there isn't a possible path that cover all of the board from the given path_tree, the function return NULL.
 * the function returns in res the list of the moves by their order from the root to the end.
 */
void findKnightPathCoveringAllBoardRec(treeNode *root, int *counter, treeNode *visitedLocations, bool *found)
{

    if (*found == true)

        return;

    treeNodeListCell *curr = NULL;

    insertDataToStartList(visitedLocations, &root->position);

    *counter = *counter + 1;

    curr = root->next_possible_positions;

    while (curr != NULL && !(*found))
    {
        findKnightPathCoveringAllBoardRec(curr->node, counter, visitedLocations, found);
        curr = curr->next;
    }

    if (!(*found))
    {

        if (*counter == SIZE_OF_BOARD * SIZE_OF_BOARD)
        {

            *found = true;

            return;
        }
        else
        {

            removeTreeCellFromStart(visitedLocations, visitedLocations->next_possible_positions);

            *counter = *counter - 1;
        }
    }
}

/*************************************************************************************************************************
 * convertTochessPosList gets a pointer to a treeNode (visitedLocations), and a pointer to a chessPosList (res).
 * the function converts and inverts the visitedLocations list to a chessPosList.
 */
void convertTochessPosList(treeNode *visitedLocations, chessPosList *res)
{

    int i;

    treeNodeListCell *curr = visitedLocations->next_possible_positions;

    for (i = 0; i < SIZE_OF_BOARD * SIZE_OF_BOARD; i++)
    {

        insertDataToStartchessPosList(res, curr->node->position);
        curr = curr->next;
    }
}

/*************************************************************************************************************************/

void insertDataToStartchessPosList(chessPosList *res, chessPos data)
{

    chessPosCell *newHead = createNewNode(data, NULL);

    insertNodeToStartchessPosList(res, newHead);
}

/*************************************************************************************************************************/

void insertNodeToStartchessPosList(chessPosList *res, chessPosCell *newHead)
{

    if (isEmptyList(res))

        res->head = res->tail = newHead;

    else
    {

        newHead->next = res->head;

        res->head = newHead;
    }
}

/*************************************************************************************************************************/

void removeNodeFromStart(chessPosList *lst, chessPosCell *toDelete)
{

    if (toDelete->next == NULL)

        makeEmptyList(lst);

    else
        lst->head = toDelete->next;

    free(toDelete);
}

/*************************************************************************************************************************/

void removeTreeCellFromStart(treeNode *visitedLocations, treeNodeListCell *saver)
{

    treeNodeListCell *toDelete = saver;
    visitedLocations->next_possible_positions = visitedLocations->next_possible_positions->next;

    free(toDelete);
}

/*************************************************************************************************************************/

void myFreeTree(pathTree tree)
{

    myFreeTreeHelper(tree.root);
}

/*************************************************************************************************************************/

void myFreeTreeHelper(treeNode *root)
{

    treeNodeListCell *curr = root->next_possible_positions;

    while (curr != NULL)
    {
        myFreeTreeHelper(root->next_possible_positions->node);

        curr = curr->next;

        removeTreeCellFromStart(root, root->next_possible_positions);
    }

    free(root);
}

/*************************************************************************************************************************/

/* EX 5 */

/*************************************************************************************************************************
 * saveListToBinFile gets a file name and a position list represanting a knight path.
 * the function saves the path in the binary file.
 * saveListToBinFile is an envelope function of saveListToBinFileHelper.
 */
void saveListToBinFile(char *file_name, chessPosList *pos_list)
{

    int size, extraPoints;

    short int numOfPoints;

    FILE *dest;

    BYTE arr[4];

    chessPosCell *rest;

    numOfPoints = listLen(pos_list);

    dest = fopen(file_name, "wb");

    fileCheck(dest);

    fwrite(&numOfPoints, sizeof(short int), 1, dest);

    saveListToBinFileHelper(dest, pos_list->head, arr, (int)numOfPoints);

    fclose(dest);
}

/*************************************************************************************************************************
 * saveListToBinFileHelper saves the path in the binary file.
 */
void saveListToBinFileHelper(FILE *dest, chessPosCell *head, BYTE arr[], int numOfPoints)
{

    int i, currX, currY;

    if (numOfPoints == 0)
        return;

    if (numOfPoints < 4 && numOfPoints > 0)
    {

        for (i = 0; i < numOfPoints; i++)
        {

            arr[i] = convertToByte(head->position);

            head = head->next;
        }

        setByteArray(arr, numOfPoints);

        printToBinFile(dest, arr, numOfPoints);

        return;
    }

    for (i = 0; i < 4; i++)
    {

        arr[i] = convertToByte(head->position);

        head = head->next;
    }

    setByteArray(arr, 4);

    printToBinFile(dest, arr, 4);

    saveListToBinFileHelper(dest, head, arr, numOfPoints - 4);
}

/*************************************************************************************************************************/

BYTE convertToByte(chessPos *position)
{

    BYTE res;
    int currX, currY;

    adjustXY(&currX, &currY, position);

    res = (BYTE)((currX * BASE) + currY);
}

/*************************************************************************************************************************
 * printToBinFile prints the Bytes of arr to dest.
 */
void printToBinFile(FILE *dest, BYTE arr[], int size)
{

    BYTE mask1, mask2;

    switch (size)
    {

    case 4:

        /* BYTE 1 */
        mask1 = arr[1] >> 6;
        arr[0] |= mask1;
        arr[1] = arr[1] << 2;

        /* BYTE 2 */
        mask2 = arr[2] >> 4;
        arr[1] |= mask2;
        arr[2] = arr[2] << 4;

        /* BYTE 3 */
        arr[2] |= (arr[3] >> 2);
        size = 3;

        break;

    case 3:

        /* BYTE 1 */
        mask1 = arr[1] >> 6;
        arr[0] |= mask1;
        arr[1] = arr[1] << 2;

        /* BYTE 2 */
        mask2 = arr[2] >> 4;
        arr[1] |= mask2;
        arr[2] = arr[2] << 4;

        break;

    case 2:

        /* BYTE 1 */
        mask1 = arr[1] >> 6;
        arr[0] |= mask1;
        arr[1] = arr[1] << 2;

        break;
    default:
        break;
    }

    fwrite(arr, sizeof(BYTE), size, dest);
}

/*************************************************************************************************************************
 * setByteArray sets the points in the array to the first 6 bits in the Byte.
 */
void setByteArray(BYTE arr[], int size)
{

    BYTE mask1 = 0x07;
    BYTE mask2 = 0x70;
    BYTE temp1, temp2;

    int i;

    for (i = 0; i < size; i++)
    {

        temp1 = (arr[i] & mask1) << 2;
        temp2 = (arr[i] & mask2) << 1;

        arr[i] = (temp1 | temp2);
    }
}

/*************************************************************************************************************************/

int listLen(chessPosList *lst)
{

    int len = 0;

    chessPosCell *curr = lst->head;

    while (curr != NULL)
    {

        len++;
        curr = curr->next;
    }

    return len;
}

/*************************************************************************************************************************/

void fileCheck(FILE *fp)
{

    if (fp == NULL)
    {

        printf("ERROR! Opening of File Failed, Exiting. \n");
        exit(1);
    }
}

/*************************************************************************************************************************/

/* EX 6 */

/*************************************************************************************************************************
 * checkAndDisplayPathFromFile gets a binary file (file_name), loads the path from the file, and displays the path on the screen.
 */
int checkAndDisplayPathFromFile(char *file_name)
{

    FILE *source;

    int res, counter, check;

    short int numOfPoints;

    BYTE *arr;

    bool legal = true;

    chessPosList lst;

    makeEmptyList(&lst);

    res = 0;

    source = fopen(file_name, "rb");

    if (fileCheck2(source) == -1)
        return -1;

    fread(&numOfPoints, sizeof(short int), 1, source);

    arr = (BYTE *)malloc(((int)numOfPoints) * sizeof(BYTE));

    allocCheck(arr);

    fread(arr, sizeof(BYTE), (int)numOfPoints, source);

    getListFromBinArray(arr, (int)numOfPoints, &lst);

    legal = checkLegalMoves(&lst);

    if (!legal)
    {

        free(arr);
        myFreeList(&lst);
        fclose(source);
        return 1;
    }

    display(&lst);

    counter = listLen(&lst);

    if (counter == SIZE_OF_BOARD * SIZE_OF_BOARD)

        res = 2;

    else
        res = 3;

    fclose(source);
    free(arr);
    myFreeList(&lst);

    return res;
}

/*************************************************************************************************************************
 * getListFromBinArray converts the Bytes to the represanting path.
 */
void getListFromBinArray(BYTE *arr, int numOfPoints, chessPosList *lst)
{

    int i, size;

    size = ((numOfPoints / 4) * 3) + (numOfPoints % 4);

    for (i = 0; i < size; i++)
    {

        convertToNodeAndInsertToList(arr, i, lst);
    }
}

/*************************************************************************************************************************/

void convertToNodeAndInsertToList(BYTE *arr, int i, chessPosList *lst)
{

    BYTE maskX, maskY, maskXb, maskYb;

    chessPos curr;

    switch (i % 3)
    {

    case 0:

        maskX = 0xE0;
        maskY = 0x1C;

        maskX = maskX & arr[i];
        maskY = maskY & arr[i];

        maskX = maskX >> 5;
        maskY = maskY >> 2;

        curr[0] = maskX + 'A';
        curr[1] = maskY + '1';

        insertDataToTail(lst, curr);

        break;

    case 1:

        maskX = 0x06;
        maskXb = 0x01;
        maskY = 0x07;

        maskX = maskX & (arr[i - 1] << 1);
        maskXb = maskXb & (arr[i] >> 7);
        maskX |= maskXb;

        maskY = maskY & (arr[i] >> 4);

        curr[0] = maskX + 'A';
        curr[1] = maskY + '1';

        insertDataToTail(lst, curr);

        break;

    case 2:

        maskX = 0x07;
        maskY = 0x04;
        maskYb = 0x03;

        maskX = maskX & (arr[i - 1] >> 1);

        maskY = maskY & (arr[i - 1] << 2);
        maskYb = maskYb & (arr[i] >> 6);
        maskY |= maskYb;

        curr[0] = maskX + 'A';
        curr[1] = maskY + '1';

        insertDataToTail(lst, curr);

        /* For the last point */

        maskX = 0x07;
        maskY = 0x07;

        maskX = maskX & (arr[i] >> 3);
        maskY = maskY & arr[i];

        curr[0] = maskX + 'A';
        curr[1] = maskY + '1';

        insertDataToTail(lst, curr);

        break;
    }
}

/*************************************************************************************************************************/

void insertDataToTail(chessPosList *lst, chessPos data)
{

    chessPosCell *newTail = createNewNode(data, NULL);

    insertNodeToTail(lst, newTail);
}

/*************************************************************************************************************************
 * checkLegalMoves gets a path, and returns true if the path is a legal knight path.
 * else, returns false.
 */
bool checkLegalMoves(chessPosList *lst)
{

    chessPosArray ***board;

    chessPosCell *curr, *saver;

    int currX, currY;

    int trash;

    bool check = true;

    curr = saver = lst->head;

    if (isEmptyList(lst) || curr->next == NULL)
        return true;

    board = validKnightMoves();

    while (curr != NULL && check)
    {

        if (curr == lst->head)
        {

            if (!((curr->position)[0] >= 'A' && (curr->position)[0] <= 'A' + SIZE_OF_BOARD - 1 && (curr->position)[1] >= '1' && (curr->position)[1] <= '1' + SIZE_OF_BOARD - 1))

                check = false;

            else

                curr = curr->next;
        }
        else
        {

            adjustXY(&currX, &currY, &(saver->position));

            if (!checkPossibleMove(board[currX][currY], curr->position))
                check = false;

            saver = curr;
            curr = curr->next;
        }
    }

    freeAllPossibleMoves(board);

    return check;
}

/*************************************************************************************************************************/

bool checkPossibleMove(chessPosArray *possibleMoves, chessPos position)
{

    int i;

    for (i = 0; i < possibleMoves->size; i++)
    {

        if ((possibleMoves->positions)[i][0] == position[0] && (possibleMoves->positions)[i][1] == position[1])
            return true;
    }

    return false;
}

/*************************************************************************************************************************/

int fileCheck2(FILE *fp)
{

    if (fp == NULL)
    {

        printf("ERROR! Opening of File Failed, Exiting. \n");
        return -1;
    }
}

/*************************************************************************************************************************/

/* EX 7 */

/*************************************************************************************************************************/

void initiateGame(int choice)
{

    int res;

    chessPos startingPosition;

    chessPos saverPosition = {0, 0};

    chessPosArray ***board = NULL;

    chessPosList *lst;

    pathTree tree;

    char *file_name;

    menuChecks check = {false, false, false};

    while (!validChoice(choice))
    {

        printf("The choice is NOT valid, please choose from among these: \n");

        printMenu();

        scanf("%d", &choice);
    }

    lst = (chessPosList *)malloc(sizeof(chessPosList));

    allocCheck(lst);

    board = validKnightMoves();

    while (validChoice(choice))
    {

        switch (choice)
        {

        case 1:

            saverPosition[0] = startingPosition[0];
            saverPosition[1] = startingPosition[1];

            scanf("\n%c", &(startingPosition[0]));
            scanf("%d", &(startingPosition[1]));
            startingPosition[1] += '0';

            if (!validLocation(startingPosition))
            {

                printf("The Location you have chosen is NOT valid! \n");
                printf("Please enter a different Location. \n");
                printf("A Location is entered with a Capital Letter (A-%c), followed by a number (1-%d), and then Enter. \n", 'A' - 1 + SIZE_OF_BOARD, 0 + SIZE_OF_BOARD);

                startingPosition[0] = saverPosition[0];
                startingPosition[1] = saverPosition[1];
            }
            else
            {

                printf("Position accepted successfully. \n");

                check.startingPointExists = true;
                check.pathExists = false;
                check.treeExists = false;
            }

            printMenu();

            scanf("%d", &choice);

            break;

        case 2:

            if (!check.startingPointExists)
            {

                StartingPointDoesnotExist(&choice);
            }
            else
            {

                tree = findAllPossibleKnightPaths(startingPosition);

                check.treeExists = true;

                printf("All Possible Knight Paths created. \n");

                printMenu();

                scanf("%d", &choice);
            }

            break;

        case 3:

            if (!check.startingPointExists)
            {

                StartingPointDoesnotExist(&choice);
            }
            else
            {

                if (!check.treeExists)
                    tree = findAllPossibleKnightPaths(startingPosition);

                lst = findKnightPathCoveringAllBoard(&tree);

                check.pathExists = true;
                check.treeExists = true;

                if (lst == NULL)
                    printf("There is no possible path for the knight to cover all of the board from this location.\n");
                else
                    printf("Found a Knight Path covering all of the board. \n");

                printMenu();

                scanf("%d", &choice);
            }

            break;

        case 4:

            if (!check.startingPointExists)
            {

                StartingPointDoesnotExist(&choice);
            }
            else
            {

                if (!check.pathExists || !check.treeExists)
                {

                    if (!check.treeExists)
                    {

                        tree = findAllPossibleKnightPaths(startingPosition);
                        check.treeExists = true;
                    }

                    if (!check.pathExists)
                    {

                        lst = findKnightPathCoveringAllBoard(&tree);
                        check.pathExists = true;

                        if (lst == NULL)
                        {

                            printf("There is no possible path for the knight to cover all of the board from this location.\n");
                            printMenu();

                            scanf("%d", &choice);
                        }
                        else
                            printf("Found a Knight Path covering all of the board. \n");
                    }

                    file_name = getFileName();

                    saveListToBinFile(file_name, lst);

                    printf("Path saved to %s successfully. \n", file_name);

                    free(file_name);
                }
                else
                {

                    file_name = getFileName();

                    saveListToBinFile(file_name, lst);

                    printf("Path saved to %s successfully. \n", file_name);

                    free(file_name);
                }

                printMenu();

                scanf("%d", &choice);
            }

            break;

        case 5:

            file_name = getFileName();

            res = checkAndDisplayPathFromFile(file_name);

            free(file_name);

            resultAnalyzer(res);

            printMenu();

            scanf("%d", &choice);

            break;

        case 6:

            if (check.pathExists)

                myFreeList(lst);

            if (check.treeExists)

                myFreeTree(tree);

            freeAllPossibleMoves(board);

            if (lst != NULL)
            {

                free(lst);
            }

            exit(0);

            break;

        default:

            printf("The choice is NOT valid, please choose from among these: \n");

            printMenu();

            scanf("%d", &choice);

            break;
        }
    }
}

/*************************************************************************************************************************/

void printMenu()
{

    printf("\n");

    printf("1. Enter a knight's starting position \n");

    printf("2. Create all possible knight paths \n");

    printf("3. Find a knight path covering all board \n");

    printf("4. Save knight path covering all board to file \n");

    printf("5. Load and display path from file \n");

    printf("6. Exit \n");
}

/*************************************************************************************************************************/

bool validChoice(int choice)
{

    return choice >= 1 && choice <= 6;
}

/*************************************************************************************************************************/

void StartingPointDoesnotExist(int *choice)
{

    printf("You have to enter a starting position before accessing this choice. \n");

    printMenu();

    scanf("%d", choice);
}

/*************************************************************************************************************************/

char *getFileName()
{

    char *str;

    char ch;

    int size, logSize;

    size = 1;
    logSize = 0;

    str = (char *)malloc(sizeof(char));

    allocCheck(str);

    printf("Insert the Name of the File: \n");

    ch = getchar(); /* to "eat" the '\n' after the last scan for choice */

    ch = getchar();

    while (ch != '\n')
    {

        if (logSize == size)
        {

            str = (char *)realloc(str, size * 2 * sizeof(char));

            allocCheck(str);

            size *= 2;
        }

        str[logSize] = ch;
        logSize++;

        ch = getchar();
    }

    if (logSize + 1 != size)
    {

        str = (char *)realloc(str, (logSize + 1) * sizeof(char));

        allocCheck(str);
    }

    str[logSize] = '\0';

    return str;
}

/*************************************************************************************************************************/

void resultAnalyzer(int res)
{

    switch (res)
    {

    case -1:

        printf("The file does not exist. \n");
        break;

    case 1:

        printf("The path is not valid. \n");
        break;

    case 2:

        printf("The path is valid, and covers all of the board. \n");
        break;

    case 3:

        printf("The path is valid, but doesn't cover all of the board. \n");
        break;
    }
}

/*************************************************************************************************************************/

bool validLocation(chessPos position)
{

    int x, y;

    x = position[0] - 'A';
    y = position[1] - '1';

    return x >= 0 && x < SIZE_OF_BOARD && y >= 0 && y < SIZE_OF_BOARD;
}

/*************************************************************************************************************************/
