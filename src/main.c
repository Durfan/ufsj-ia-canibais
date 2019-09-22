#include "./includes/main.h"
#include "raylib.h"
  
int main(void) {

	const int screenWidth = 700;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "IA - Missionarios vs. Canibais");

	State start = setState(M,C);
 	State *hashmap = initMap();

	addState(start,hashmap);
	expand(start,hashmap);

 	for (int i=0; i < 10; i++) {
		for (int j=0; j < mapSize(); j++) {
			expand(hashmap[j],hashmap);
		}
	}

	prtMap(hashmap);

	SetTargetFPS(30);
	int posx,posy,bloc;

    while (!WindowShouldClose()) {

		posx = 1;
		posy = 10;
		bloc = 0;

        BeginDrawing();
		ClearBackground(RAYWHITE);

		for (int i=0; i < mapSize(); i++) {
			if (bloc > 33) {
				bloc = 0;
				posx = 1;
				posy += 10;
			}

			if (hashmap[i].mapped) {
				if (!hashmap[i].dinner)
					DrawRectangle(posx*10,posy,9,9,BLUE);
				else
					DrawRectangle(posx*10,posy,9,9,RED);
				//DrawText(stateInfo(hashmap[i],hashmap),200,80,10,BLACK);
			}
			else
				DrawRectangle(posx*10,posy,9,9,LIGHTGRAY);
			posx++;
			bloc++;
		}

		
        EndDrawing();
    }

	free(hashmap);
	return 0;
}