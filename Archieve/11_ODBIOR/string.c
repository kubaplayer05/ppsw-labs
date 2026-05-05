#include "string.h"

#define NULL '\0'

void CopyString(char pcSource[], char pcDestination[]) {

    unsigned char ucSourceIndex;

    for(ucSourceIndex = 0; NULL != pcSource[ucSourceIndex]; ucSourceIndex++) {
        pcDestination[ucSourceIndex] = pcSource[ucSourceIndex];
    }

    pcDestination[ucSourceIndex] = NULL;
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[]) {

    unsigned char ucStringIndex;

    for(ucStringIndex = 0; NULL != pcStr1[ucStringIndex] || NULL != pcStr2[ucStringIndex]; ucStringIndex++) {
        if(pcStr1[ucStringIndex] != pcStr2[ucStringIndex]) {
            return DIFFERENT;
        }
    }

    return EQUAL;
}

void AppendString(char pcSourceStr[],char pcDestinationStr[]) {

    unsigned char ucStringIndex;

    for(ucStringIndex = 0; NULL != pcDestinationStr[ucStringIndex]; ucStringIndex++) {}
    CopyString(pcSourceStr, &pcDestinationStr[ucStringIndex]);
}

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar) {

    unsigned char ucStringIndex;

    for(ucStringIndex = 0; NULL != pcString[ucStringIndex]; ucStringIndex++) {
        if(cOldChar == pcString[ucStringIndex]) {
            pcString[ucStringIndex] = cNewChar;
        }
    }
}

void UIntToHexStr(unsigned int uiValue, char pcStr[]) {
    
    unsigned char ucTetradCounter;
    unsigned char ucTetradValue;

    pcStr[0] = '0';
    pcStr[1] = 'x';

    for(ucTetradCounter = 0; ucTetradCounter < 4; ucTetradCounter++) {
        ucTetradValue = (uiValue >> (4 * ucTetradCounter)) & 0x000F; 

        if(10 > ucTetradValue) {
            pcStr[5 - ucTetradCounter] = ucTetradValue + '0';
        } else {
            pcStr[5 - ucTetradCounter] = (ucTetradValue - 10) + 'A';
        }
    }

    pcStr[6] = NULL;
}

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue) {

    unsigned char ucCharCounter;
    unsigned char ucCharValue;

    *puiValue = 0;

    if(('0' != pcStr[0]) || ('x' != pcStr[1]) || (NULL == pcStr[2])) {
        return ERROR;
    }

    for(ucCharCounter = 2; NULL != pcStr[ucCharCounter]; ucCharCounter++) {
        ucCharValue = pcStr[ucCharCounter];
        
        if(6 == ucCharCounter) {
            return ERROR;
        }

        *puiValue = *puiValue << 4;

        if(('0' <= ucCharValue) && ('9' >= ucCharValue)) {
            *puiValue = *puiValue + (ucCharValue - '0');
        } else if(('A' <= ucCharValue) && ('F' >= ucCharValue)) {
            *puiValue = *puiValue + ((ucCharValue + 10) - 'A');
        } else {
            return ERROR;
        }
    }

    return OK;
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]) {
    unsigned char ucCharCounter;

    for(ucCharCounter = 0; NULL != pcDestinationStr[ucCharCounter]; ucCharCounter++) {}
    UIntToHexStr(uiValue, pcDestinationStr + ucCharCounter);
}
