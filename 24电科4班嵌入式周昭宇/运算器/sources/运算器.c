#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����ڵ�
typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

// ������ջ
typedef struct LinkedStack {
    StackNode *top;
} LinkedStack;

// ��ʼ��
LinkedStack *initStack() {
    LinkedStack *stack = (LinkedStack *)malloc(sizeof(LinkedStack));
    if (stack != NULL) {
        stack->top = NULL;
    }
    return stack;
}

// ������ջ
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

// ��ջ
void push(LinkedStack *stack, int data) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// ��ջ
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

// ��ջ��Ԫ��
int peek(LinkedStack *stack) {
    if (stack->top != NULL) {
        return stack->top->data;
    }
    return -1;
}

// ��׺���ʽת��׺���ʽ
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
                printf("����\n");
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
                printf("û��ƥ�䵽������\n");
                freeStack(stack);
                return -1;
            }
        } else {
            printf("�в���ʶ����ַ�\n");
            freeStack(stack);
            return -1;
        }
        i++;
    }
    while (stack->top != NULL) {
        if (is_left(peek(stack))) {
            printf("��û��ƥ�䵽��'(',ȱ��')'\n");
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

// ����
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
                printf("����\n");
                freeStack(stack);
                return 999;
            }
            push(stack, ret);
        } else if (str[i] == ' ')
		 {
         }
         else {
            printf("����\n");
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
    printf("����������������ʽ:\n");
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
