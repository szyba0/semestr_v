#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    FILE *oldFile;
    FILE *newFile;

    // 1. Sprawdź ilość argumentów
    if (argc < 3)
    {
        perror("Nie podano dwóch argumentów!");
        exit(1);
    }

    // 2. Sprawdź dostęp do "tmp.txt"
    oldFile = fopen("tmp.txt", "r");
    if (oldFile == NULL)
    {
        perror("Nie udało się odczytać pliku tmp.txt!");
        exit(2);
    }

    // 3. Sprawdź dostęp do nowego pliku
    newFile = fopen(argv[1], "w+");
    if (newFile == NULL)
    {
        perror("Nie udało się otworzyć nowego pliku!");
        exit(3);
    }

    // 4.
    char *tmp = NULL;
    size_t len = 120;
    fprintf(newFile, "Zadanie 1:\n");
    getline(&tmp, &len, oldFile);
    getline(&tmp, &len, oldFile);
    getline(&tmp, &len, oldFile);
    fprintf(newFile, tmp);
    getline(&tmp, &len, oldFile);
    getline(&tmp, &len, oldFile);
    fprintf(newFile, tmp);
    getline(&tmp, &len, oldFile);
    getline(&tmp, &len, oldFile);
    fprintf(newFile, tmp);
    fseek(oldFile, 0, SEEK_SET);

    // 5.
    fprintf(newFile, "Zadanie 2:\n");
    getline(&tmp, &len, oldFile);
    getline(&tmp, &len, oldFile);
    for(int i = 0; i < strlen(tmp); i++){
        tmp[i] = toupper(tmp[i]);
    }
    fprintf(newFile, tmp);
    getline(&tmp, &len, oldFile);
    getline(&tmp, &len, oldFile);
    for(int i = 0; i < strlen(tmp); i++){
        tmp[i] = toupper(tmp[i]);
    }
    fprintf(newFile, tmp);
    getline(&tmp, &len, oldFile);
    getline(&tmp, &len, oldFile);
    for(int i = 0; i < strlen(tmp); i++){
        tmp[i] = toupper(tmp[i]);
    }
    fprintf(newFile, tmp);
    fseek(oldFile, 0, SEEK_SET);

    // 6.
    fprintf(newFile, "Zadanie: 3\n");
    int k;
    do {
        char numbers[100] = "";
        k = getline(&tmp, &len, oldFile);
        int j = 0;
        for(int i = 0; i < strlen(tmp); i++){
            if(isdigit(tmp[i])){
                numbers[j] = tmp[i];
                j++;
            }
        }
        fprintf(newFile, "%*s\n", j, numbers);
    }while(k >= 0);
    fseek(oldFile, 0, SEEK_SET);

    // 7.
    fprintf(newFile, "Zadanie 4:\n");
    int line = 0;
    do {
        line++;
        k = getline(&tmp, &len, oldFile);
        if(strstr(tmp, argv[2]) != NULL){
            fprintf(newFile, "Linia nr: %i ", line);
        }
        
    } while (k >= 0);

    // 9.
    chmod(argv[1], 0600);

    // 10.Zamknij pliki
    fclose(oldFile);
    fclose(newFile);

    // 8.
    struct stat sb;
    if(stat(argv[1], &sb) != -1){
        printf("Wielkość pliku \"%s\" wynosi %d", argv[1], sb.st_size);
    }
}