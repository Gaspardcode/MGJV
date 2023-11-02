#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>



#define INPUT 784
#define HIDDEN 15

double randomchoice() 
{
    int randomInt = rand();
    double randomDouble = ((double)randomInt / RAND_MAX) - 1;
    return randomDouble;
}



void insert_file(size_t a, size_t b, char* file) //insert des valeurs aleatoires dans le fichier file
{
    int fd = open(file, O_WRONLY);
    if (fd == -1)
        err(1,"open()1");
    size_t i = 0;
    size_t j = 0;
    char str[80];
    long nbr = 0;
    while(i<a)
    {
        j =0;
        while(j<b)
        {
            double random = randomchoice();
            sprintf(str, "%f\n", random);
            write(fd, str, strlen(str));
            j++;
            nbr++;
        }
        i++;
    }
    close(fd);
}



void insert_list(size_t a, size_t b, char* file, double** tab) // recupere les donnees de file et les mets dans tab
{
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        err(1,"open()");

    int r,w;
    char buffer[64];
    char nbr[80];
    size_t k =0;
    size_t z =0;
    size_t i = 0;
    while((r = read(fd, buffer, 64)) != 0)
    {
        size_t j = 0;
        while(j < r)
        {
            char* eptr;
            double result;
            if(buffer[j] == '\n')
            {
                nbr[i] = 0;
                result = strtod(nbr, &eptr);
                i =0;
                j++;
                tab[k][z] = result;
                z++;
                if(z == b)
                {
                    z = 0;
                    k++;
                }
            }
            else
            {
                nbr[i] = buffer[j];
                i++;
                j++;
            }
        }
    }
    close(fd);

}



void replace(size_t a, size_t b, char* file, double** tab) // detruit le fichier file et le remplace par un nouveau avec les valeurs de tab
{
    if(remove(file) ==-1)
        err(1,"remove()");
    char str[80];
    int fd = open(file,O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        err(1, "creat()");
    for( size_t i =0; i<a;i++)
    {
        for(size_t j =0; j <b;j++)
        {

            sprintf(str, "%f\n", tab[i][j]);
            if(write(fd, str, strlen(str)) == -1)
                err(1, "write()");

        }
    }
    close(fd);
}


int main()
{
    //test avec une matrice 10x10
    double **h_weight;
    h_weight = malloc(10 * sizeof(double*));
    for(size_t i =0;i <10;i++)
    {
        *(h_weight+i) = calloc(10, sizeof(double));
    }
    srand(time(NULL));
    insert_file(10,10,"hweight.txt");
    insert_list(10,10,"hweight.txt",h_weight);
    replace(10,10,"hweight.txt",h_weight);
    return 0;
}
