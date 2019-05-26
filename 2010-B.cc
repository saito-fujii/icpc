#include <iostream>
#include <algorithm>

using namespace std;
#define repi(i, a, b) for (int i = (a); i < (b); i++)

/*2010年 ICPC 国内予選 迷図と命ず*/

bool map[70][70][4];
int map_step[70][70];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

int search (int w, int h){
  bool finish = false;
  int step = 1;

  repi(i,0,h) repi(j,0,w) map_step[i][j] = -1;

  map_step[0][0] = 1;
  step = 1;

  while(map_step[h-1][w-1] == -1){
    finish = true;
    repi(i, 0, h){
      repi(j, 0, w){
        if(map_step[i][j] == step){
          repi(k,0,4) {
            if(map[i][j][k] == true){
              if(map_step[i+dy[k]][j+dx[k]] == -1)
                map_step[i+dy[k]][j+dx[k]] = step+1;                
            }
          }
        }
      }
    }
    step++;
    repi(i, 0, h)
      repi(j, 0, w) if(map_step[i][j] == step) finish = false;

    if(finish) return 0;
  }

  return step;
}


int main(){

  int w, h;
  int tmp, step;

  while(cin >> w >> h && (h || w)){
    repi(i, 0, w){
      map[0][i][0] = false; map[h-1][i][2] = false;
    }
    repi(i,0, h){
      map[i][0][3] = false; map[i][w-1][1] = false;
    }

    repi(i, 0, 2*h-1){
      if(i % 2 == 0){
        repi(j,0,w-1){
          cin >> tmp;
          if(tmp == 1){
            map[i/2][j][1] = false;
            map[i/2][j+1][3] = false;
          } else {
            map[i/2][j][1] = true;
            map[i/2][j+1][3] = true;
          }
        }
      } else {
        repi(j, 0, w){
          cin >> tmp;
          if(tmp == 1){
            map[i/2][j][2] = false;
            map[i/2+1][j][0] = false;
          } else {
            map[i/2][j][2] = true;
            map[i/2+1][j][0] = true;
          }
        }
      }
    }
    cout << search(w,h) << endl;

    /*  repi(i, 0, h){
        repi(j, 0, w){
        repi(k,0,4) cout << map[i][j][k] << " ";
        cout << endl;
      }
    }

    cout << "*****" << endl;
    repi(i, 0, h){
      repi(j,0,w)
        cout << map_step[i][j] << " ";
      cout << endl;
    }
    */
  }
  return 0;
}
