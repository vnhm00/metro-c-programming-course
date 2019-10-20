#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define MAX 2000

typedef struct chunk_
{
    uint8_t *data;
    uint16_t size;
    uint16_t capacity;
    uint16_t crc;
} chunk;

bool fileDataGenerate(char filename[]);
bool chunkRead(char filename[], chunk *chunks, const int chunksize, int *chunknumber);
uint16_t crc16(const uint8_t* data_p, unsigned int length);

bool fileDataGenerate(char filename[])
{
    FILE *file;
    int i = 0, ran = 0;
    char ch = '\0';

    file = fopen(filename,"wb"); //open writing binary file
    if (file == NULL) return false; //if not find file return false

    srand(time(NULL));
    i = rand()%1000 + 1000; //get a random value from 1000 to 2000
    for (; i > 0 ; i--)
    {
        ran = (rand()%2550)%255; //pick random value for r (from 0 to 255)
        ch = ran;
        fwrite(&ch, sizeof(char), 1, file); //write into file in binary mode
    }

    fclose(file); //close file after writing
    return true; //return true means writing successful
}

bool chunkRead(char filename[],chunk *chunks, const int chunksize, int *chunknumber)
{
    FILE *file;
    int count = 0, num = 0;
    char ch = '\0';

    file = fopen(filename,"rb"); //open reading binary file
    if (file == NULL) return false; //if not find file return false

    chunks[num].data = (uint8_t *)malloc(sizeof(uint8_t) * chunksize);

    while (!feof(file))
    {
        fread(&ch, sizeof(char), 1, file); //read from file in binary mode
        chunks[num].data[count] = ch; //assign data for chunk
        if (count == chunksize - 1) //if chunk-size byte are read then move on to the next chunk
        {
            chunks[num].size = chunksize;
            chunks[num].capacity = chunksize;
            chunks[num].crc = 0;
            count = 0;
            num++;
            chunks[num].data = (uint8_t *)malloc(sizeof(uint8_t) * chunksize);
        }
        else count++; //else continue increment count
    }

    if (count >= 0) //deal with left over data which is not fit into a chunk-size chunk
    {
        chunks[num].size = count - 1;
        chunks[num].capacity = chunksize;
        chunks[num].crc = 0;
    }

    *chunknumber = num;
    fclose(file); //close file after reading
    return true;
}

uint16_t crc16(const uint8_t* data_p, unsigned int length)
{
    uint8_t x;
    uint16_t crc = 0xFFFF;
    while (length--)
    {
        x = crc >> 8 ^ *data_p++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x <<5)) ^ ((uint16_t)x);
    }
    return crc;
}

int main()
{
    while (true)
    {
        char filename[10]; //string to hold the name of the file
        chunk *chunks = {'\0'};
        int i = 0, chunksize = 0;

        //ASK USER TO ENTER THE NAME OF THE FILE AND CHUNK SIZE
        printf("Type the name of the file (.bin): ");
        scanf("%s",filename);
        printf("Enter the chunk size: ");
        scanf("%d", &chunksize);
        int chunknumber = MAX / chunksize + 2;
        chunks = malloc(chunknumber * sizeof *chunks);

        if (!fileDataGenerate(filename)) return 0;
        if (!chunkRead(filename, chunks, chunksize, &chunknumber)) return 0;

        //PRINT AS REQUESTED
        for (i = 0 ; i <= chunknumber ; i++)
            printf("%s: %-7d %s: %-8d %s: %-7d %s: %.4X\n", "Chunk number" ,i+1, "Chunk capacity", chunks[i].capacity, "Chunk size", chunks[i].size, "CRC", crc16(chunks[i].data, chunks[i].size));

        free(chunks);

        printf("\nAnother file is to be read? (yes/no): ");
        scanf("%s",filename);
        if (strcmp(filename,"yes")!=0) return 0;
    }

    return 0;
}

