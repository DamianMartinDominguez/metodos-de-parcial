// ////////////////////////////////////////////////    ejemplo de pila   /////////////////////////////////////////////////////////////////////////////////////

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


//  /////////////////////////////////////////////////////////////ejemplo de cola///////////////////////////////////////////////////////////////


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

