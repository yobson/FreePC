#include "functions.h"

int populateCompNode(char **out, Computer comp) {
    int len = strlen(CompNode) + sizeof(Computer) + 1 - sizeof(int) * 4;
    *out = malloc(len);
    **out = '\0';
    sprintf(*out, CompNode, comp.id, (comp.status == 0 ? "OFF" : "ON"), comp.user);
    return len;
}

int buildRoomTable(char **out, Room *room) {
    *out = malloc((strlen(CompNode) + sizeof(Computer) - sizeof(int) * 3) * room->rows * room->colls);
    **out = '\0';
    int rowCount = 0, loopEnd = 0, i = 0, rowIndex = 0, iterator, len = 0;

    while (rowCount < room->rows) {
        loopEnd = 0;
        strcat(*out, "<tr>\n");
        len += strlen("<tr>\n");
        while (loopEnd == 0) {
            char *block;
            len += populateCompNode(&block, room->computers[i]);
            strcat(*out, block);
            free(block);
            if (room->computers[i].right != -1) {
                for (iterator = 0; iterator < room->computers[i].rightOffset; iterator++) {
                    strcat(*out, "<td></td>\n");
                    len += strlen("<td></td>\n");
                }
                i = room->computers[i].right;
            } else { loopEnd = 1; }
        }

        i = room->computers[rowIndex].below;
        rowIndex = i;
        rowCount++;
        strcat(*out, "</tr>\n");
        len += strlen("</tr>\n");
    }
    return len;
}

void addRoom(char id[2], int numberOfComputers) {
    rooms[roomTracker+1] = malloc(sizeof(Room) + sizeof(Computer) * numberOfComputers);
    strncpy(rooms[roomTracker+1]->roomID, id, 2);
    rooms[roomTracker+1]->rows = 1;
    rooms[roomTracker+1]->colls = 1;
    addY = 1;
    roomTracker++;
    numberOfRooms++;
}

void fillComp(void) {
    char id[3] = {'\0'};
    strncpy(rooms[roomTracker]->computers[currentID].id, rooms[roomTracker]->roomID, 2);
    sprintf(id, " %i", currentID + 1);
    rooms[roomTracker]->computers[currentID].id[2] = '\0';
    strcat(rooms[roomTracker]->computers[currentID].id, id);
    strncpy(rooms[roomTracker]->computers[currentID].user, "None", 24);
    rooms[roomTracker]->computers[currentID].status = 0;
    rooms[roomTracker]->computers[currentID].right = -1;
    rooms[roomTracker]->computers[currentID].rightOffset = 0;
    rooms[roomTracker]->computers[currentID].below = 0;
    currentID++;
}

void addInitial(void) {
    currentID = 0;
    intID = currentID;
    fillComp();
}

void addBelow(void) {
    rooms[roomTracker]->rows++;
    addY = 1;
    rooms[roomTracker]->computers[intID].below = currentID;
    intID = currentID;
    fillComp();
}

void addRight(int offset) {
    rooms[roomTracker]->computers[currentID-1].right = currentID;
    rooms[roomTracker]->computers[currentID-1].rightOffset = offset;
    addY += 1 + offset;
    if (addY > rooms[roomTracker]->colls) { rooms[roomTracker]->colls = addY; }
    fillComp();
}