/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//stores integers(memory values) with ready access to lowest one 
class minheap{
private:
    //~dynamically resizing~ array
    int* arr;
    //points to the index where the next element can be inserted
    int size;
    int capacity;
    
    //useless variables to make this size be equal to HeapNode
    int tmp1,tmp2,tmp3;

    void resize(){
        if (size==capacity){
            capacity=capacity*2;
            int*tmp = new int[capacity];
            for(int i=0;i<size;i++){tmp[i]=arr[i];}
            delete arr;arr=tmp; 
            return;
        }

        if (size<(capacity/4)){
            capacity=(capacity/4);
            int*tmp = new int[capacity];
            for(int i=0;i<size;i++){tmp[i]=arr[i];}
            delete arr; arr=tmp; 
            return;
        }
    }

    static int inline Parent(int &index){return(index-1)/2;}
    static int inline LChild(int &index){return(2*index+1);}
    static int inline RChild(int &index){return(2*index+2);}

    void bubble_up(){
        int current=size-1;
        int parent=Parent(current);
        int tmp;

        while(current and arr[current]<arr[parent]){
            tmp=arr[parent];arr[parent]=arr[current];arr[current]=tmp;
            current=parent;parent=Parent(current);
        }
    }

    void bubble_down(){
        int current=0;
        int child,tmp;

        while (current<size){
            child = LChild(current);
            if (child<size and arr[child]<arr[current]){
                tmp=arr[current];arr[current]=arr[child];arr[child]=tmp;
                current=child;
                continue;
            }
            child = RChild(current);
            if (child<size and arr[child]<arr[current]){
                tmp=arr[current];arr[current]=arr[child];arr[child]=tmp;
                current=child;
                continue;
            }
            return;
        }
    }
public:
    minheap(int memory_size){
        arr= new int[memory_size+1];
        for (int i=0;i<memory_size;i++){arr[i]=i;}
        size=memory_size; capacity=memory_size+1;
    }
    minheap(){
        arr=new int[1];
        size=0;capacity=1;
    }
    ~minheap(){delete arr;}

    int get_min(){return arr[0];}

    void push_heap(int inp){
        resize();
        arr[size]=inp;size++;
        bubble_up();
    }

    void pop(){
        if(size==0){return;}
        arr[0]=arr[size-1];size--;
        resize();
        bubble_down();
    }

};

//Write your code below this line

MinHeap::MinHeap(){
    //HeapNode is 32bytes, make sure minheap is also 32 then!
    static_assert(sizeof(HeapNode)==sizeof(minheap));
    root= (HeapNode*) new minheap();
}

void MinHeap::push_heap(int num){
    return ((minheap*)root)->push_heap(num);
}

int MinHeap::get_min(){
    return ((minheap*)root)->get_min();
}

void MinHeap::pop(){
    return ((minheap*)root)->pop();
}

MinHeap::~MinHeap(){
    delete ((minheap*)root);
}

// #include<iostream>
// int main(){
//     MinHeap h;
//     for (int i:{8,4,5,12,3}){
//         h.push_heap(i);
//     }
//     for (int i:{1,2,3,4,5}){
//         std::cout<<h.get_min()<<endl;
//         h.pop();
//     }
    
// }