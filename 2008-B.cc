#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define repi(i,a,b) for(int i = (a); i < (b); i++)

typedef long long ll;

/*2008年 ICPC国内予選 月曜土曜素因数*/

/*
  月曜素因数を探す 
  1以外
  7で割ると１余る数 8, 15, 22, 29, ..
  7で割ると６余る数 6, 13, 20, ..
 */

int main(){

  int inp, count=0, divisor[100000];
  int factor[100000], num=0;


  for(int i = 7; i <= 300000; i += 7){
    divisor[count++] = i-1;
    divisor[count++] = i+1;
  }

  factor[num++] = divisor[0];
  repi(i, 1, count){
    bool judge = true;
    for(int j=0; divisor[j] <= sqrt(divisor[i]) + 1; j++){
      if(divisor[i] % divisor[j] == 0){judge = false;  break;}
    }
    if(judge == true) factor[num++] = divisor[i]; 
  }
  
  while(cin >> inp && inp != 1){
   cout << inp << ":";
   repi(i, 0, num){
      if(inp % factor[i] == 0) cout << " " << factor[i];
    }
    cout << endl;
  }

  return 0;
}
