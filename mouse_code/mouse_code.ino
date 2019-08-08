//=====Arrays Declarations=====
/*
char Maze[11][11] = { {'.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.'},
{'|', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|'},
{'.', ' ', '.', ' ', '.', '-', '.', '-', '.', ' ', '.'},
{'|', ' ', '|', ' ', '|', ' ', ' ', ' ', '|', ' ', '|'},
{'.', ' ', '.', ' ', '.', '-', '.', ' ', '.', ' ', '.'},
{'|', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|'},
{'.', ' ', '.', ' ', '.', '-', '.', '-', '.', ' ', '.'},
{'|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', '|'},
{'.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.'},
{'|', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
{'.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.'} };
*/
char Maze[11][11] = { {'.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.'},
{'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
{'.', ' ', '.', ' ', '.', '-', '.', '-', '.', ' ', '.'},
{'|', ' ', '|', ' ', '|', ' ', ' ', ' ', '|', ' ', '|'},
{'.', ' ', '.', ' ', '.', '-', '.', ' ', '.', ' ', '.'},
{'|', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
{'.', ' ', '.', ' ', '.', '-', '.', '-', '.', ' ', '.'},
{'|', ' ', '|', ' ', '|', ' ', ' ', ' ', '|', ' ', '|'},
{'.', ' ', '.', '_', '.', ' ', '.', ' ', '.', ' ', '.'},
{'|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
{'.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.'} };
char FFA[11][11] = { {'.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.'},
{'|', 'e', ' ', 'd', ' ', 'c', ' ', 'd', ' ', 'e', '|'},
{'.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.'},
{'|', 'd', ' ', 'c', ' ', 'b', ' ', 'c', ' ', 'd', '|'},
{'.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.'},
{'|', 'c', ' ', 'b', ' ', 'a', ' ', 'b', ' ', 'c', '|'},
{'.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.'},
{'|', 'd', ' ', 'c', ' ', 'b', ' ', 'c', ' ', 'd', '|'},
{'.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.'},
{'|', 'e', ' ', 'd', ' ', 'c', ' ', 'd', ' ', 'e', '|'},
{'.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.'} };
//=====Declarations & Inital values=====
int x = 0;
int y = 0;
int xp = 1;
int yp = 9;
int i = 0;
char direc = 'S';
char S_value;
char D_value;
char L_value;
char R_value;
char current_value;
int U_turn;
int total;
//=====Print Maze Function=====
void PrintMaze()
{
//=====Print-out the maze=====
x = 0;
y = 0;
while(x < 11)
{
Serial.print(Maze[y][x]);
Serial.print(' ');
x++;
if(x > 10)
{
Serial.print("\n");
y++;
x = 0;
if(y > 10)
{
x = 11;
}
}
}
Serial.print("\n");
Serial.print("\n");
}
//=====Print LHW Function=====
void PrintFFA()
{
//=====Print-out the FFA=====
x = 0;
y = 0;
while((x < 11) && (i < 33))
{
Serial.print(FFA[y][x]);
Serial.print(' ');
x++;
if(x > 10)
{
Serial.print("\n");
y++;
x = 0;
if(y > 10)
{
x = 11;
}
}
}
Serial.print("\n");
Serial.print("\n");
}
void setup()
{
Serial.begin(9600); // for serial monitor output
delay(500);
Serial.print("\n");
//=====MAZE Titel=====
Serial.print("MAZE");
Serial.print("\n");
PrintMaze(); //Call Print Maze Function
//=====LHW Titel=====
Serial.print("Fill Flood Algorithem");
Serial.print("\n");
current_value = FFA[yp][xp];
//FFA[yp][xp] = 'M';
PrintFFA(); //Call Print FFA Function
FFA[yp][xp] = 'M';
}
void loop()
{
while(i < 40)
{
S_value = 125;
L_value = 125;
R_value = 125;
D_value = 125;
if(direc == 'S')
{
FFA[yp-1][xp] = Maze[yp-1][xp];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp+1][xp] = Maze[yp+1][xp];
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(S_value <= L_value && S_value <= R_value && S_value != 125){direc = 'S';}
else if(L_value <= S_value && L_value <= R_value && L_value != 125){direc = 'L';}
else if(R_value <= S_value && R_value <= L_value && R_value != 125){direc = 'R';}
else{direc = 'D';}
}
else if(direc == 'D')
{
FFA[yp+1][xp] = Maze[yp+1][xp];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp-1][xp] = Maze[yp-1][xp];
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(D_value <= L_value && D_value <= R_value && D_value != 125){direc = 'D';}
else if(R_value <= D_value && R_value <= L_value && R_value != 125){direc = 'R';}
else if(L_value <= D_value && L_value <= R_value && L_value != 125){direc = 'L';}
else{direc = 'S';}
}
else if(direc == 'L')
{
FFA[yp+1][xp] = Maze[yp+1][xp];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp-1][xp] = Maze[yp-1][xp];
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(L_value <= S_value && L_value <= D_value && L_value != 125){direc = 'L';}
else if(S_value <= L_value && S_value <= D_value && S_value != 125){direc = 'S';}
else if(D_value <= L_value && D_value <= S_value && D_value != 125){direc = 'D';}
else{direc = 'R';}
}
else if(direc == 'R')
{
FFA[yp+1][xp] = Maze[yp+1][xp];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp-1][xp] = Maze[yp-1][xp];
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(R_value <= S_value && R_value <= D_value && R_value != 125){direc = 'R';}
else if(D_value <= R_value && D_value <= S_value && D_value != 125){direc = 'D';}
else if(S_value <= R_value && S_value <= D_value && S_value != 125){direc = 'S';}
else{direc = 'L';}
}
PrintFFA(); //Call Print FFA Function
if (xp == 5 && yp == 5){i = 50;}
if(i != 50)
{
if(direc == 'S')
{
if(S_value > current_value)
{
current_value = S_value + 1;
}
FFA[yp][xp] = current_value;
yp = yp - 2;
}
else if(direc == 'D')
{
if(D_value > current_value)
{
current_value = D_value + 1;
}
FFA[yp][xp] = current_value;
yp = yp + 2;
}
else if(direc == 'L')
{
if(L_value > current_value)
{
current_value = L_value + 1;
}
FFA[yp][xp] = current_value;
xp = xp - 2;
}
else if(direc == 'R')
{
if(R_value > current_value)
{
current_value = R_value + 1;
}
FFA[yp][xp] = current_value;
xp = xp + 2;
}
current_value = FFA[yp][xp];
FFA[yp][xp] = 'M';
//PrintFFA(); //Call Print FFA Function
i++;
}
}
i = 0;
Serial.println("==========================");
FFA[5][5] = 'a';
delay(200);
PrintFFA(); //Call Print FFA Function
//if(direc=='S'){direc = 'D'} //might needed (change back the direction becose it inverted in the last proccess)
Serial.println("==========================");
i = 0;
xp = 5;
yp = 5;
while(i < 40)
{
S_value = 125;
L_value = 125;
R_value = 125;
D_value = 125;
if(direc == 'S')
{
FFA[yp-1][xp] = Maze[yp-1][xp];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp+1][xp] = Maze[yp+1][xp];
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(S_value <= L_value && S_value <= R_value && S_value != 125){direc = 'S';}
else if(L_value <= S_value && L_value <= R_value && L_value != 125){direc = 'L';}
else if(R_value <= S_value && R_value <= L_value && R_value != 125){direc = 'R';}
else{direc = 'D'; U_turn = 1;}
}
else if(direc == 'D')
{
FFA[yp+1][xp] = Maze[yp+1][xp];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp-1][xp] = Maze[yp-1][xp];
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(D_value <= L_value && D_value <= R_value && D_value != 125){direc = 'D';}
else if(R_value <= D_value && R_value <= L_value && R_value != 125){direc = 'R';}
else if(L_value <= D_value && L_value <= R_value && L_value != 125){direc = 'L';}
else{direc = 'S'; U_turn = 1;}
}
else if(direc == 'L')
{
FFA[yp+1][xp] = Maze[yp+1][xp];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp-1][xp] = Maze[yp-1][xp];
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(L_value <= S_value && L_value <= D_value && L_value != 125){direc = 'L';}
else if(S_value <= L_value && S_value <= D_value && S_value != 125){direc = 'S';}
else if(D_value <= L_value && D_value <= S_value && D_value != 125){direc = 'D';}
else{direc = 'R'; U_turn = 1;}
}
else if(direc == 'R')
{
FFA[yp+1][xp] = Maze[yp+1][xp];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp-1][xp] = Maze[yp-1][xp];
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(R_value <= S_value && R_value <= D_value && R_value != 125){direc = 'R';}
else if(D_value <= R_value && D_value <= S_value && D_value != 125){direc = 'D';}
else if(S_value <= R_value && S_value <= D_value && S_value != 125){direc = 'S';}
else{direc = 'L'; U_turn = 1;}
}
PrintFFA(); //Call Print FFA Function
if (xp == 1 && yp == 9){i = 50;}
total = 0;
if(S_value==125){total = total + 1;}
if(D_value==125){total = total + 1;}
if(L_value==125){total = total + 1;}
if(R_value==125){total = total + 1;}
if(total < 2)
{
U_turn = 0;
}
if(direc == 'S')
{
if(S_value < FFA[yp][xp] && U_turn==0)
{
FFA[yp-2][xp] = FFA[yp][xp] + 1;
}
yp = yp - 2;
}
else if(direc == 'D')
{
if(D_value < FFA[yp][xp] && U_turn==0)
{
FFA[yp+2][xp] = FFA[yp][xp] + 1;
}
yp = yp + 2;
}
else if(direc == 'L')
{
if(L_value < FFA[yp][xp] && U_turn==0)
{
FFA[yp][xp-2] = FFA[yp][xp] + 1;
}
xp = xp - 2;
}
else if(direc == 'R')
{
if(R_value < FFA[yp][xp] && U_turn==0)
{
FFA[yp][xp+2] = FFA[yp][xp] + 1;
}
xp = xp + 2;
}
//current_value = FFA[yp][xp];
//FFA[yp][xp] = 'M';
//PrintFFA(); //Call Print FFA Function
i++;
//PrintFFA(); //Call Print FFA Function
}
Serial.println("==========================");
i = 0;
xp = 1;
yp = 9;
direc = 'S';
FFA[yp][xp] = 'X';
while(i < 40)
{
S_value = 125;
L_value = 125;
R_value = 125;
D_value = 125;
if(direc == 'S')
{
FFA[yp-1][xp] = Maze[yp-1][xp];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp+1][xp] = Maze[yp+1][xp];
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(S_value <= L_value && S_value <= R_value && S_value != 125){direc = 'S';}
else if(L_value <= S_value && L_value <= R_value && L_value != 125){direc = 'L';}
else if(R_value <= S_value && R_value <= L_value && R_value != 125){direc = 'R';}
else{direc = 'D';}
}
else if(direc == 'D')
{
FFA[yp+1][xp] = Maze[yp+1][xp];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp-1][xp] = Maze[yp-1][xp];
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(D_value <= L_value && D_value <= R_value && D_value != 125){direc = 'D';}
else if(R_value <= D_value && R_value <= L_value && R_value != 125){direc = 'R';}
else if(L_value <= D_value && L_value <= R_value && L_value != 125){direc = 'L';}
else{direc = 'S';}
}
else if(direc == 'L')
{
FFA[yp+1][xp] = Maze[yp+1][xp];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp-1][xp] = Maze[yp-1][xp];
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(L_value <= S_value && L_value <= D_value && L_value != 125){direc = 'L';}
else if(S_value <= L_value && S_value <= D_value && S_value != 125){direc = 'S';}
else if(D_value <= L_value && D_value <= S_value && D_value != 125){direc = 'D';}
else{direc = 'R';}
}
else if(direc == 'R')
{
FFA[yp+1][xp] = Maze[yp+1][xp];
FFA[yp][xp+1] = Maze[yp][xp+1];
FFA[yp][xp-1] = Maze[yp][xp-1];
FFA[yp-1][xp] = Maze[yp-1][xp];
if(FFA[yp][xp+1] == ' '){R_value = FFA[yp][xp+2];}
if(FFA[yp-1][xp] == ' '){S_value = FFA[yp-2][xp];}
if(FFA[yp+1][xp] == ' '){D_value = FFA[yp+2][xp];}
if(FFA[yp][xp-1] == ' '){L_value = FFA[yp][xp-2];}
if(R_value <= S_value && R_value <= D_value && R_value != 125){direc = 'R';}
else if(D_value <= R_value && D_value <= S_value && D_value != 125){direc = 'D';}
else if(S_value <= R_value && S_value <= D_value && S_value != 125){direc = 'S';}
else{direc = 'L';}
}
//PrintFFA(); //Call Print FFA Function
//if (xp == 3 && yp == 3){i = 50;}
if(i != 50)
{
if(direc == 'S')
{
//FFA[yp][xp] = 'X';
yp = yp - 2;
}
else if(direc == 'D')
{
//FFA[yp][xp] = 'X';
yp = yp + 2;
}
else if(direc == 'L')
{
//FFA[yp][xp] = 'X';
xp = xp - 2;
}
else if(direc == 'R')
{
//FFA[yp][xp] = 'X';
xp = xp + 2;
}
//current_value = FFA[yp][xp];
FFA[yp][xp] = 'X';
//PrintFFA(); //Call Print FFA Function
i++;
PrintFFA(); //Call Print FFA Function
if (xp == 5 && yp == 5){i = 50;}
}
}
i = 0;
//delay(500);
PrintFFA(); //Call Print FFA Function
//delay(500);
PrintFFA(); //Call Print FFA Function
while(1);
}
