#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sData {
    char TimeDat[24][9];
    float TempArr[24][2], HumiArr[24], MotionArr[24][6];
};

void ReadDataFile(char *location, struct sData *sensorFileData);


int main() {
    struct sData sensorFileData;
    char filePath[100];
    int opt, fileOpt;

    do {
        for (int i = 0; i < 32; i++) {
            printf("-");
            if (i == 31) {
                printf("\n");
            }
        }
        printf("1 - Read File\n"
               "2 - Other stuff\n"
               "3 - Other stuff\n"
               "4 - Other stuff\n"
               "5 - Terminate Application\n");

        for (int i = 0; i < 32; i++) {
            printf("-");
            if (i == 31) {
                printf("\n");
            }
        }

        switch(opt) {
            case 1:
                printf("Which file do you want to load?\n 1 - Bedroom.txt\n 2 - Kitchen.txt\n 3 - LivingRoom.txt\n");
                scanf("%d", &fileOpt);
                switch(fileOpt) {
                    case 1:
                        printf("Enter Bedroom.txt file path: ");
                        scanf("%s", filePath);
                        ReadDataFile(filePath, &sensorFileData);
                        break;

                }
                break;
        }

        printf("\nPlease select an option: ");
        scanf("%d", &opt);
        printf("Enter file path: ");
        scanf("%s", filePath);
        ReadDataFile(filePath, &sensorFileData);

        for (int t = 0; t < 24; t++) {
            printf("\n\nTime: %s\n", sensorFileData.TimeDat[t]);
            printf("Temperatures: %.1f, %.1f\n", sensorFileData.TempArr[t][0], sensorFileData.TempArr[t][1]);
            printf("Humidity: %.1f\n", sensorFileData.HumiArr[t]);
            printf("Motion Sensors: ");
            for (int k = 0; k < 6; k++) {
                printf("%.1f, ", sensorFileData.MotionArr[t][k]);
            }
            printf("\n\n");
        }
    } while (opt != 5);
    return 0;
}


void ReadDataFile(char *location, struct sData *sensorFileData) {
    int t;
    FILE *fp; // assign to the file location
    fp = fopen(location, "r");
    if(fp == NULL)
    {
        printf("Error!\n");
        exit(1);
    }
    for(t=0; (t<24 && !feof(fp)); t++)
    {
        fscanf(fp, "%s", sensorFileData->TimeDat[t]); // 00:42:52 TimeDat[0] == 00:42:52
        //read temperatures
        fscanf(fp, "%f%f", &sensorFileData->TempArr[t][0], &sensorFileData->TempArr[t][1]);
        //read humidity
        fscanf(fp, "%f", &sensorFileData->HumiArr[t]);
        //read motion Data
        for (int k = 0; k < 6; k++)
            fscanf(fp, "%f", &sensorFileData->MotionArr[t][k]);
    }
    fclose(fp);
}