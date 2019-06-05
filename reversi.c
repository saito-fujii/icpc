#include <stdio.h>

#define WHITE 0
#define BLACK 1
#define NON 2

int board[10][10];
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int color_rev[2] = {1, 0};
char color_str[2][10] = {"WHITE", "BLACK"};

void print_board(){
  int i, j;

  printf("\t ");
  for(i = 1; i <= 8; i++)
    printf("  %d", i);
  printf("\n");

  for(i = 1; i < 9 ; i++){
    printf("\t  ");
    for(j = 0; j < 8; j++) printf(" --");
    printf("\n");
    for(j = 1; j < 9 ; j++){
      if(j == 1) printf("\t%d |", i);
      if(board[i][j] == WHITE) printf("○ |");
      if(board[i][j] == BLACK) printf("● |");
      if(board[i][j] == NON) printf("　|");
    }
    printf("\n");
  }
  printf("\t  ");
  for(j = 0; j < 8; j++) printf(" --");
  printf("\n\n");
}

void init_board(){

  int i, j;

  for(i = 0 ; i < 10 ; i++){
    for(j = 0; j < 10 ; j++){
      board[i][j] = NON;
    }
  }

  board[4][4] = BLACK;
  board[5][5] = BLACK;
  board[4][5] = WHITE;
  board[5][4] = WHITE;
}

void reverse_stone(int check[][8], int color){
  int i, j, tmp;

  for(i = 0; i < 8 ; i++){
    for(j = 0; j < 8; j++){
      tmp = check[i][j];
      if(tmp == 0) break;
      board[tmp/8 + 1][tmp%8 + 1] = color;
    }
  }
}

int puts_stone(int x, int y, int color){

  int i, j, k;
  int tmp, check[8][8], count[8] = {0, 0, 0, 0, 0, 0, 0, 0};


  //check
  if(x < 1 || y < 1 || x > 8 || y > 8) {
    printf("\n範囲外なんだよな\n");
    return 0;
  }
  if(board[y][x] != NON) {
    printf("\nそこ置いてあるんだよな\n");
    return 0;
  }

  for(i=0 ; i < 8; i++) for(j = 0 ; j < 8 ; j++) check[i][j] = -1;

  for(i = 0 ; i < 8; i++){//方向
    for(j = 1; j <=  8 ; j++){//深さ
      tmp = board[y+(dy[i]*j)][x+(dx[i]*j)];
      if(tmp == color){
        if(count[i] == 0) check[i][0] = -1;
        break;
      } else if (tmp == color_rev[color]){
        check[i][j-1] = 8*(y-1) + 8*j*dy[i] + x + j*dx[i] - 1;
        count[i]++;
      } else {
        check[i][0] = -1;
        count[i] = 0;
        break;
      }
    } 
  }

  for(i = 0, tmp = 0 ; i < 8 ; i++) tmp += count[i];
  if(tmp > 0){
      board[y][x] = color;
      reverse_stone(check, color);
    }
      
  return tmp;
  
}

int main(){

  int x, y, tmp;
  int turn = BLACK;
  int score[2] = {2, 2};

  init_board();
  print_board(); 
  printf("ゲームを始めるぞ〜〜\n");

  while(1){
    printf("%sのターンだぞ〜\n", color_str[turn]);
    printf("(x, y) :");
    scanf("%d %d", &x, &y);
    if((tmp = puts_stone(x, y, turn)) == 0){
      printf("そこは置けないよ？\n");
    } else {
      turn = color_rev[turn];
      print_board();
      score[turn] += tmp + 1;
      score[color_rev[turn]] -= tmp;
      printf("Score \n WHITE : %d \t BLACK : %d\n\n", score[WHITE], score[BLACK]);
    }

  }
  return 0;
}
