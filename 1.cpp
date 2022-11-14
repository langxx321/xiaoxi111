// �����ڸտ�ʼ�Ͽε�ʱ����ܹ�һ��Сѧ���������Զ����ɳ�������ӣ���ʵ������Ҫ��
// �١��ܹ��Զ���������������ϰ��
// �ڡ����Զ�����Ŀ����
// �ۡ��û�����ѡ�������
// �ܡ��û��������������ʮ���ڡ������ڵȣ�
// �ݡ��û�ѡ���Ƿ������š��Ƿ���С��
// �ޡ��û�ѡ�������ʽ����������ļ�����ӡ���ȣ�
// �ߡ�������ṩͼ���û����棨�����Լ�����ѡ�����������������Ϊ����

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "math.h"

#define GetRandomNum(maxNum) rand() % 10001 / 10000.0 * maxNum
#define GetRandomOp(opChar) opChar[rand() % strlen(opChar)]
/**
 * @brief ����������ϰ��
 * @param n ����������ϰ������
 * @param m ��ϰ���м���
 * @param opChar �����
 * @param maxNum ��������������
 * @param isFloat �����
 * @param isBracket �Ƿ�������
 * @param printFlag 0:��ӡ����Ļ 1:��ӡ���ļ�
 * @return char** �������ɵ�������ϰ��
 */
char** Generate(int n, int m, char* opChar, int maxNum, int isFloat, int isBracket, int printFlag);
//  84 88 84 85 82 87 87 89 85 90
int main()
{

    //printf("������������ϰ��������");
    //int n;
    //scanf("%d", &n);
    //printf("��������ϰ�⼸�����㣺");
    //int m;
    //scanf("%d", &m);
    //printf("�������������");
    //char opChar[10];
    //scanf("%s", opChar);
    //printf("�����ò���������������");
    //int maxNum;
    //scanf("%d", &maxNum);
    //printf("������������Ƿ�ΪС��(1:��С�� 0:��С��):");
    //int isFloat;
    //scanf("%d", &isFloat);
    //printf("�������Ƿ�������(1:������ 0:������):");
    //int isBracket;
    //scanf("%d", &isBracket);
    //printf("�����������ʽ(1:ֱ�Ӵ�ӡ��Ļ�� 0:�����result.txt��):");
    //int printFlag;
    //scanf("%d", &printFlag);
    //char** result = Generate(n, m, opChar, maxNum, isFloat, isBracket, printFlag);
    char opChar[10] = "+-";
    char **result = Generate(3, 4, opChar, 10, 0, 1, 1);
    return 0;
}

char** Generate(int n, int m, char* opChar, int maxNum, int isFloat, int isBracket, int printFlag)
{
    //����ʱ�����������������
    srand((unsigned)time(0));
    // ��̬��������ʽ�ڴ�
    char** result = (char**)malloc(sizeof(char*) * n);

    for (int i = 0; i < n; i++)
    {
        double firstItem = GetRandomNum(maxNum);
        // firstItemת��Ϊ�ַ���
        char* tempFormula = (char*)malloc(sizeof(char) * m * 10);
        isFloat ? sprintf(tempFormula, "%.2f", firstItem) : sprintf(tempFormula, "%d", (int)firstItem);
        for (int j = 0; j < m - 1; j++)
        {
            char* tempItem = (char*)malloc(sizeof(char) * 10);
            // ��������������Ȼ��ƴ��
            sprintf(tempItem, " %c ", GetRandomOp(opChar));
            strcat(tempFormula, tempItem);

            // ����һ�������
            double nextItem = 0;
            if (tempItem[1] == '/')
            {
                while (nextItem == 0 || nextItem < 1)
                {
                    nextItem = GetRandomNum(maxNum);
                }
            }
            else
            {
                nextItem = GetRandomNum(maxNum);
            }

            isFloat ? sprintf(tempItem, "%.2f", nextItem) : sprintf(tempItem, "%d", (int)nextItem);
            strcat(tempFormula, tempItem);

            free(tempItem);
        }
        strcat(tempFormula, " =\0");
        result[i] = tempFormula;
    }
    // �ж��Ƿ���Ҫ�������
    if (isBracket)
    {
        for (int i = 0; i < n; i++)
        {
            // ��ȡ������ʽ�е������
            char* op = (char*)malloc(sizeof(char) * 10);
            int opIndex = 0;
            for (int j = 0; j < strlen(result[i]); j++)
            {
                if (strchr(opChar, result[i][j]))
                {
                    op[opIndex++] = result[i][j];
                }
            }
            op[opIndex] = '\0';

            // ����������ֻ�мӼ��������ڼ��ź����������
            // ����������ֻ�г˳��������ڳ��������������
            // �����������мӼ����ͳ˳��������ڼӼ��������������
            if ((strchr(op, '+') || strchr(op, '-')) && !strchr(op, '*') && !strchr(op, '/'))
            {
                // ���opǰһ��������Ǽ��ţ����Һ�һ�����������\0�����ں�һ�������ǰ���������
                for (int j = 0; j < strlen(op); j++)
                {
                    if (op[j] == '-' && op[j + 1] != '\0')
                    {
                        // �ҵ����ŵ�λ��
                        int minusIndex = 0;
                        for (int k = 0; k < strlen(result[i]); k++)
                        {
                            if (result[i][k] == '-')
                            {
                                minusIndex = k;
                                break;
                            }
                        }
                        int nextOpIndex = 0;
                        int OpCount = 0;
                        for (int k = minusIndex + 1; k < strlen(result[i]); k++)
                        {
                            // �ж�result[i][k]�ǲ���+-*/=�е�һ��
                            // printf("%s\n", strchr(opChar, result[i][k]));
                            int isOp = strchr(opChar, result[i][k]) ? 1 : 0;
                            if (result[i][k] == '=' || isOp)
                            {
                                if (OpCount)
                                {
                                    nextOpIndex = k;
                                    break;
                                }
                                OpCount++;
                            }
                        }
                        // ��minusIndex�����������
                        char* temp = (char*)malloc(sizeof(char) * m * 10);
                        memset(temp, 0, sizeof(char) * m * 10);
                        strncpy(temp, result[i], minusIndex + 1);
                        strcat(temp, " (");
                        strncat(temp, result[i] + minusIndex + 1, nextOpIndex - minusIndex - 1);
                        strcat(temp, ") ");
                        strncat(temp, result[i] + nextOpIndex, strlen(result[i]) - nextOpIndex);
                        // �ͷ�ԭ�����ڴ棬��ֹ�ڴ�й©
                        free(result[i]);
                        result[i] = temp;
                        // printf("1: %s\n", result[i]);

                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            if ((strchr(op, '*') || strchr(op, '/')) && !strchr(op, '+') && !strchr(op, '-'))
            {
                // ���opǰһ��������ǳ��ţ����Һ�һ�����������\0�����ں�һ�������ǰ���������
                for (int j = 0; j < strlen(op); j++)
                {
                    if (op[j] == '/' && op[j + 1] != '\0')
                    {
                        // �ҵ����ŵ�λ��
                        int divideIndex = 0;
                        for (int k = 0; k < strlen(result[i]); k++)
                        {
                            if (result[i][k] == '/')
                            {
                                divideIndex = k;
                                break;
                            }
                        }
                        int nextOpIndex = 0;
                        int OpCount = 0;
                        for (int k = divideIndex + 1; k < strlen(result[i]); k++)
                        {
                            // �ж�result[i][k]�ǲ���+-*/=�е�һ��
                            // printf("%s\n", strchr(opChar, result[i][k]));
                            int isOp = strchr(opChar, result[i][k]) ? 1 : 0;
                            if (result[i][k] == '=' || isOp)
                            {
                                if (OpCount)
                                {
                                    nextOpIndex = k;
                                    break;
                                }
                                OpCount++;
                            }
                        }
                        // printf("\n*/ %d %d %d\n", i, divideIndex, nextOpIndex);
                        // ��divideIndex�����������
                        char* temp = (char*)malloc(sizeof(char) * m * 10);
                        memset(temp, 0, sizeof(char) * m * 10);

                        strncpy(temp, result[i], divideIndex + 1);
                        strcat(temp, " (");
                        strncat(temp, result[i] + divideIndex + 1, nextOpIndex - divideIndex - 1);
                        strcat(temp, ") ");
                        strncat(temp, result[i] + nextOpIndex, strlen(result[i]) - nextOpIndex);
                        // �ͷ�ԭ�����ڴ棬��ֹ�ڴ�й©
                        free(result[i]);
                        result[i] = temp;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            if ((strchr(op, '+') || strchr(op, '-')) && (strchr(op, '*') || strchr(op, '/')))
            {
                // ���opǰһ��������Ǽ��ţ����Һ�һ�����������\0�����ں�һ�������ǰ���������
                for (int j = 0; j < strlen(op); j++)
                {
                    if ((op[j] == '*' || op[j] == '/') && op[j + 1] != '\0')
                    {
                        // �ҵ����ŵ�λ��
                        int minusIndex = 0;
                        for (int k = 0; k < strlen(result[i]); k++)
                        {
                            if (result[i][k] == '*' || result[i][k] == '/')
                            {
                                minusIndex = k;
                                // printf("%d %d\n", i, minusIndex);
                                break;
                            }
                        }
                        int nextOpIndex = -1;
                        int OpCount = 0;
                        for (int k = minusIndex + 1; k < strlen(result[i]); k++)
                        {
                            // �ж�result[i][k]�ǲ���+-*/=�е�һ��
                            int isOp = strchr("+-", result[i][k]) ? 1 : 0;
                            if (result[i][k] == '=' || isOp)
                            {
                                if (OpCount)
                                {
                                    nextOpIndex = k;
                                    OpCount++;
                                    break;
                                }
                                OpCount++;
                            }
                            else
                            {
                                OpCount = 1;
                                break;
                            }
                        }
                        if (OpCount == 1)
                        {
                            break;
                        }
                        // ��minusIndex�����������
                        char* temp = (char*)malloc(sizeof(char) * m * 10);
                        memset(temp, 0, sizeof(char)* m * 10);
                        strncpy(temp, result[i], minusIndex + 1);
                        strcat(temp, " (");
                        strncat(temp, result[i] + minusIndex + 1, nextOpIndex - minusIndex - 1);
                        strcat(temp, ") ");
                        strncat(temp, result[i] + nextOpIndex, strlen(result[i]) - nextOpIndex);
                        free(result[i]);
                        result[i] = temp;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }
    // ������
    FILE* fp = fopen("result.txt", "w");
    for (int i = 0; i < n; i++)
    {
        // ���printFlagΪ1:ֱ�Ӵ�ӡ��Ļ�� 0:�����result.txt��
        if (printFlag)
        {
            printf("%s\n", result[i]);

        }
        else
        {
            fprintf(fp, "%s\n", result[i]);
        }
    }
    fclose(fp);
    return result;
}
