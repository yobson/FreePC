#include "freepc.h"
#include "assets.h"
#include "timetable.h"

int mainPage(struct http_request *req)
{
	int len = strlen(IndexPage)-2;
	char *out, *table;
	len += buildRoomTable(&table, rooms[0]);
	out = malloc(len);
	*out = '\0';
	sprintf(out, IndexPage, table);
	http_response_header(req, "content-type", "text/html");
	http_response(req, 200, out, strlen(out));
	free(out);
	free(table);
	return (KORE_RESULT_OK);
}

int registerComp(struct http_request *req) {
	http_populate_get(req);

	char *roomID, *user;
	char *done = "Done", *error = "Error";
	int status, compID, search = 1, i = 0;

	http_argument_get_string(req, "roomID", &roomID);
	http_argument_get_int32 (req, "compID", &compID);
	http_argument_get_string(req, "user", &user);
	http_argument_get_int32 (req, "status", &status);

	printf("Registering %s %i\n", roomID, compID);

	while(search) {
		if (strcmp(roomID, rooms[i]->roomID)) {
			search = 0;
		} else { 
			i++;
			if(i >= numberOfRooms) { 
				http_response(req, 400, error, strlen(error));
				return (KORE_RESULT_OK); 
			}
		}
	}

	rooms[i]->computers[compID-1].status = status;
	strncpy(rooms[i]->computers[compID-1].user, user, 24);
	
	http_response(req, 200, done, strlen(done));
	printf("DONE\n");
	return (KORE_RESULT_OK);
}

void alloc(void) {
	printf("---------Init----------\n");
	atexit(&dealloc);
	roomTracker = -1;
	currentID = 0;
	numberOfRooms = 0;
	
	buildStudyArea();

	CompNode = malloc(asset_len_node_html + 1);
	IndexPage = malloc(asset_len_main_html + 1);
	*(CompNode + asset_len_node_html) = '\0';
	*(IndexPage + asset_len_main_html) = '\0';
	strncpy(CompNode, (char *) asset_node_html, asset_len_node_html);
	strncpy(IndexPage, (char *) asset_main_html, asset_len_main_html);
	printf("Done\n");
}

void dealloc(void) {
	printf("-----Dealloc-----\n");
	int i;
	for(i = 0; i < numberOfRooms; i++) {
		free(rooms[i]);
	}
	free(CompNode);
	free(IndexPage);
}

void buildStudyArea(){
	addRoom("SB", 14);
	addInitial();
	addBelow();
	addBelow();
	addBelow();
	addBelow();
	addBelow();
	addBelow();
	addBelow();
	addBelow();
	addBelow();
	addBelow();
	addBelow();
	addRight(0);
	addRight(0);
}