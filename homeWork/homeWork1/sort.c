#include "sort.h"


void popSort(int *p,int len,int control(int ,int )){
    for (int i = 0; i < len-1 ; ++i) {
        for (int j = 0; j < len-i-1; ++j) {
            if (control(p[j],p[j+1])){
                p[j]= p[j]^p[j+1];
                p[j+1]= p[j]^p[j+1];
                p[j]= p[j]^p[j+1];
            }
        }
    }
}