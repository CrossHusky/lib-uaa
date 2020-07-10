#include <cstring>
#include <ctime>
#include <iostream>
#include <unistd.h>

using namespace std;

// Tiempo
time_t ahora;

// Estructura para el manejo del inventario
struct Art {
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

struct Venta {
    char cliente[32];
    char total[9];
    char* tiempo;
};

struct Compra {
    char proveedor[32];
    char total[11];
    char* tiempo;
};

// Prototipos
void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}
void press();                      // Presentación
void inAlta(FILE*(&), Art(&));     // Dar de alta de artículos
void inBaja(FILE*(&), Art(&));     // Dar de baja artículos
void inVenta(FILE*(&), FILE*(&));  // Venta de artículos
void inVentaH(FILE*(&));           // Historial de ventas
void inCompra(FILE*(&), FILE*(&)); // Compra de artículos
void inCompraH(FILE*(&));          // Historial de compras
void inTodo(FILE*(&), Art(&));     // Mostrar todos los artículos

int main(void)
{
    // Datos a usar
    FILE *fInventario, *fVenta, *fCompra; // Archivo del inventario, venta y compra
    Art libro;                            // Estructura para entrada/salida de datos
    char r = 'x';                         // Respuesta en el menú
    int ctr = 0;                          // Control del menú
    press();
    // Ciclo del menú
    while(r != 's') {
        system("clear");
        fflush(stdin);
        ahora = time(0);
        // Menú en pantalla
        printf("--------------------------------------------------------------------------------");
        printf("\n                Líbreria <Alejandría>  %s", ctime(&ahora));
        printf("--------------------------------------------------------------------------------\n");
        printf("Sistema de gestión de inventario y ventas\n");
        printf("[a] >> Dar de alta un artículo no existente\n");
        printf("[b] >> Dar de baja un artículo existente\n");
        printf("[v] >> Vender artículo a cliente\n");
        printf("[h] >> Mostrar el historial de ventas\n");
        printf("[c] >> Adquirir artículo de proveedor\n");
        printf("[d] >> Mostrar el historial de compras\n");
        printf("[t] >> Muestra todo el inventario\n");
        printf("[s] >> Salir del programa\n");
        printf("Teclee una opción válida:");
        // Evita usar enter la primera vez
        if(ctr == 1) {
            cin.ignore();
        }

        // Control del menú
        ctr = 1;

        r = getchar();

        // Seleccionador
        switch(r) {
        case('a'):
            inAlta(fInventario, libro);
            break;
        case('b'):
            inBaja(fInventario, libro);
            break;
        case('t'):
            inTodo(fInventario, libro);
            break;
        case('v'):
            inVenta(fInventario, fVenta);
            break;
        case('h'):
            inVentaH(fVenta);
            break;
        case('c'):
            inCompra(fInventario, fCompra);
            break;
        case('d'):
            inCompraH(fCompra);
            break;
        }
        // Fin del ciclo
    }
    return 0;
}

// Implementación
void inAlta(FILE*(&fInventario), Art(&libro))
{
    fflush(stdin);
    fInventario = fopen("Inventario.txt", "a");
    system("clear");
    char op = 'x';
    printf("\nRealizando alta...\n");
    // cin.ignore();
    while(op != 'n') {
        fseek(fInventario, 0, SEEK_END);
        cin.ignore();
        printf("Título:");
        fgets(libro.titulo, 32, stdin); // scanf("%s", &libro.titulo);
        cin.ignore();
        printf("Autor:");
        fgets(libro.autor, 32, stdin); // scanf("%s", &libro.autor);
        cin.ignore();
        printf("Género:");
        fgets(libro.genero, 32, stdin); // scanf("%s", &libro.genero);
        cin.ignore();
        printf("Editorial:");
        fgets(libro.editorial, 32, stdin); // scanf("%s", &libro.editorial);
        cin.ignore();
        printf("Páginas:");
        fgets(libro.paginas, 4, stdin); // scanf("%s", &libro.paginas);
        cin.ignore();
        printf("Año de edición:");
        fgets(libro.edicion, 5, stdin); // scanf("%s", &libro.edicion);
        cin.ignore();
        printf("ISBN:");
        fgets(libro.isbn, 14, stdin); // scanf("%s", &libro.isbn);
        cin.ignore();
        printf("Costo:");
        fgets(libro.costo, 9, stdin); // scanf("%.2f", &libro.costo);
        cin.ignore();
        printf("Precio:");
        fgets(libro.precio, 9, stdin); // scanf("%.2f", &libro.precio);
        cin.ignore();
        printf("Existencia(s):");
        fgets(libro.ex, 3, stdin); // scanf("%i", &libro.ex);
        cin.ignore();
        fwrite(&libro, sizeof(Art), 1, fInventario);
        printf("\nAlta exitosa!\tAñadir otra alta? [s/n]:");
        // cin.ignore();
        op = getchar(); // scanf("%c", &op);
    }
    fclose(fInventario);
    system("clear");
}

void inTodo(FILE*(&fInventario), Art(&libro))
{
    fflush(stdin);
    fInventario = fopen("Inventario.txt", "r");
    int i = 0;
    char s = 'x';
    system("clear");
    printf("\nMostrando contenido del inventario\n");
    while(1) {
        fseek(fInventario, i * sizeof(Art), SEEK_SET);
        fread(&libro, sizeof(Art), 1, fInventario);

        if(feof(fInventario))
            break;

        printf("-----------------------------------------------------------------------\n");
        printf("\nTítulo: %s\tAutor: %s\tGénero: %s", &libro.titulo, &libro.autor, &libro.genero);
        printf("\nEditorial: %s\tPáginas: %s\tAño de edición: %s\tISBN: %s", &libro.editorial, &libro.paginas,
            &libro.edicion, &libro.isbn);
        printf("\nCosto: %s\tPrecio: %s\tExistencia(s): %s", &libro.costo, &libro.precio, &libro.ex);
        i++;
    }

    printf("\n-----------------------------------------------------------------------\n");
    printf("<<<Presione [Esc] y después [Enter] para volver al menú>>>");
    // Mantener el inventario en pantalla hasta presionar "Esc"
    while(1) {
        if(s == '\e')
            break;
        s = getchar();
    }

    fclose(fInventario);
    system("clear");
}

void inBaja(FILE*(&fInventario), Art(&libro))
{
    fflush(stdin);
    system("clear");
    FILE* aux;
    aux = fopen("aux.txt", "w");
    fInventario = fopen("Inventario.txt", "r");

    char xbaja[14];
    int mark = 0;
    int i = 0;
    char s = 'x';

    printf("Teclee el código del artículo:");
    cin.ignore();
    fgets(xbaja, 14, stdin);

    while(1) {

        fseek(fInventario, i * sizeof(Art), SEEK_SET);
        fread(&libro, sizeof(Art), 1, fInventario);

        if(feof(fInventario))
            break;

        if(strcmp(xbaja, libro.isbn) != 0) {
            fwrite(&libro, sizeof(Art), 1, aux);
        }

        if(strcmp(xbaja, libro.isbn) == 0) {
            mark = 1;
        }
        i++;
    }
    if(mark == 1) {
        remove("Inventario.txt");
        rename("aux.txt", "Inventario.txt");
        printf("Baja exitosa!\n");
    } else {
        printf("Registro no encontrado!\n");
    }

    fclose(fInventario);
    fclose(aux);
    printf("<<<Presione [Esc] y después [Enter] para volver al menú>>>");
    while(1) {
        if(s == '\e')
            break;
        s = getchar();
    }
    system("clear");
}

void inVenta(FILE*(&fInventario), FILE*(&fVenta))
{

    Venta venta1;
    Art aux;
    int iter = 0;
    int totAux = 0;
    char resp1 = 'x';
    char libAux[14];

    fVenta = fopen("Ventas.txt", "a+");
    fInventario = fopen("Inventario.txt", "r+");

    system("clear");
    fflush(stdin);

    printf("-------------------------");
    printf("\n- Venta de artículo -\n");
    printf("-------------------------");
    printf("\nTeclee código del artículo:");
    cin.ignore();
    fgets(libAux, 14, stdin);

    while(1) {

        fseek(fInventario, iter * sizeof(Art), SEEK_SET);
        fread(&aux, sizeof(Art), 1, fInventario);

        if(feof(fInventario))
            break;

        if(strcmp(libAux, aux.isbn) == 0) {
            int exAux = 0;
            exAux = atoi(aux.ex);
            exAux--;
            sprintf(aux.ex, "%d", exAux);
            totAux += atof(aux.precio);
            gcvt(totAux, 8, venta1.total);
            fseek(fInventario, iter * sizeof(Art), SEEK_SET);
            fwrite(&aux, sizeof(Art), 1, fInventario);
        }

        iter++;
    }

    printf("Nombre del cliente:");
    cin.ignore();
    fgets(venta1.cliente, 32, stdin);

    ahora = time(0);
    venta1.tiempo = ctime(&ahora);

    fseek(fVenta, 0, SEEK_END);
    fwrite(&venta1, sizeof(Venta), 1, fVenta);

    fclose(fVenta);
    fclose(fInventario);

    printf("\n<<<Presione [Esc] y después [Enter] para volver al menú>>>");

    while(1) {
        if(resp1 == '\e')
            break;
        resp1 = getchar();
    }
}

void inVentaH(FILE*(&fVenta))
{
    system("clear");

    fVenta = fopen("Ventas.txt", "r");
    Venta show;

    int i = 0;
    char resp = 'x';
    while(1) {
        fseek(fVenta, i * sizeof(Venta), SEEK_SET);
        fread(&show, sizeof(Venta), 1, fVenta);

        if(feof(fVenta))
            break;
        printf("-------------------------------------------------------------------");
        printf("Fecha:%s Cliente:%s Total:%s", show.tiempo, show.cliente, show.total);
        i++;
    }
    printf("\n<<<Presione [Esc] y después [Enter] para volver al menú>>>");

    while(1) {
        if(resp == '\e')
            break;
        resp = getchar();
    }
    fclose(fVenta);
}

void inCompra(FILE*(&fInventario), FILE*(&fCompra))
{

    Compra compra1;
    Art aux;
    int iter = 0;
    int totAux = 0;
    char resp1 = 'x';
    char libAux[14];

    fCompra = fopen("Compras.txt", "a+");
    fInventario = fopen("Inventario.txt", "r+");

    system("clear");
    fflush(stdin);

    printf("-------------------------");
    printf("\n- Compra de artículo -\n");
    printf("-------------------------");
    printf("\nTeclee código del artículo:");
    cin.ignore();
    fgets(libAux, 14, stdin);

    while(1) {

        fseek(fInventario, iter * sizeof(Art), SEEK_SET);
        fread(&aux, sizeof(Art), 1, fInventario);

        if(feof(fInventario))
            break;

        if(strcmp(libAux, aux.isbn) == 0) {
            int exAux = 0;
            exAux = atoi(aux.ex);
            exAux++;
            sprintf(aux.ex, "%d", exAux);
            totAux += atof(aux.precio);
            gcvt(totAux, 10, compra1.total);
            fseek(fInventario, iter * sizeof(Art), SEEK_SET);
            fwrite(&aux, sizeof(Art), 1, fInventario);
        }

        iter++;
    }

    printf("Nombre del proveedor:");
    cin.ignore();
    fgets(compra1.proveedor, 32, stdin);

    ahora = time(0);
    compra1.tiempo = ctime(&ahora);

    fseek(fCompra, 0, SEEK_END);
    fwrite(&compra1, sizeof(Venta), 1, fCompra);

    fclose(fCompra);
    fclose(fInventario);

    printf("\n<<<Presione [Esc] y después [Enter] para volver al menú>>>");

    while(1) {
        if(resp1 == '\e')
            break;
        resp1 = getchar();
    }
}

void inCompraH(FILE*(&fCompra))
{
    system("clear");

    fCompra = fopen("Compras.txt", "r");
    Compra show;

    int i = 0;
    char resp = 'x';
    while(1) {
        fseek(fCompra, i * sizeof(Venta), SEEK_SET);
        fread(&show, sizeof(Venta), 1, fCompra);

        if(feof(fCompra))
            break;

        printf("-----------------------------------------------------------------------");
        printf("Fecha:%s Proveedor:%s Total:%s", show.tiempo, show.proveedor, show.total);

        i++;
    }
    printf("\n<<<Presione [Esc] y después [Enter] para volver al menú>>>");

    while(1) {
        if(resp == '\e')
            break;
        resp = getchar();
    }
    fclose(fCompra);
}

void press()
{
    char pausa = 'x';
    system("clear");
    gotoxy(18, 9);
    printf("Universidad Autónoma de Auascalientes");
    gotoxy(18, 10);
    printf("Ingeniería en Sistemas Computacionales");
    gotoxy(18, 11);
    printf("Programación I");
    gotoxy(18, 12);
    printf("Carlos Luévano Santillán");
    gotoxy(18, 13);
    printf("Francisco Samael Martínez Contreras");
    gotoxy(12, 15);
    printf("<<<Presione [Esc] y después [Enter] para continuar>>>");
    while(1) {
        if(pausa == '\e')
            break;
        pausa = getchar();
    }
    cin.ignore();
    system("clear");
}