#include <stdio.h>

void E(char *in, char *out);
int find(char *param);

char capLetters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char rainbowTable[913952][4];
char returnedRainbowTable[4];

int main() {

    int a, b, c, d, counter = 0, returnedIndex;

    char hashPass[4];
    char needHashPass[4];

    for (a = 0; a < 26; a++){
        for (b = 0; b < 26; b++){
            for (c = 0; c < 26; c++){
                for (d = 0; d < 26; d++){

                    char pass[4] = {capLetters[a], capLetters[b], capLetters[c], capLetters[d]};

                    E(pass, hashPass);

                    //if (counter % 20000 == 0) {
                        printf("Hash: %s Original Pass: %s\n", hashPass, pass);
                    //}

                    rainbowTable[counter][0] = hashPass[0];
                    rainbowTable[counter][1] = hashPass[1];
                    rainbowTable[counter][2] = hashPass[2];
                    rainbowTable[counter][3] = hashPass[3];

                    rainbowTable[counter+1][0] = pass[0];
                    rainbowTable[counter+1][1] = pass[1];
                    rainbowTable[counter+1][2] = pass[2];
                    rainbowTable[counter+1][3] = pass[3];

                    counter+=2;

                }
            }
        }
    }

    printf("Enter the hash of the pass you wish to retrieve: ");
    scanf("%s", needHashPass);

    returnedIndex = find(needHashPass);

    if(returnedIndex != 1000000) {
        returnedRainbowTable[0] = rainbowTable[returnedIndex + 1][0];
        returnedRainbowTable[1] = rainbowTable[returnedIndex + 1][1];
        returnedRainbowTable[2] = rainbowTable[returnedIndex + 1][2];
        returnedRainbowTable[3] = rainbowTable[returnedIndex + 1][3];

        printf("The password is %s\n", returnedRainbowTable);
    }

    return 0;
}

// DES replacement cipher
// The function E takes 4 bytes from *in as input and
// writes 4 bytes to *out
void E(char *in, char *out) {
    out[0]=(in[0]&0x80)^(((in[0]>>1)&0x7F)^((in[0])&0x7F));
    out[1]=((in[1]&0x80)^((in[0]<<7)&0x80))^(((in[1]>>1)&0x7F)^((in[1])&0x7F));
    out[2]=((in[2]&0x80)^((in[1]<<7)&0x80))^(((in[2]>>1)&0x7F)^((in[2])&0x7F));
    out[3]=((in[3]&0x80)^((in[2]<<7)&0x80))^(((in[3]>>1)&0x7F)^((in[3])&0x7F));
}

int find(char *param){

    int z;

    for(z = 0; z < 913952; z+=2){

        if ((rainbowTable[z][0] == param[0]) && (rainbowTable[z][1] == param[1]) && (rainbowTable[z][2] == param[2]) && (rainbowTable[z][3] == param[3])) {
            return z;
        }

    }

    printf("Password not found\n");
    return 1000000;

}
