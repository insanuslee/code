//
//  main.c
//  LR
//
//  Created by insanus on 2017/3/16.
//  Copyright © 2017年 insanus. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM (((unsigned)-1)>>1)

/*堆栈结点*/
struct node {
    char* data;
    struct node* next;
    struct node* before;
};

typedef struct {
    struct node* begin;
    struct node* last;
    int size;
}* stack;



/*lib*/
int getindexofchar(char* str, char c);
char* chartostr(char c);
void draw(char* sign, char* ch, const char* input, char* other);

/*stack*/
stack init_stack();
char* pop(stack list);
void push(char* input, stack list);
void foreach(stack list);
char* nforeach(stack list);
char* getnode(stack list, int x);
int getsize(stack list);
char* getlast(stack list);



/*堆栈方法*/
stack init_stack() {
    /*新建堆栈*/
    stack temp = (stack)malloc(sizeof(*(stack)0));
    temp->size = 0;
    temp->begin = NULL;
    temp->last = NULL;
    return temp;
}

char* getlast(stack list) {
    if (list->last != NULL)
        return list->last->data;
    return NULL;
}

char* pop(stack list) {
    /*pop*/
    if(list->size == 0)
        return NULL;
    struct node* temp;
    char* data;
    temp = list->last;
    data = temp->data;
    if (temp->before != NULL)
        temp->before->next = NULL;
    list->last = temp->before;
    list->size --;
    free(temp);
    return data;
}

void push(char* input, stack list) {
    /*push*/
    struct node* ground = (struct node*)malloc(sizeof(struct node));
    struct node* temp;
    if (list->size == 0) {
        list->begin = ground;
        list->last = ground;
        temp = NULL;
    } else {
        temp = list->last;
        temp->next = ground;
        list->last = ground;
    }
    ground->next = NULL;
    ground->data = input;
    ground->before = temp;
    list->size ++;
}

void foreach(stack list) {
    /*遍历*/
    struct node* temp = list->begin;
    for (int size = list->size, n = 0;n < size; n ++) {
        printf("%s\n", temp->data);
        temp = temp->next;
    }
}

char* nforeach(stack list) {
    /*遍历*/
    struct node* temp = list->begin;
    char* string = (char *)malloc((MAXNUM)*sizeof(char));
    for (int size = list->size, n = 0;n < size; n ++) {
        string = strcat(string,temp->data);
        temp = temp->next;
    }
    return string;
}

char* getnode(stack list, int x) {
    struct node* temp = list->begin;
    for (int size = list->size, n = 0;n < size; n ++) {
        if (x == n)
            return temp->data;
        temp = temp->next;
    }
    return NULL;
}

int getsize(stack list) {
    return list->size;
}


//int main(int argc, const char * argv[]) {
//    /*堆栈单元测试*/
//    stack list = init_stack();
//    push("第一条测试数据", list);
//    push("第二条测试数据", list);
//    push("第三条测试数据", list);
//    push("第四条测试数据", list);
//    printf("%s\n",nforeach(list));
//    printf("有%d条数据\n", getsize(list));
//    pop(list);
//    printf("%s\n",nforeach(list));
//    printf("有%d条数据\n", getsize(list));
//
//
///*output:
// 第一条测试数据第二条测试数据第三条测试数据第四条测试数据
// 有4条数据
// 第一条测试数据第二条测试数据第三条测试数据
// 有3条数据
//*/
//
//
//}

void Go(const char* inputs) {
    
    stack gotos = init_stack();
    stack action = init_stack();
    
    
    char* index[] = {"E=E+E", "E=E*E", "E=(E)", "E=i"};
    char* finals = "i+*()#";
    char* nofinals = "E";
    
    
                  /*i + * ( ) # */
    push(          "S3    S2    "          , gotos);
    push(          "  S4S5    - "          , gotos);
    push(          "S3    S2    "          , gotos);
    push(          "R4R4R4R4R4R4"          , gotos);
    push(          "S3    S2    "          , gotos);
    push(          "S3    S2    "          , gotos);
    push(          "  S4S5  S9  "          , gotos);
    push(          "  R1S5  R1R1"          , gotos);
    push(          "  R2R2  R2R2"          , gotos);
    push(          "R3R3R3R3R3R3"          , gotos);
    
    push(          "1"          , action);
    push(          " "          , action);
    push(          "6"          , action);
    push(          " "          , action);
    push(          "7"          , action);
    push(          "8"          , action);
    push(          " "          , action);
    push(          " "          , action);
    push(          " "          , action);
    push(          " "          , action);
    
    
    stack sign = init_stack();
    stack ch = init_stack();
    
    push("0", sign);
    draw(nforeach(sign), nforeach(ch), &inputs[0], "初始化");
    
    char* temp;
    for (int n = 0; 1; n ++) {
        
        int m =getindexofchar(finals, inputs[n])*2;
        if (m != -1) {
            
            
            temp = getnode(gotos, getlast(sign)[0]-'0');
            if (temp[m] == 'S') {
                push(chartostr(temp[m+1]), sign);
                push(chartostr(inputs[n]), ch);
                draw(nforeach(sign), nforeach(ch), &inputs[n+1], "移进");
                
            } else if (temp[m] == 'R') {
                
                
                if (getsize(sign) != 1)
                    n --;
                int forindex = temp[m+1] -'0' - 1;
                int innerlen = (int)(strlen(index[forindex])) - 2;
                /*E=i  ==> 3 - 2*/
                
                int tempinner = innerlen;
                
                
                while(tempinner --) {
                    pop(sign);
                    pop(ch);
                }
                
                push(chartostr(index[forindex][0]), ch);
                
                
                int status = getlast(sign)[0] - '0';
                
                
                int y = getindexofchar(nofinals, index[forindex][0]);
                char* mislead = chartostr(getnode(action, status)[y]);
                push(mislead, sign);
                
                
                
                draw(nforeach(sign), nforeach(ch), &inputs[n+1], "归约");
            } else if (temp[m] == ' ') {
                printf("ERROR\n");
                return;
            } else if (temp[m] == '-') {
                printf("ACC\n");
                return;
            }
        } else {
            printf("ERROR\n");
            return;
        }
    }
    
}

/*lib*/
int getindexofchar(char* str, char c) {
    unsigned long len = strlen(str);
    for (int n = 0; n < len; n ++) {
        if (str[n] == c)
            return n;
    }
    return -1;
}

char* chartostr(char c) {
    char* string = (char *)malloc(2*sizeof(char));
    string[0] = c;
    string[1] = '\0';
    return string;
}

void draw(char* sign, char* ch, const char* input, char* other) {
    printf("%-15s\t#%-15s\t%-15s\t%s\n", sign, ch, input, other);
}

int main(int argc, const char * argv[]) {
    char inputs[1000];
    scanf("%s", inputs);
    Go(inputs);
    return 0;
}
