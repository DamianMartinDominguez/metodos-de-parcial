// ////////////////////////////////////////////////    ejemplo de cola  /////////////////////////////////////////////////////////////////////////////////////

/* existe un archivo binario "paciente.dat" secuencial con la siguiente estructura: 
int id;
char n[30];
unsigned int tipo;
que prentan los datos de un paciente que se efectuara un analisis donde la variable tipo
es un numero binario que en su bit numero 3 indica con 1 significa analisis de orina,
y el bit 4 en 1 significa analisis de sangre.
crear una funcion que arme una cola con aquellos registros del archivo que corresponde analisis de sangre.
mostrar los datos de la cola en el main y luego eliminarlos, 
sabiendo que no hay variables globales 
*/

//codigo

struct datos{
            int id;
            char n[30];
            unsigned int tipo;
            };

struct cola{
            struct datos d;
            struct cola*l;
            };

void generaArchivo(void);
void setCola(struct cola **p,struct cola **u);

int main()
{
 struct cola *p=NULL, *u= NULL, *aux;
 generaArchivo();

 setCola(&p,&u);
 while(p)
 {
    printf("%4d %-20s 0x%x\n",p->d.id, p->d.n, p->d.tipo);
    aux=p;
    p=p->l;
    free(aux);
 }
 system("pause");
 return 0;
}

void setCola(struct cola **p,struct cola **u)
{
  struct datos bf;
  struct cola *aux;
  FILE *fp;
  if((fp=fopen("paciente.dat","rb"))== NULL)
    {
    printf("\n error en el archivo\n");

    return 1;
    }
  fread(&bf,sizeof(struct datos),1,fp);
  while(!feof(fp))
  {
  
  if(bf.tipo & 0x10)//si quiero que este el bit 4 que es la posicion 5 en 1
  //if(!(bf.tipo & 0x10)) si quiero que este el bit 4 que es la posicion 5 en 0 
  {
  aux = (struct cola*)malloc(sizeof(struct cola));
  if(aux)
  {
    aux->d=bf;
    if(*p==NULL)
      *p= *u = aux;
    else
    {
      (*u)->l=aux;
      *u=aux;
    }
    (*u)->l= NULL;
}
}
fread(&bf,sizeof(struct datos),1,fp);
}
fclose(fp);
}

void generaArchivo(void)
{
struct datos bf[]={ 1,"juan primero",0x11,
                    2,"juan segundo",0x12,
                    3,"juan tercero",0x13,
                    4,"juan cuarto",0x14,
                    5,"juan quinto",0x15,
                    6,"juan sexto",0x16,
                    7,"juan septimo",0x17,
                    8,"juan octavo",0x18,};
FILE *fp=fopen("paciente.dat","wb");

fwrite(bf,sizeof(struct datos),8,fp);
printf("\n\n");
fclose(fp);
}


//  /////////////////////////////////////////////////////////////ejemplo de pila///////////////////////////////////////////////////////////////


/* parcial de romero 
Legajo: 110009		Apellido y nombre: Romero, Luis 	Email: lromero4598@gmail.com
Teoría:
1- Si bien ambas son estructuras referenciadas, la diferencia es que la cola 
es un tipo de estructura en el que el primer dato que entra es también el primero 
en salir. En cambio una lista es una estructura con un cierto criterio de orden,
en el que puedo atender el dato que precise.
2-CREATE: crea nuevas tablas.
ALTER: modifica las tablas agregando o cambiando la definicion de los campos
DROP: elimina tablas.
TRUNCATE: elimina todos los registros de la tabla.
COMMENT: agrega comentarios al diccionario de datos.
RENAME: renombra objetos
Práctica:
*/

/*
1) Existe un archivo binario, “cliente.dat”, secuencial con la siguiente estructura:
int id, char n[30] , unsigned int tipo, int b(baja lógica b=0), que son los datos de un cliente,
donde cada bit del campo tipo representa alguna situación del cliente: el bit 5 en 1 significa que no tiene crédito
y el bit 4 en 1 que es deudor, etc.
 Crear una función que arme una pila con los registros que no sean deudores verificando que estén activos.
Realizar el main() con la llamada a dicha función y crear un archivo con los datos de la pila. No utilizar variables Globales
Enviar a Gustavo Viard: gviard_electronica@yahoo.com.ar
*/



#include <stdio.h>
#include <stdlib.h>

struct datos{

        int id;
        char n[30];
        unsigned int tipo;
        int b;

    };

    struct pila{
        struct datos d;
        struct pila *l;
    };

    struct pila *p=NULL, *aux, *r;

void crearPila (struct pila **l);

int main()
{
    FILE *pf;

    crearPila(&p);

    if((pf=fopen("activos.dat","wb"))==NULL)
        {
            printf("no se puede abrir el archivo");
            return ;
        }

   while(p)
   {
       aux=p;
       fwrite(&p,sizeof(struct datos),1,pf);
       p=p->l;
       free(aux);
   }

   fclose(pf);
}

void crearPila (struct pila **l)
{
    struct pila *aux;
    struct datos bf;
    FILE *fp;

    if((fp=fopen("clientes.dat","rb"))==NULL)
        {
            printf("no se puede abrir el archivo");
            return ;
        }

    fread(&bf,sizeof(struct datos),1,fp);
    while(!feof(fp))
    {
        if(bf.b!=0 && !(bf.tipo & 0x10))
        {
            aux=(struct pila *) malloc (sizeof(struct pila));
            aux->d=bf;
            aux->l=p;
            p=aux;
        }
    }
    fclose(fp);
}


//------------Fin del Parcial------------

//Romero, Luis.


////////////////////////////////////////////////////  ejemplo de lista /////////////////////////////////////////////////////////////////////





#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    char nombre[30];
    unsigned short edad;
    long legajo;

}datos_t;

struct listaDoble_t
{
    datos_t data;
    struct listaDoble_t *siguiente, *anterior;
};

int main()
{
    datos_t nuevo;
    struct listaDoble_t *lista = NULL, *aux= NULL,*local= NULL;
    short opc= 0;
    printf("\nejemplo lista doble con memoria dinamica\n");
    do
    {
        aux = (struct listaDoble_t*)malloc(sizeof(struct listaDoble_t));
        if(aux==NULL)
        {
            printf("\n no hay memoria disponible\n");
            return 0;

        }
        printf("\n ingrese el registro de la lista\n");
        printf("\n ingrese el nombre\n");
        fflush(stdin);
        scanf("%s",&aux->data.nombre);
        printf("\n ingrese la edad\n");
        fflush(stdin);
        scanf("%d",&aux->data.edad);
        printf("\n ingrese el legajo\n");
        fflush(stdin);
        scanf("%ld",&aux->data.legajo);
        if(lista == NULL)
        {
          lista = aux;
          lista->siguiente = NULL;
          lista->anterior = NULL;
         }
         else
         {
          local = lista;
          while((local->data.edad <= aux->data.edad) && (local->siguiente != NULL))
          {
            local = local->siguiente;
          }
          //reemplazo a local
          if(local->data.edad > aux->data.edad)//registro intermedio
          {
            if((aux->anterior) != NULL)

            aux->anterior->siguiente = aux;
            else lista = aux;
            aux->anterior = local->anterior;
            local->anterior = aux;
            aux->siguiente = local;
           }
           else{
           //registro al final
           local->siguiente = aux;
           aux->anterior = local;
           aux->siguiente = NULL;


           }}
        printf("\ndesea seguir agregando datos?\n 1_S  2_N");
        fflush(stdin);
        scanf("%d",&opc);



    }while(opc == 1);
    printf("\n carga de pila completada" );
    do
    {
        printf("\n como desea imprimirlo? 1- mayor a menor   2- menor a mayor  3- liberar salir  ");
         fflush(stdin);
        scanf("%d",&opc);
        if(opc == 2)
        {
          local = lista;
          do{
           printf("\n----------------------------------------------------------------");
           printf("\n el registro contiene :\n Nombre:%s  \nEdad: %d \nLegajo: %ld", local->data.nombre,local->data.edad,local->data.legajo);
           local= local->siguiente;
        }while(local->siguiente != NULL);
         printf("\n----------------------------------------------------------------");
         printf("\n el registro contiene :\n Nombre:%s  \nEdad: %d \nLegajo: %ld", local->data.nombre,local->data.edad,local->data.legajo);
         printf("\n----------------------------------------------------------------");
        }
        if(opc == 1)
        {
          local = lista;
          while(local->siguiente != NULL)
            local = local->siguiente;
          do{
              printf("\n----------------------------------------------------------------");
              printf("\n el registro contiene :\n Nombre:%s  \nEdad: %d \nLegajo: %ld", local->data.nombre,local->data.edad,local->data.legajo);
              local= local->anterior;
             }while(local->anterior != NULL);
             printf("\n----------------------------------------------------------------");
             printf("\n el registro contiene :\n Nombre:%s  \nEdad: %d \nLegajo: %ld", local->data.nombre,local->data.edad,local->data.legajo);
             printf("\n----------------------------------------------------------------");
             }
             }while(opc != 3);
             printf("\n liberando...");
             do {
              aux = lista;
              lista = lista->siguiente;
              free(aux);
              }while(lista->siguiente != NULL);
              free(lista);
              printf("\nfin");

    return 0;
}

