/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

extern int Compare(const char* op1, const char* op2);

unsigned int FindMinIndexElement(char* data, size_t num, size_t len, int (*Compare) (const char*, const char* )){
    unsigned int i=0;
    unsigned int founded_index = 0;    
    for(i=1;i<num;i++){
        if (Compare(data + founded_index*len, data + i*len) > 0){
            founded_index = i;
        }
    }
    return founded_index;
}

char* FindMinElement(char* data, size_t num, size_t len, int (*Compare) (const char*, const char* )){
    unsigned int i=0;
    unsigned int founded_index = 0;    
    for(i=1;i<num;i++){
        if (Compare(data + founded_index*len, data + i*len) > 0){
            founded_index = i;
        }
    }
    return data + founded_index*len;
}

unsigned int FindMaxIndexElement(char* data, size_t num, size_t len, int (*Compare) (const char*, const char* )){
    unsigned int i=0;
    unsigned int founded_index = 0;    
    for(i=1;i<num;i++){
        if (Compare(data + founded_index*len, data + i*len) < 0){
            founded_index = i;
        }
    }
    return founded_index;
}

char* FindMaxElement(char* data, size_t num, size_t len, int (*Compare) (const char*, const char* )){
    unsigned int i=0;
    unsigned int founded_index = 0;    
    for(i=1;i<num;i++){
        if (Compare(data + founded_index*len, data + i*len) < 0){
            founded_index = i;
        }
    }
    return data + founded_index*len;
}

void Swap(char* data_1, char* data_2, unsigned int len){
    char tmp_data[len];
    memcpy(tmp_data, data_1, len);
    memcpy(data_1, data_2, len); 
    memcpy(data_2, tmp_data, len);
}

//Bubble sort O(N*N), stable
void BubbleSort(char* data, size_t num, size_t len, int (*Compare) (const char*, const char* )){
     unsigned int i=0;
     unsigned int j=0;
     bool exchanged = false;
     unsigned int offset =0;
     char* ptr_1;
     char* ptr_2;
     char data_tmp[len];
     
     for (j=1;j<num;j++){
          exchanged = false;
          offset = 0;
          for (i=0; i<num-j; i++){
                ptr_1 = data+offset;
                ptr_2 = data+offset+len;
                if (Compare(ptr_1, ptr_2) > 0){
                    memcpy(data_tmp, ptr_1, len);
                    memcpy(ptr_1, ptr_2, len);
                    memcpy(ptr_2, data_tmp, len);
                    exchanged = true;
                }
                offset += len;
          }
          if (!exchanged) break;
     }
}

//Inserting sort O(N*N), stable
void InsertSort(char* data, size_t num, size_t len, int (*compare) (const char*, const char* )){
     char* ptr_1;
     unsigned int offset = 0;
     char data_sorted[num*len];
     memset(data_sorted,0,sizeof(data_sorted));
     unsigned int new_index = 0;

     for (unsigned int i=0; i<num; i++){          
        ptr_1 = data+offset;
        for (unsigned int j=0; j<=new_index; j++){
            char* ptr_data = data_sorted + len*j;
            if (j==new_index){
                 memcpy(ptr_data, ptr_1, len);
            } else if (Compare(ptr_1, ptr_data) < 0){
                for(unsigned int k=new_index; k!=j;k--){
                    memcpy(data_sorted+k*len, data_sorted+(k-1)*len, len);
                }
                memcpy(ptr_data, ptr_1, len);
                break;
            }
        }
        new_index++;
        offset += len;
    }
    memcpy(data, data_sorted, num*len);
}

//Selecting sort O(N*N), stable
void SelectSort(char* data, size_t num, size_t len, int (*compare) (const char*, const char* )){
    unsigned int index = 0;
    char* min_ptr;
    char data_tmp[len];
    
    for (unsigned int i=0; i<num; i++){ 
        min_ptr = FindMinElement(data+index, num-i, len, compare);
        memcpy(data_tmp, data+index, len);
        memcpy(data+index, min_ptr, len);
        memcpy(min_ptr, data_tmp, len);
        index += len;
    }
}

void QuickSort(char* data, size_t num, size_t len, int (*Compare) (const char*, const char* )){
    if (num <= 1) return;

    //put less elements to the left and bigger\equal to the right
    unsigned int div_index = 0;
    unsigned int pair_index = num-1;
    unsigned int tmp;
    for (unsigned int i=0; i<num-1; i++){    
        int stat = Compare(data + div_index*len, data + pair_index*len);
        if ((stat > 0 && pair_index > div_index) || (stat <= 0 && pair_index < div_index)){
            Swap(data + div_index*len, data + pair_index*len, len);
            tmp = div_index; 
            div_index = pair_index;
            pair_index = tmp;
        }
        if (div_index < pair_index) pair_index--;
        else pair_index++;
    }
    //call QSort for the left and right parts
    QuickSort(data, div_index, len, Compare); //left
    QuickSort(data+(div_index+1)*len, num-div_index-1, len, Compare); //right
}

void MergeSort(char* data, size_t num, size_t len, int (*Compare) (const char*, const char* )){
    if (num <= 1) return;
    size_t num_right;
    if (num % 2 != 0) num_right = num/2 + 1;
    else num_right = num/2;
    
    MergeSort(data, num/2, len, Compare);
    MergeSort(data + num/2*len, num_right, len, Compare);
    
    char data_tmp[num*len];
    
    unsigned int i=0;
    unsigned int j=0;
    unsigned int offset =0;
    while (i<num/2 && j<num_right){
        if (Compare(data + i*len, data + (num/2)*len + j*len) < 0){
            memcpy(data_tmp + offset, data + i*len, len);
            i++;
            offset += len;
        } else {
            memcpy(data_tmp + offset, data + (num/2)*len + j*len, len);
            j++;
            offset += len;
        }
    }
    if (i == num/2) memcpy(data_tmp + offset, data + (num/2)*len + j*len, (num_right - j)*len);
    else            memcpy(data_tmp + offset, data + i*len, (num/2 - i)*len);
    memcpy(data, data_tmp, num*len);
}