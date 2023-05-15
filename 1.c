#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int position = 0;

struct shop
{
    char name[30]; // name
    char year[5]; // year of birth
    char NumGr[10]; // group number
    // grades
    char fiz;
    char math;
    char inform;
    char him;
};

char filename[] = "shop.txt";
char file[] = "shops_2.txt";
int size_m = 0;
void readFile(struct shop* shops) {
    FILE* in = fopen(filename, "r");
    fseek(in, position, SEEK_SET);
    if (in) {
        int i = 0;
        while (!feof(in)) {
            struct shop T;
            fscanf(in, "%s %s %s %c %c %c %c", T.name, T.year, T.NumGr, &T.fiz, &T.math, &T.inform, &T.him);
            shops[i] = T;
            ++i;
            ++size_m;
        }
    }
    fseek(in, 0, SEEK_END); // Seek to the end of the file
    position = ftell(in); // Get the current position, which is the size of the file
    fclose(in);
}

void writeFile(char* name) {
    FILE* out = fopen(name, "a");
    if (out) {
        struct shop T;
        printf("Enter surname, age, group number, and grades (physics, math, informatics, chemistry):\n");
        scanf("%s %s %s %c %c %c %c", T.name, T.year, T.NumGr, &T.fiz, &T.math, &T.inform, &T.him);
        fprintf(out, "%s %s %s %c %c %c %c\n", T.name, T.NumGr, T.year, T.fiz, T.math, T.inform, T.him);
    }
    fclose(out);
}

void clearFiles(char* name) {
    FILE* out = fopen(name, "w");
    if (out)
        fprintf(out, " ");
        fclose(out);
    }
    
void outFile() {
    FILE* in = fopen(filename, "r");
    char line[200];
    if (in)
    {
        while (fgets(line, 200, in))
        {
            printf("%s", line);
        }
    }
    fclose(in);
}

void findStudent(struct shop* shops) {
    
    readFile(shops);
    char one;
    char name_1;
    printf("Students with good grades whose surname starts with: \n");
    printf("Enter the letter: \t");
    scanf(" %c", &one);
    // For average score
    char f[3];
    char m[3];
    char inf[3];
    char h[3];
    int f_2 = 0;
    int m_2 = 0;
    int inf_2 = 0;
    int h_2 = 0;
    double SrZn = 0;
        
    for (int i = 0; i < size_m-1; i++)
    {
    
        name_1 = shops[i].name[0];
        f_2 = (int)shops[i].fiz - 48;
        m_2 = (int)shops[i].fiz - 48;
        inf_2 = (int)shops[i].fiz - 48;
        h_2 = (int)shops[i].fiz - 48;
        
        SrZn = ((f_2 + m_2 + inf_2 + h_2) / 4);
        
    
        if (one == name_1 && SrZn == 5) {
            
            printf("Average score of student %d: %f\n", i+1, SrZn);
            printf("name: %s group: %s age: %s physics: %c math: %c informatics: %c chemistry: %c %d\n", shops[i].name, shops[i].NumGr, shops[i].year, shops[i].fiz, shops[i].math, shops[i].inform, shops[i].him, SrZn);
    
            FILE* out = fopen(file, "a");
            
            if (out) {
                fprintf(out, "name: %s group: %s age: %s physics: %c math: %c informatics: %c chemistry: %c\n", shops[i].name, shops[i].NumGr, shops[i].year, shops[i].fiz, shops[i].math, shops[i].inform, shops[i].him);
            }
            
            fclose(out);
        }
    }
    
}

int main()
{
    struct shop* shops = (struct shop*)malloc(sizeof(struct shop) * 100);
    int key;
    
    do
    {
        printf("1 - Add a new student\n2 - Clear the file\n3 - Output the contents of the file\n4 - Search for a student with good grades\n5 - Exit\n");
        scanf("%d", &key);
        switch (key)
        {
            case 1:
            writeFile(filename);
            break;
            case 2:
            clearFiles(filename);
            clearFiles(file);
            break;
            case 3:
            outFile();
            break;
            case 4:
            findStudent(shops);
            break;
            case 5:
            printf("Goodbye!\n");
            break;
            default:
            printf("Incorrect input\n");
            break;
        }
    } while (key != 5);
    
    free(shops);
    
    return 0;
}
