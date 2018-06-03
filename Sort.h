#pragma once
#include <cassert>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
#define POSITIONS_INT 10
void InsertSort(int* a,int len)
{
    int begin = 1;
    while(begin < len)
    {
        int key = a[begin];
        for(int i = 0;i<begin;i++)
        {
            if(a[i]>key)
            {
                for(int j = begin-1;j>=i;j--)
                {
                    a[j+1] = a[j];
                }
                a[i] = key;
                break;
            }
        }
        begin++;
    }
}

void ShellSort(int* a,int len)
{
    int gap = len;
    while(gap > 1)  //避免死循环
    {
        gap = gap/3 + 1;
        for(int i = 0;i<len-gap;i++)
        {
            int end = i;   //当前的位置
            int tmp = a[end + gap];   //当前位置的下一个，插入的key
            while(end>=0 && a[end] > tmp)   //满足条件，进行插入移动
            {
                a[end+gap] = a[end];
                end -= gap;        //end
            }
            a[end+gap] = tmp;          //把key放入合适的位置
        }
    }
}

void SelectSort(int* a,size_t len)
{
    assert(a);
    int begin = 0;
    int end = len;
    int max = 0;
    int min = 0;
    while(begin < end)
    {
        max = begin,min = begin;
        for(int i = begin;i < end;i++)
        {
            if(a[i]>a[max])
            {
                max = i;
            }
            if(a[i]<a[min])
            {
                min = i;
            }
        }
        swap(a[min],a[begin]);  //ps!!the two codes's sort is impotant
        if(max != begin)
        swap(a[max],a[end-1]);  
        begin++;
        end--;
    } 
}

void Adjustdown(int* a,int root,int len)
{
    int parent = root;
    int child = 2*parent+1;
    while(child<len)
    {   
        if(child<len-1 && a[child] < a[child+1])
        child++;
        if(a[parent] < a[child])
        swap(a[parent],a[child]);
        parent = child;                                                                                                                                    
        child = 2*parent + 1;
    }   
                        
}

void CreateHeap(int* a,int len)
{
    for(int i = 0;i<(len-1)/2;i++)
    {
        Adjustdown(a,i,len);
    }
}

void HeapSort(int* a,int len)
{
    for(int i = 0;i<len;i++)
    {
        CreateHeap(a,len);
    }
    int end = len-1;
    while(end>0)
    {
        swap(a[0],a[end]);
        Adjustdown(a,0,end);
        end--;
    }
}

void BubbleSort(int* a,size_t len)
{
    int end = len-1;
    while(end > 0)
    {
        bool exchange = false;
        for(int i = 0;i < end;i++)
        {
            if(a[i]>a[i+1])
            {
            swap(a[i],a[i+1]);
            exchange = true;
            }
        }
        if(exchange == false)
            return;
        else
            exchange = false;
        end--;
    }
}

int GetMidIndex(int* a,int begin,int end);
int PartSort1(int* a,int begin,int end)
{
    int mid = GetMidIndex(a,begin,end);   //三数取中
    swap(a[end],a[mid]);
    int key = a[end];
    int tmp = end;   // 2 1 4 3 1.5 
    while(begin < end) 
    {
        while(begin < end && a[begin] <= key)
            ++begin;
        while(begin < end && a[end] >= key)
            --end;
        swap(a[begin],a[end]);
    }
    swap(a[begin],a[tmp]);
    return begin;
}

int PartSort2(int* a,int begin,int end)
{
    int key = a[end];
    while(begin < end)
    {
        while(begin < end && a[begin] <= key)
        {
            ++begin;
        }
        a[end] = a[begin];
        while(begin < end && a[end] >= key)
        {
            --end;
        }
        swap(a[begin],a[end]);
    }
    a[begin] = key;
    return begin;
}

int PartSort3(int *a,int begin,int end)
{
    if(begin < end)
    {
        int key = a[end];
        int prev = begin-1;
        int cur = begin;
        while(cur < end)
        {
           while(a[cur]<key && ++prev != cur)
           {
            swap(a[prev],a[cur]);
           }
           cur++;
        }
        swap(a[++prev],a[end]);
        return prev;
    }
    return -1;

}

void QuickSort_non(int* a,int begin,int end)
{
    stack<int> s;
    int mid = 0;
    if(begin < end)
    {
        s.push(end);
        s.push(begin);
        while(!s.empty())
        {
            int left = s.top();
            s.pop();
            int right = s.top();
            s.pop();
            mid = PartSort1(a,left,right);
            if(left<mid-1)
            {
                s.push(mid-1);
                s.push(left);
            }
            if(mid+1<right)
            {
                s.push(right);
                s.push(mid+1);
            }
        }
    }
}

int GetMidIndex(int* a,int begin,int end)
{
    assert(a);
    int mid = begin+((end-begin)>>1);

    if(a[end] > a[mid])
    {
        if(a[mid] > a[begin])
            return mid;
        else
        {
            if(a[end] > a[begin])
                return begin;
            else
                return end;
        }
    }
    else//end<=mid
    {
        if(a[end]>a[begin])
            return end;
        else   //end <=begin
        {
            if(a[begin] > a[mid])
                return mid;
            else
                return begin;
        }
    }
}

void QuickSort(int* a,int left,int right)
{
    assert(a);
    if(left>=right)
        return;
    if(right - left +1 < 10)
        InsertSort(a+left,right-left+1);
    int mid = PartSort1(a,left,right);
    QuickSort(a,left,mid-1);
    QuickSort(a,mid+1,right);
}

void _MergeSort(int* a,int left,int right,int* tmp)
{
    //出口  如果只有一个 或者 没有了 
    if(left >= right)
        return;
    //划分
    int mid = left + ((right-left)>>1);
    _MergeSort(a,left,mid,tmp);
    _MergeSort(a,mid+1,right,tmp);
    //开始归并
    int index = left;
    int begin1 = left,end1 = mid;
    int begin2 = mid+1,end2 = right;
    while(begin1 <= end1 && begin2 <= end2)
    {
        if(a[begin1] <= a[begin2])
            tmp[index++] = a[begin1++];
        else
            tmp[index++] = a[begin2++];
    }
    while(begin1<=end1)
    {
        tmp[index++] = a[begin1++];
    }
    while(begin2<=end2)
    {
        tmp[index++] = a[begin2++];
    }
    index = left;
    //放回
    while(left <= right)
    {
        a[left++] = tmp[index++];
    }
}
void MergeSort(int* a,int len)
{
    int* tmp = new int[len];
    _MergeSort(a,0,len-1,tmp);
    delete[] tmp;
}

void MergeSort_non(int* a,int len)
{
    int gap = 1;
    int* tmp = new int[len];
    while(gap<=len)
    {
        int i = 0;
        for(i = 0;i<len-2*gap+1;i+=(2*gap))
        {
            _MergeSort(a,i,i+gap,tmp);
        }
        if(i<len-gap+1)
        {
            _MergeSort(a,i,len-1,tmp);
        }
        gap*=2;
    }
    delete[] tmp;
}

void CountSort(int* a,int len)
{
    int max = a[0];
    int min = a[0];
    for(int i = 1;i<len;i++)
    {
        if(a[i] > max)
            max = a[i];
        if(a[i] < min)
            min = a[i];
    }
    int range = max-min+1;
    vector<int> hashtable;
    hashtable.resize(range,0);
    
    //统计
    for(int i = 0;i<len;i++)
    {
        hashtable[a[i]-min]++;
    }
    int index = 0;

    for(int i = 0;i<range;i++)
    {
        while(hashtable[i]--)
        {
            a[index++] = i+min;

        }
    }
}

int GetPosition(int num,size_t pos)
{
    int tmp = 1;
    for(size_t i = 0;i<pos;i++)
    {
        tmp*=10;
    }
    return (num/tmp) % 10;
    
}
void RadixSort(int* a,size_t lenth) //32位编译器下最大10位数
{
    vector<vector<int> > radixVec;
    radixVec.resize(10);
    for(size_t pos = 0;pos<POSITIONS_INT;pos++)
    {
        for(size_t j = 0;j<lenth;j++)       //放入基数序列
        {
        int index = GetPosition(a[j],pos);    
        radixVec[index].push_back(a[j]);
        }
        size_t k1 = 0;
        for(size_t k = 0;k<POSITIONS_INT;k++)
        {
            for(size_t k2 = 0;k2 < radixVec[k].size();k1++,k2++)
                if(k1 < lenth)
                a[k1] = radixVec[k][k2];
        }
        for(size_t i = 0;i<POSITIONS_INT;i++)
            radixVec[i].clear();
    }
}
/*void TestSortTime()
{
    srand(time(NULL));
    int N = 1000000;
    int *a = new int[N];
    int *b = new int[N];
    for(int i = 0;i<N;i++)
    {
        a[i] = rand();
        b[i] = rand();
    }
    ShellSort(a,N);
}
*/

