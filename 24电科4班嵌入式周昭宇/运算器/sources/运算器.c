#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义节点
typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

// 定义链栈
typedef struct LinkedStack {
    StackNode *top;
} LinkedStack;

// 初始化
LinkedStack *initStack() {
    LinkedStack *stack = (LinkedStack *)malloc(sizeof(LinkedStack));
    if (stack != NULL) {
        stack->top = NULL;
    }
    return stack;
}

// 销毁链栈
void freeStack(LinkedStack *stack) {
    StackNode *current = stack->top;
    StackNode *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(stack);
}

// 入栈
void push(LinkedStack *stack, int data) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// 出栈
int pop(LinkedStack *stack) {
    if (stack->top != NULL) {
        StackNode *temp = stack->top;
        int data = temp->data;
        stack->top = temp->next;
        free(temp);
        return data;
    }
    return -1;
}

// 找栈顶元素
int peek(LinkedStack *stack) {
    if (stack->top != NULL) {
        return stack->top->data;
    }
    return -1;
}

// 中缀表达式转后缀表达式
char a[256] = {0};
int i  = 0;
void char_put(char ch) {
    a[i++] = ch;
}

int priority(char ch) {
    int ret = 0;
    switch (ch) {
        case '+':
        case '-':
            ret = 1;
            break;
        case '*':
        case '/':
            ret = 2;
            break;
    }
    return ret;
}

int is_number(char ch) {
    return (ch >= '0' && ch <= '9');
}

int is_operator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int is_left(char ch) {
    return (ch == '(');
}

int is_right(char ch) {
    return (ch == ')');
}

int transform(char str[]) {
    LinkedStack *stack = initStack();
    int i = 0;
    while (str[i] != '\0') {
        if (is_number(str[i])) {
            if (is_number(str[i + 1])) {
                char_put(str[i]);
            } else {
                char_put(str[i]);
                char_put(' ');
            }
        } else if (is_operator(str[i])) {
            if (str[i + 1] == '0' && str[i] == '/') {
                printf("错误\n");
                freeStack(stack);
                return 0;
            }
            while (stack->top != NULL && priority(str[i]) <= priority(peek(stack))) {
                char_put(peek(stack));
                char_put(' ');
                pop(stack);
            }
            push(stack, str[i]);
        } else if (is_left(str[i])) {
            push(stack, str[i]);
        } else if (is_right(str[i])) {
            while (stack->top != NULL && !is_left(peek(stack))) {
                char_put(peek(stack));
                char_put(' ');
                pop(stack);
            }
            if (stack->top != NULL && is_left(peek(stack))) {
                pop(stack);
            } else {
                printf("没有匹配到左括号\n");
                freeStack(stack);
                return -1;
            }
        } else {
            printf("有不能识别的字符\n");
            freeStack(stack);
            return -1;
        }
        i++;
    }
    while (stack->top != NULL) {
        if (is_left(peek(stack))) {
            printf("有没有匹配到的'(',缺少')'\n");
            freeStack(stack);
            return -1;
        }
        char_put(peek(stack));
        char_put(' ');
        pop(stack);
    }
    freeStack(stack);
    return 1;
}

// 计算
int express(int left, int right, char op) {
    switch (op) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            if (right == 0) {
                return 999;
            }
            return left / right;
        default:
            break;
    }
    return -1;
}

int calculate(char str[]) {
    LinkedStack *stack = initStack();
    int i = 0;
    while (str[i] != '\0') {
        char a[6] = {0};
        int j = 0;
        if (is_number(str[i])) {
            while (is_number(str[i])) {
                a[j++] = str[i++];
            }
            int num = atoi(a);
            push(stack, num);
        } else if (is_operator(str[i])) {
            int right = pop(stack);
            int left = pop(stack);
            int ret = express(left, right, str[i]);
            if (ret == 999) {
                printf("错误\n");
                freeStack(stack);
                return 999;
            }
            push(stack, ret);
        } else if (str[i] == ' ')
		 {
         }
         else {
            printf("错误\n");
            freeStack(stack);
            break;
        }
        i++;
    }
    int result = pop(stack);
    freeStack(stack);
    return result;
}

int main() {
    char str[1024] = {0};
    printf("请输入四则运算表达式:\n");
    scanf("%s", str);
    int number = transform(str);
    if (number == 1) {
        int num = calculate(a);
        if (num != 999) {
            printf("%d\n", num);
        }
    }
    return 0;
}    
