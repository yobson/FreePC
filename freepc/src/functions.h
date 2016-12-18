#include <kore/kore.h>
#include <kore/http.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Global Vars;
char *CompNode;
char *IndexPage;
int roomTracker, currentID, intID, addY, numberOfRooms;

typedef struct {
    char id[5];
    int status;
    char user[24];
    int below;
    int right;
    int rightOffset;
} Computer;

typedef struct {
    char roomID[2];
    int rows;
    int colls;
    Computer computers[];
} Room;

Room *rooms[12];

int populateCompNode(char **, Computer);
int buildRoomTable(char **, Room *);
void addRoom(char id[2], int numberOfComputers);
void fillComp(void);
void addInitial(void);
void addBelow(void);
void addRight(int offset);