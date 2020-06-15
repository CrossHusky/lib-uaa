// Proyecto final de Programación 1 2° R
// Carlos Luevano
// Samael Martínez
#include <iostream>

using namespace std;

// Estructura para el manejo del archivo
struct alumno
{
    char pNom[100];
    char pDir[100];
    char pTel[100];
    char pEdad[3];
};

int main(void)
{

    // Datos a usar
    FILE *fBin, *fText;
    alumno p;

    // Apertura del archivo
    fBin = fopen("File.bin", "ab+");
    fText = fopen("File.txt", "w+");

    if (fBin == NULL)
    {
        printf("No se puede leer el archivo...");
        return -1;
    }

    if (fText == NULL)
    {
        printf("No se puede leer el archivo...");
        return -1;
    }

    // Escritura en el archivo
    for (int i = 0; i < 5; i++)
    {
        fseek(fBin, 0, SEEK_END);
        printf("Nombre:");
        scanf("%[^\n]", p.pNom);
        cin.ignore();
        printf("Dirección:");
        scanf("%[^\n]", p.pDir);
        cin.ignore();
        printf("Teléfono:");
        scanf("%[^\n]", p.pTel);
        cin.ignore();
        printf("Edad:");
        scanf("%[^\n]", p.pEdad);
        cin.ignore();
        fwrite(&p, sizeof(struct alumno), 1, fBin);
    }

    // Lectura del archivo
    for (int i = 0; i < 5; i++)
    {
        fseek(fBin, i * sizeof(struct alumno), SEEK_SET);
        fread(&p, sizeof(struct alumno), 1, fBin);
        printf("\nDatos del alumno %d:\n", i + 1);
        printf("Nombre:");
        printf("%s \n", p.pNom);
        printf("Dirección:");
        printf("%s \n", p.pDir);
        printf("Teléfono:");
        printf("%s \n", p.pTel);
        printf("Edad:");
        printf("%s \n", p.pEdad);
        // Copia al archivo de Texto
        fseek(fText, 0, SEEK_END);
        fwrite(&p, sizeof(struct alumno), 1, fText);
    }

    // Cerrar archivo
    fclose(fBin);
    fclose(fText);

    return 0;
}