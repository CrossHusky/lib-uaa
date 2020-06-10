// Proyecto final de Programación 1 2° R
// Carlos Luevano
// Samael Martínez
#include <iostream>

using namespace std;

// Estructura para el manejo del archivo
struct persona {
    char pNom[100];
    char pDir[100];
    char pTel[100];
};

int main(void)
{

    // Datos a usar
    FILE* fp1;
    persona p;

    // Apertura del archivo
    fp1 = fopen("File.txt", "r+");
    if(fp1 == NULL) {
        fp1 = fopen("File.txt", "w+");
        if(fp1 == NULL) {
            printf("Error al abrir archivo. \n");
            return -1;
        }
    }

    // Escritura en el archivo
    fseek(fp1, 0, SEEK_END);
    printf("Nombre:");
    scanf("%[^\n]", p.pNom);
    cin.ignore();
    printf("Dirección:");
    scanf("%[^\n]", p.pDir);
    cin.ignore();
    printf("Teléfono:");
    scanf("%[^\n]", p.pTel);
    cin.ignore();
    fwrite(&p, sizeof(p), 1, fp1);
    
    //Lectura del archivo
    fread(&p, sizeof(p), 1, fp1);
    printf("Nombre:");
    printf("%s \n", p.pNom);
    printf("Dirección:");
    printf("%s \n", p.pDir);
    printf("Teléfono:");
    printf("%s \n", p.pTel);
    
    //Cerrar archivo
    fclose(fp1);
    
    return 0;
}