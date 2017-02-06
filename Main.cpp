#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <math.h>



using namespace std;

class Sorts {
public:
   int *input;
	int siz;
   Sorts(int *input, int s);
   void counting();
   void bucket();
   void radix();

};

Sorts::Sorts(int *in, int s) {
   input = new int[s];
   siz = s;
   for(int i = 0;i < siz; i++) {
      input[i] = in[i];
   }
}

void Sorts::counting() {

   int minimo = INT_MAX;
   int maximo = 0;
   int dif = INT_MAX;
   int aux = 0;

   for(int i = 0; i < siz; i++ )
	{
	    if( input[i] > maximo ){
         maximo = input[i];
	    }
	    if( input[i] < minimo ){
         minimo = input[i];
	    }
	}

	dif = (maximo - minimo) + 1;
	int *help = new int[dif];
	memset( help, 0, dif*sizeof(int));

	for( int i = 0; i < siz; i++ ){
      help[input[i] - minimo]++;
	}

	for(int i = minimo;i <= maximo;i++ )
	{
      while(help[i - minimo] )
      {
         input[aux++] = i;
         help[i - minimo]--;
	   }
	}
	free(help);
}

void Sorts::bucket() {
   vector<int> help[siz];
   int index = 0;
   int maximo = INT_MAX, minimo = INT_MIN, num;

   for(int i = 0; i < siz; i++ )
	{
	    if( input[i] > maximo ){
         maximo = input[i];
	    }
	    if( input[i] < minimo ){
         minimo = input[i];
	    }
	}

   int div = (int)ceil((maximo + 1.0)/siz);

   for (int i=0; i<siz; i++)
   {
      index = (int) floor(input[i]/div);
      help[index].push_back(input[i]);
   }

   for (int i=0; i<siz; i++){
      if(help[i].size() != 0) {
         sort(help[i].begin(), help[i].end());
      }
   }

   index = 0;
   for (int i = 0; i < siz; i++) {

         for (int j = 0; j < help[i].size(); j++) {
            input[index++] = help[i][j];
         }

   }
}

void Sorts::radix() {

    int maximo = input[0];
    for (int i = 1; i < siz; i++){
        if (input[i] > maximo){
            maximo = input[i];
        }
    }

    for (int e = 1; maximo/e > 0; e *= 10) {
      int output[siz];
      int i, help[10] = {0};
      for (i = 0; i < siz; i++)
         help[(input[i]/e)%10 ]++;

      for (i = 1; i < 10; i++){
         help[i] += help[i - 1];
      }

      for (i = siz - 1; i >= 0; i--)
      {
         output[help[(input[i]/e)%10 ] - 1] = input[i];
         help[(input[i]/e)%10 ]--;
      }
      for (i = 0; i < siz; i++) {
         input[i] = output[i];
      }
   }
}

int main(int argc, char* argv[]) {

   int chooseSort = atoi(argv[1]);
   int siz;
   cin >> siz;
   int *input = new int[siz];

   for(int i = 0; i < siz; i++) {
      cin >> input[i];
   }

	Sorts *sorts = new Sorts(input, siz);

	clock_t startTime, endTime;

	switch(chooseSort) {
   case 1:
      startTime = clock();
      sorts->counting();
      endTime = clock();
      break;
   case 2:
      startTime = clock();
      sorts->bucket();
      endTime = clock();
      break;
   case 3:
      startTime = clock();
      sorts->radix();
      endTime = clock();
      break;
	}

	for(int i = 0; i < siz; i++) {
		if(i != (siz - 1)) {
			cout << sorts->input[i] << endl;
		}
      else {
      	cout << sorts->input[i];
      }
	}

   //printf("\nTempo gasto: %4.0f ms\n\n",1000*(double)(endTime-startTime)/(double)(CLOCKS_PER_SEC));
   free(input);
   free(sorts->input);
   free(sorts);
}
