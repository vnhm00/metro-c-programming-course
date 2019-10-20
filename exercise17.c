#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct car_record
{
    char manu[10]; //make of the car
    char model[12]; //model of the car
    int price; //price of the car
    float emission; //co2 emission of the car
} car;

void init(char *filename, car *cars)
{
    cars[0] = (car){.manu = "Toyota",.model = "Aygo",.price = 14000,.emission = 113.4};
    cars[1] = (car){.manu = "Dacia",.model = "Duster",.price = 15000,.emission = 150.1};
    cars[2] = (car){.manu = "Volk",.model = "Transporter",.price = 55000,.emission = 167};
    cars[3] = (car){.manu = "Mercedes",.model = "ML320",.price = 35000,.emission = 159.8};
    cars[4] = (car){.manu = "Opel",.model = "Zafira",.price = 30000,.emission = 159.5};

    cars[5] = (car){.manu = "Volk",.model = "Tiguan",.price = 35000,.emission = 200};
    cars[6] = (car){.manu = "Opel",.model = "Insignia",.price = 32000,.emission = 106.1};
    cars[7] = (car){.manu = "Chevrolet",.model = "Cruze",.price = 20000,.emission = 160};
    cars[8] = (car){.manu = "Ford",.model = "FocusSW",.price = 22000,.emission = 115};
    cars[9] = (car){.manu = "Renault",.model = "Fluence",.price = 21300,.emission = 137.4};

    /*TESTING DATA
    {"Ford", "Focus", 35000, 90},
    {"Seat", "Ibiza", 20000, 102},
    {"Dacia", "Logan", 15000,124}*/

    FILE *file;
    file = fopen(filename,"wb"); //open writing binary file
    if (file == NULL) return false; //if not find file return false
    char ch = '-';

    //Print data to the file in binary mode
    for (int i = 0; i < 10; i++)
    {
        ch = '-';
        fwrite(cars[i].manu, 1,sizeof(cars[i].manu),file);
        fwrite(&ch, sizeof(char), 1, file);
        fwrite(cars[i].model, 1,sizeof(cars[i].model),file);
        fwrite(&ch, sizeof(char), 1, file);
        fwrite(&cars[i].price,sizeof(int),1,file);
        fwrite(&ch, sizeof(char), 1, file);
        fwrite(&cars[i].emission,sizeof(float),1,file);
        ch = '\n';
        fwrite(&ch, sizeof(char), 1, file);
    }
    fclose(file); //close file after writing
}

void allCarsPrint(char *filename)
{
    FILE *file;

    char ch = '\0'; int count = 0;
    file = fopen(filename,"rb"); //open reading binary file
    if (file == NULL) return false; //if not find file return false

    printf("\n--- ALL CARS ---\n");
    printf("%-10s%10s%19s%19s\n","MANUFACTURER","MODEL","PRICE","CO2 EMISSION");

    //Basically read data from the file
    while (!feof(file))
    {
        if (count < 2) fread(&ch, sizeof(char), 1, file); //read from file in binary mode
        if (ch == '-')
        {
            printf("%7s"," ");
            count++;
        } else printf("%c",ch);

        if (count == 2 && ch == '-')
        {
            int i = 0;
            fread(&i, sizeof(int), 1, file);
            printf("%d",i);
            fread(&ch, sizeof(char), 1, file);
        } else if (count == 3 && ch == '-')
        {
            float i = 0;
            fread(&i, sizeof(float), 1, file);
            printf("%.2f",i);
            fread(&ch, sizeof(char), 1, file);
        } else if (ch == '\n') count = 0;
    }
    fclose(file); //close file after reading
    return true;
}

bool addNewCarToFile(char *filename, car carNew)
{
    FILE *file;
    file = fopen(filename,"ab"); //open writing binary file
    if (file == NULL) return false; //if not find file return false
    char ch = '-';

    ch = '-';
    fwrite(carNew.manu, 1,sizeof(carNew.manu),file);
    fwrite(&ch, sizeof(char), 1, file);
    fwrite(carNew.model, 1,sizeof(carNew.model),file);
    fwrite(&ch, sizeof(char), 1, file);
    fwrite(&carNew.price,sizeof(int),1,file);
    fwrite(&ch, sizeof(char), 1, file);
    fwrite(&carNew.emission,sizeof(float),1,file);
    ch = '\n';
    fwrite(&ch, sizeof(char), 1, file);
    fclose(file); //close file after writing

    return true;
}

int main()
{
    char *filename = "file.bin";
    int func = 0;
    int numCars = 10; //number of initial cars
    car *cars = malloc(numCars * sizeof *cars), carNew = {'\0'};
    init(filename,cars); //initializing cars into the file


    //Repeat until func = 3 means quitting the program
    do
    {
        func = 0;
        printf("Three functions:\n1. Print all cars from the file\n2. Add new car to the end of the file\n3. Quit program\n");

        //Make sure valid function is selected
        do
        {
            printf("Choose a function: ");
            scanf("%d", &func);
            if (func>3 || func<1) printf("Function not available! Try again\n");
        } while (func>3 || func<1);

        switch (func)
        {
            //PRINT ALL CARS FROM THE FILE
            case 1:
                allCarsPrint(filename);
                break;

            //ADD NEW CAR TO THE END OF THE FILE
            case 2:
                //ASS USER DATA OF THE CAR TO ADD
                printf("Enter the manufacturer: ");
                scanf("%s", carNew.manu);
                printf("Enter the model: ");
                scanf("%s", carNew.model);
                printf("Enter the price: ");
                scanf("%d",&carNew.price);
                printf("Enter the CO2 emission: ");
                scanf("%f",&carNew.emission);

                //Print message to announce new car is added or not
                if (addNewCarToFile(filename,carNew)) printf("New car is added to the end of file.\n\n");
                else printf("Error. Try again!\n\n");
                break;

            //QUIT PROGRAM
            case 3:
            default:
                printf("Exit program");
                break;
        }
    } while (func!=3);

    free(cars);
    return(0);
}
