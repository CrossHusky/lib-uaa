// Proyecto final de Programación 1 2° R
// Carlos Luevano
// Samael Martínez
#include <iostream>

using namespace std;

// Estructura para el manejo del archivo
struct Art
{
    char titulo[32];
    char autor[32];
    char genero[32];
    char editorial[32];
    char paginas[4];
    char edicion[5];
    char isbn[14];
    char costo[9];
    char precio[9];
    char ex[3];
};

// Prototipo
void inAlta(FILE *(&), Art(&)); // Dar de alta de artículos
void inBaja(FILE *(&), Art(&)); // Dar de baja artículos
/*void inVenta(FILE*(&), Art(&));  // Venta de artículos
void inCompra(FILE*(&), Art(&)); // Compra de artículos*/
void inTodo(FILE *(&), Art(&)); // Mostrar todos los artículos

int main(void)
{

    // Datos a usar
    FILE *fInventario; // Archivo del inbentario
    Art libro;         // Estructura para entrada/salida de datos
    char r = 'x';      // Respuesta en el menú
    int ctr = 0;       // Control del menú

    // Apertura del inventario
    // fInventario = fopen("Inventario.bin", "ab+");

    // Ciclo del menú
    while (r != 's')
    {

        // Menú en pantalla
        printf("\nLíbreria <Alejandría>\n");
        printf("Sistema de gestión de inventario y ventas\n");
        printf("[a]lta  >> Dar de alta un artículo no existente\n");
        printf("[b]aja  >> Dar de baja un artículo existente\n");
        /*printf("[venta] Vender artículo a cliente");
        printf("[compra] Adquirir artículo");*/
        printf("[t]odo  >> Muestra todo el inventario\n");
        printf("[s]alir >> Salir del programa\n");
        printf("Teclee una opción válida:");

        // Evita usar enter la primera vez
        if (ctr == 1)
        {
            cin.ignore();
        }

        // Respuesta
        r = getchar(); // scanf("%c", &r);

        // Control del menú
        ctr = 1;

        // Seleccionador
        switch (r)
        {
        case ('a'):
            inAlta(fInventario, libro);
            break;
        case ('b'):
            inBaja(fInventario, libro);
            break;
        case ('t'):
            inTodo(fInventario, libro);
            break;
        }
        // Fin del ciclo
    }
    return 0;
}

// Implementación
void inAlta(FILE *(&fInventario), Art(&libro))
{
    fInventario = fopen("Inventario.bin", "ab");
    system("clear");
    char op = 'x';
    printf("\nRealizando alta...\n");
    cin.ignore();
    while (op != 'n')
    {
        fseek(fInventario, 0, SEEK_END);
        printf("Título:");
        fgets(libro.titulo, 32, stdin); // scanf("%s", &libro.titulo);
        cin.ignore();
        printf("\nAutor:");
        fgets(libro.autor, 32, stdin); // scanf("%s", &libro.autor);
        cin.ignore();
        printf("\nGénero:");
        fgets(libro.genero, 32, stdin); // scanf("%s", &libro.genero);
        cin.ignore();
        printf("\nEditorial:");
        fgets(libro.editorial, 32, stdin); // scanf("%s", &libro.editorial);
        cin.ignore();
        printf("\nPáginas:");
        fgets(libro.paginas, 4, stdin); // scanf("%s", &libro.paginas);
        cin.ignore();
        printf("\nAño de edición:");
        fgets(libro.edicion, 5, stdin); // scanf("%s", &libro.edicion);
        cin.ignore();
        printf("\nISBN:");
        fgets(libro.isbn, 14, stdin); // scanf("%s", &libro.isbn);
        cin.ignore();
        printf("\nCosto:");
        fgets(libro.costo, 14, stdin); // scanf("%.2f", &libro.costo);
        cin.ignore();
        printf("\nPrecio:");
        fgets(libro.precio, 14, stdin); // scanf("%.2f", &libro.precio);
        cin.ignore();
        printf("\nExistencia(s):");
        fgets(libro.ex, 14, stdin); // scanf("%i", &libro.ex);
        cin.ignore();
        fwrite(&libro, sizeof(struct Art), 1, fInventario);
        printf("\nAlta exitosa!\tAñadir otra alta? [s/n]");
        // cin.ignore();
        op = getchar(); // scanf("%c", &op);
    }
    fclose(fInventario);
    system("clear");
}

void inTodo(FILE *(&fInventario), Art(&libro))
{
    fInventario = fopen("Inventario.bin", "rb");
    int i = 0;
    char s = 'x';
    system("clear");
    printf("\nMostrando contenido del inventario\n");
    while (1)
    {
        fseek(fInventario, i * sizeof(struct Art), SEEK_SET);
        fread(&libro, sizeof(struct Art), 1, fInventario);

        if (feof(fInventario))
            break;

        printf("\nTítulo: %s\tAutor: %s\tGénero: %s", &libro.titulo, &libro.autor, &libro.genero);
        printf("\nEditorial: %s\tPáginas: %s\tAño de edición: %s\tISBN: %s", &libro.editorial, &libro.paginas,
               &libro.edicion, &libro.isbn);
        printf("\nCosto: %s\tPrecio: %s\tExistencia(s): %s", &libro.costo, &libro.precio, &libro.ex);
        i++;
    }

    printf("<<<Presione [Esc] y después [Enter] para volver al menú>>>");
    // Mantener el inventario en pantalla hasta presionar "Esc"
    while (1)
    {
        if (s == '\e')
            break;
        s = getchar();
    }

    fclose(fInventario);
    system("clear");
}

void inBaja(FILE *(&fInventario), Art(&libro))
{
    system("clear");
    printf("Realizando baja...");
    /*for(int i = 0; i < 5; i++) {
        fseek(fInventario, 0, SEEK_END);
        printf("Nombre:");
        scanf("%[^\n]", libro.pNom);
        cin.ignore();
        printf("Dirección:");
        scanf("%[^\n]", libro.pDir);
        cin.ignore();
        printf("Teléfono:");
        scanf("%[^\n]", libro.pTel);
        cin.ignore();
        printf("Edad:");
        scanf("%[^\n]", libro.pEdad);
        cin.ignore();
        fwrite(&libro, sizeof(struct Art), 1, fInventario);
    }*/
    printf("Baja exitosa!");
    system("clear");
}
#include <iostream>

using namespace std;

// Estructura para el manejo del archivo
struct Art
{
    char titulo[32];
    char autor[32];
    char genero[32];
    char editorial[32];
    char paginas[4];
    char edicion[5];
    char isbn[14];
    char costo[9];
    char precio[9];
    char ex[3];
};

// Prototipo
void inAlta(FILE *(&), Art(&)); // Dar de alta de artículos
void inBaja(FILE *(&), Art(&)); // Dar de baja artículos
/*void inVenta(FILE*(&), Art(&));  // Venta de artículos
void inCompra(FILE*(&), Art(&)); // Compra de artículos*/
void inTodo(FILE *(&), Art(&)); // Mostrar todos los artículos

int main(void)
{

    // Datos a usar
    FILE *fInventario; // Archivo del inbentario
    Art libro;         // Estructura para entrada/salida de datos
    char r = 'x';      // Respuesta en el menú
    int ctr = 0;       // Control del menú

    // Apertura del inventario
    // fInventario = fopen("Inventario.bin", "ab+");

    // Ciclo del menú
    while (r != 's')
    {

        // Menú en pantalla
        printf("\nLíbreria <Alejandría>\n");
        printf("Sistema de gestión de inventario y ventas\n");
        printf("[a]lta  >> Dar de alta un artículo no existente\n");
        printf("[b]aja  >> Dar de baja un artículo existente\n");
        /*printf("[venta] Vender artículo a cliente");
        printf("[compra] Adquirir artículo");*/
        printf("[t]odo  >> Muestra todo el inventario\n");
        printf("[s]alir >> Salir del programa\n");
        printf("Teclee una opción válida:");

        // Evita usar enter la primera vez
        if (ctr == 1)
        {
            cin.ignore();
        }

        // Respuesta
        r = getchar(); // scanf("%c", &r);

        // Control del menú
        ctr = 1;

        // Seleccionador
        switch (r)
        {
        case ('a'):
            inAlta(fInventario, libro);
            break;
        case ('b'):
            inBaja(fInventario, libro);
            break;
        case ('t'):
            inTodo(fInventario, libro);
            break;
        }
        // Fin del ciclo
    }
    return 0;
}

// Implementación
void inAlta(FILE *(&fInventario), Art(&libro))
{
    fInventario = fopen("Inventario.bin", "ab");
    system("clear");
    char op = 'x';
    printf("\nRealizando alta...\n");
    cin.ignore();
    while (op != 'n')
    {
        fseek(fInventario, 0, SEEK_END);
        printf("Título:");
        fgets(libro.titulo, 32, stdin); // scanf("%s", &libro.titulo);
        cin.ignore();
        printf("\nAutor:");
        fgets(libro.autor, 32, stdin); // scanf("%s", &libro.autor);
        cin.ignore();
        printf("\nGénero:");
        fgets(libro.genero, 32, stdin); // scanf("%s", &libro.genero);
        cin.ignore();
        printf("\nEditorial:");
        fgets(libro.editorial, 32, stdin); // scanf("%s", &libro.editorial);
        cin.ignore();
        printf("\nPáginas:");
        fgets(libro.paginas, 4, stdin); // scanf("%s", &libro.paginas);
        cin.ignore();
        printf("\nAño de edición:");
        fgets(libro.edicion, 5, stdin); // scanf("%s", &libro.edicion);
        cin.ignore();
        printf("\nISBN:");
        fgets(libro.isbn, 14, stdin); // scanf("%s", &libro.isbn);
        cin.ignore();
        printf("\nCosto:");
        fgets(libro.costo, 14, stdin); // scanf("%.2f", &libro.costo);
        cin.ignore();
        printf("\nPrecio:");
        fgets(libro.precio, 14, stdin); // scanf("%.2f", &libro.precio);
        cin.ignore();
        printf("\nExistencia(s):");
        fgets(libro.ex, 14, stdin); // scanf("%i", &libro.ex);
        cin.ignore();
        fwrite(&libro, sizeof(struct Art), 1, fInventario);
        printf("\nAlta exitosa!\tAñadir otra alta? [s/n]");
        // cin.ignore();
        op = getchar(); // scanf("%c", &op);
    }
    fclose(fInventario);
    system("clear");
}

void inTodo(FILE *(&fInventario), Art(&libro))
{
    fInventario = fopen("Inventario.bin", "rb");
    int i = 0;
    char s = 'x';
    system("clear");
    printf("\nMostrando contenido del inventario\n");
    while (1)
    {
        fseek(fInventario, i * sizeof(struct Art), SEEK_SET);
        fread(&libro, sizeof(struct Art), 1, fInventario);

        if (feof(fInventario))
            break;

        printf("\nTítulo: %s\tAutor: %s\tGénero: %s", &libro.titulo, &libro.autor, &libro.genero);
        printf("\nEditorial: %s\tPáginas: %s\tAño de edición: %s\tISBN: %s", &libro.editorial, &libro.paginas,
               &libro.edicion, &libro.isbn);
        printf("\nCosto: %s\tPrecio: %s\tExistencia(s): %s", &libro.costo, &libro.precio, &libro.ex);
        i++;
    }

    printf("<<<Presione [Esc] y después [Enter] para volver al menú>>>");
    // Mantener el inventario en pantalla hasta presionar "Esc"
    while (1)
    {
        if (s == '\e')
            break;
        s = getchar();
    }

    fclose(fInventario);
    system("clear");
}

void inBaja(FILE *(&fInventario), Art(&libro))
{
    system("clear");
    printf("Realizando baja...");
    /*for(int i = 0; i < 5; i++) {
        fseek(fInventario, 0, SEEK_END);
        printf("Nombre:");
        scanf("%[^\n]", libro.pNom);
        cin.ignore();
        printf("Dirección:");
        scanf("%[^\n]", libro.pDir);
        cin.ignore();
        printf("Teléfono:");
        scanf("%[^\n]", libro.pTel);
        cin.ignore();
        printf("Edad:");
        scanf("%[^\n]", libro.pEdad);
        cin.ignore();
        fwrite(&libro, sizeof(struct Art), 1, fInventario);
    }*/
    printf("Baja exitosa!");
    system("clear");
}