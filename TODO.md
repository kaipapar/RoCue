# TODO

### Guide

- [<status>] <priority> <Brief description> #<tag> @<mention> <yyyy-mm-dd>  
    - [] <Subtask>  
    - <Description>  
  
status flags:   x = done,  
                ~ = on hold,  
                + = almost done,  
                - = started,  
                u = untested,  
                t = tested  


priority flags: 1 = low priority,  
                2 = medium priority,  
                3 = high priority  

### Uncompleted
7.5.23  
- [-] 1 Github: make repo _nice_ #docs
- [~] 2 Doxygen: Create documentation with doxygen or similar tool #docs
- [~] 2 Pathfinding: Make the orcs BSF pathfinding work @Kaipapar
- [] 2 Inventory: Create architecture for inventory system
- [] 1 Items: Create new items after inventory system
- [] 1 World interaction: Pitfalls etc
- [] 1 File I/O: Save points--gamestates..
- [+] 2 Error Checking: Memory buffers, check that malloc works.
- [] 1 Seed: Make seeding optional

8.5.23  
- [-] 2 Commenting: Recreate docstrings and comments to work with Doxygen #docs
- [] 1 Windows port: recreate menu using ncurses or find a way for menu.h to work with Win

10.5.23
- [] 1 Time tracking: create a spreadsheet for time tracking

12.5.23
- [] Consider updating floor struct to be more efficient.  See localizing.txt for details.
    - [] Try to swap the pointers from floor struct members and once created only access them directly using floor.map[y][x] syntax, not floor->map...

23.5.23
- [-] 3 Upkeep function: Check surroundings of player and do something 
    - [-] --> Update game world / player status / logic tick
- [] Restart button alongside Quit game button --> returns to main menu and regenerates maps

### Completed [x]
12.5.23
- [x] 2 Create floor struct and struct array 
    - [x] to replace 3d array of map. z coordinates --> floors struct elements.
- [x] 3 Plan: write plan for code architecture without any global variables. #docs #code
    - [x] Main.c global variables and Rogue.h externs should be localized.
- [x] 3 Reminder: remove all global variables. #code

17.5.23
- [x] Localize currentfloor. Make a pointer to the original currentfloor integer and edit through that. 17.5.23
- [x] Make posStart = location of stairs.   15.5.23
    - [x] I've now made posStart a member of floorStruct but it doesn't update the players position for some reason. 
            - [] the reason was something to do with casting the global current floor to local current floor etc... WEIRD stuff mang.
- [x] Localize currentFloor 12.5.23

23.5.23
- [x] 2 Stairs: Stairs currently only work in one direction, need to work both ways.