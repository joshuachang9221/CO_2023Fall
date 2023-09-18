#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* forward declaration */
int cmd_q(char*);
int cmd_help(char*);
int cmd_tee(char*);
int cmd_fibo(char*);
int cmd_sort(char*);
int cmd_palin(char*);


typedef struct {
    char* name;
    char* description;
    int (*handler)(char*);  // function pointer
} cmd_t;

cmd_t cmd_table[] = {
    {"q", "exit the interactive interface", &cmd_q},
    {"help", "print useful information about supported commands", &cmd_help},
    {"tee", "receive the arguments and print it to standard output", &cmd_tee},
    {"fibo", "Print the nth fibonacci number Fn , where n is input of user", &cmd_fibo},
    {"sort", "sort the given sequence of integer numbers, where the sequence is input of user", &cmd_sort},
    {"palin", "print whether the given string (user input) is palindrome", &cmd_palin},
};

#define ARRLEN(s) (sizeof(s) / sizeof(*s))
#define NUM_CMD ARRLEN(cmd_table)
#define SORT_ARRLEN 1000

int cmd_q(char* args) { return -1; }

int cmd_help(char* args) {
    if (args == NULL) {
        for (int i = 0; i < NUM_CMD; i++) {
            printf("%s: %s\n", cmd_table[i].name, cmd_table[i].description);
        }
        return 0;
    }

    int i;
    for (i = 0; i < NUM_CMD; i++) {
        if (strcmp(args, cmd_table[i].name) == 0) {
            printf("%s\n", cmd_table[i].description);
            break;
        }
    }
    if (i == NUM_CMD) {
        printf("%s\n", "help: Unknown command!");
    }
    return 0;
}

int cmd_tee(char* args){
  if (args == NULL) {
        printf("%s\n", "tee:No input received!");
        return 0;
    }
    printf("%s\n", args);
    return 0;
}

int fibo_cal(int n){
        if( n==1 || n==2 )return 1;
        if( n >= 3 )return (fibo_cal(n-1) + fibo_cal(n-2));
}

int cmd_fibo(char* args){
    printf("%d\n",fibo_cal(atoi(args)));
    return 0;
}


void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[i]) {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}

int cmd_sort(char* args){
    char input_arr[SORT_ARRLEN*2] ;
    strncpy(input_arr,args,SORT_ARRLEN*2);

    int arr[SORT_ARRLEN];
    int n = 0;

    char* token = strtok(input_arr, " ");
    while (token != NULL && n < SORT_ARRLEN) {
        arr[n++] = atoi(token);
        token = strtok(NULL, " ");
    }
    bubbleSort(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

int cmd_palin(char* args){
    int len = strlen(args);
    int i, j= len - 1;
    for (i = 0; i < j; i++, j--) {
        if (args[i] != args[j]) {
            printf("%s is not a palindrome.\n", args);
            return 0; // Not a palindrome
        }
    }
    printf("%s is palindrome.\n", args);
    return 0; // Palindrome
}

char* rl_gets(void) {
    static char* line = NULL;  // note this is static variable in a function

    if (line) {
        free(line);
        line = NULL;
    }

    line = readline("(CO2023) ");
    if (line && *line) {
        add_history(line);
    }

    return line;
}

int main(void) {
    for (char* read_line; (read_line = rl_gets()) != NULL;) {
        char* read_line_end = read_line + strlen(read_line) + 1;

        char* cmd = strtok(read_line, " ");
        if (cmd == NULL) {
            /* empty input -> continue and read new line */
            continue;
        }

        char* args = read_line + strlen(cmd) + 1;
        if (args >= read_line_end) {
            args = NULL;
        }

        int i;
        for (i = 0; i < NUM_CMD; i++) {
            if (strcmp(cmd, cmd_table[i].name) == 0) {
                if (cmd_table[i].handler(args) < 0) {
                    return 0;
                }
                break;
            }
        }
        if (i == NUM_CMD) {
            printf("%s\n", "Unsupported command!");
        }
    }
}
