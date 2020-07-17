#include <stdio.h>
#include <stdlib.h>

float s_exp();
float m_exp(float sub_exp, char op);
float get_num();
char get_op();

int main() {
    char prompt = 'y';

    //basic while loop that checks for prompt value to continue
    while(prompt == 'y' || prompt == 'Y'){
        printf("Please input a simple arithmetic expression:");
        float answer = s_exp();

        printf("\nThe answer is %f \n", answer);

        //Continuation Prompt
        printf("Do you want to try another expression? Y = Yes, N = No.");
        scanf("%c", &prompt);

    }
}

float s_exp(void){
    //creating local variables
    float curNum = get_num();
    char curOp = get_op();

    //the end of the expression
    if(curOp == '\n'){
        return curNum;
    }

    //calling m_exp with the number and op
    float sub_expr = m_exp(curNum, curOp);
    curOp = get_op();

    //if the curOp is not the end of the espression
    while (curOp != '\n' ){
        if(curOp != '-' && curOp != '+'){
            sub_expr = m_exp(curNum,curOp);
        }//if curOp is + or -
        else{
            curNum = get_num();
            if(curOp == '-'){
                curOp = get_op();
                sub_expr = sub_expr - m_exp(curNum,curOp);
            }
            else if(curOp == '+'){
                curOp = get_op();
                sub_expr = sub_expr + m_exp(curNum,curOp);
            }
        }
        curOp = get_op();
    }
    return sub_expr;
}

float m_exp(float sub_exp, char op) {
    //creating local variables
    char next_op;
    float next_num;
    float new_s_exp;

    if(op != '+' && op != '-' && op != '\n'){
        //get the next number and operation
        next_num = get_num();
        next_op = get_op();

        if (op == '/') {
            //Confirming that it is nto attempting to divide by 0
            if (next_num != 0.0) {
                new_s_exp = sub_exp / next_num;
            }
            else if (next_num == 0.0) { // if it is attempting to divide by 0 it exits.
                printf("You cannot divide by 0.");
                exit(EXIT_FAILURE);
            }
        }
        else if (op == '*') {
            new_s_exp = sub_exp * next_num;
        }
            //Invalid operator
        else {
            printf("This operator is invalid.");
            exit(EXIT_FAILURE);
        }
        // recursive call
        return m_exp(new_s_exp, next_op);
    }
    //if the operator is + or - and not * or /
    else if (op == '+' || op == '-' || op == '\n'){
        //pushing the operator back into the stdin
        ungetc(op, stdin);
        return sub_exp;
    }

}


float get_num(){
    float curNum = ' ';

    //loop through spaces until float is found
    while(curNum == ' '){
        scanf("%f", &curNum);
    }
    if(curNum != ' '){
        return curNum;
    }
}

char get_op(){
    char curOp = ' ';

    //loop through spaces until operation is found
    while(curOp == ' '){
        scanf("%c", &curOp);
    }
    if(curOp != ' '){
        return curOp;
    }
}