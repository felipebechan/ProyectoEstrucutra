#include "hashmap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


#define MAP_SIZE_X 20
#define MAP_SIZE_Y 20

// Estructura para el mapa
typedef struct {
  char data[MAP_SIZE_X][MAP_SIZE_Y];
} Mapa;

typedef struct {
  char *nombre;      // nombre del jugador
  int prota;         // 1 si es el prota, 0 si es un enemigo
  long pH;           // puntos de vida
  long psMax;        // puntos de vida maximos
  int comp;          // bonificador de competencia
  int fuerza;        // fuerza del jugador
  int bonifFuerza;   // bonificacion de fuerza del jugador
  int destreza;      // destreza del jugador
  int bonifDestreza; // bonificacion de destreza del jugador
  long exp;          // experiencia
  HashMap *items;    // hashmap de objetos
  HashMap *equipo;   // hashmap de equipo
  int turno;         // turno en el combate
  int armorClass;    // clase de armadura, numero a superar para que le peguen
  int cubierto;      // 1 si esta cubierto, 0 si no
  int desventaja;    // 1 si tiene desventaja, 0 si no
  int desarmadoPrin; // 1 si esta desarmado, 0 si no
  int desarmadoSec;  // 1 si esta desarmado, 0 si no
} Jugador;

typedef struct {
  char *nombre; // nombre del objeto
  int atk;      // ataque del objeto
  int def;      // defensa del objeto
  int curacion; // curacion del objeto
  int cantidad; // cantidad de objetos
} Objeto;

void clear_console() {
  system("clear");
  system("cls"); // Utilizar "cls" en Windows
}

bool checkFileForEstado(const char* filename,char* estado) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return false;
    }

    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        if (strcmp(word, estado) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

void st_combate() {
  FILE *file = fopen("estado.txt", "w");
  if (file == NULL) {
    printf("Error al abrir el archivo estado.txt.");
    exit(1);
  }

  fprintf(file, "combate");
  fclose(file);
}
void st_hoguera() {
  FILE *file = fopen("estado.txt", "w");
  if (file == NULL) {
    printf("Error al abrir el archivo estado.txt.");
    exit(1);
  }

  fprintf(file, "bonfire");
  fclose(file);
}
void st_mapa() {
  FILE *file = fopen("estado.txt", "w");
  if (file == NULL) {
    printf("Error al abrir el archivo estado.txt.");
    exit(1);
  }

  fprintf(file, "mapa");
  fclose(file);
}

void load_map_from_file(char *file_path, Mapa *mapa) {
  FILE *file = fopen(file_path, "r");
  if (file == NULL) {
    printf("Error al abrir el archivo.");
    exit(1);
  }

  int i, j;
  for (i = 0; i < MAP_SIZE_X; i++) {
    for (j = 0; j < MAP_SIZE_Y; j++) {
      fscanf(file, " %c,", &(mapa->data[i][j]));  // Leer el carácter y la coma
    }
  }

  fclose(file);
}

void display_map(Mapa *mapa, int player_x, int player_y) {
  clear_console();

  int i, j;
  for (i = 0; i < MAP_SIZE_X; i++) {
    for (j = 0; j < MAP_SIZE_Y; j++) {
      if (i == player_y && j == player_x) {
        printf("@");          // Carácter del jugador
        mapa->data[i][j] = '@'; // Guardar la posición del jugador en el mapa
      } else {
        printf("%c", mapa->data[i][j]);
      }
    }
    printf("\n");
  }
}

void save_map_to_file(char *file_path, Mapa *mapa) {
  FILE *file = fopen(file_path, "w");
  if (file == NULL) {
    printf("Error al abrir el archivo.");
    exit(1);
  }

  int i, j;
  for (i = 0; i < MAP_SIZE_X; i++) {
    for (j = 0; j < MAP_SIZE_Y; j++) {
      fprintf(file, "%c,", mapa->data[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);
}

void process_actions(char *file_path, Mapa *mapa, int *player_x, int *player_y) {
  FILE *file = fopen(file_path, "r");
  if (file == NULL) {
    printf("Error al abrir el archivo.");
    exit(1);
  }

  char action[5];
  fgets(action, 5, file);

  if (strlen(action) > 0) {
    printf("Esperando respuesta de archivo %s\n", file_path);
    printf("Acción hecha: %c\n", action[0]);

    switch (action[0]) {
      case 'W':
      case 'w':
        if (*player_y > 0 && mapa->data[*player_y - 1][*player_x] != '#') {
                        if (mapa->data[*player_y - 1][*player_x] == 'd') {
      // Cambiar al siguiente mapa
      load_map_from_file("mapa2.csv", mapa);
      
      break;
    }
     if (mapa->data[*player_y - 1][*player_x] == 'e') {
      mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_y)--;
      // combate
      st_combate();
     
      

      break;
    }
    if (mapa->data[*player_y - 1][*player_x] == 'b') {
      mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_y)--;
      // hoguera
      st_hoguera();
     
      

      break;
    }
          mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_y)--;
        }
        break;
      case 'A':
      case 'a':
        if (*player_x > 0 && mapa->data[*player_y][*player_x - 1] != '#') {
               if (mapa->data[*player_y][*player_x - 1] == 'd') {
      // Cambiar al siguiente mapa
      load_map_from_file("mapa2.csv", mapa);
 
      break;
    }
     if (mapa->data[*player_y ][*player_x - 1] == 'e') {
       mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_x)--;
      // combate
      st_combate();
     
    
      break;
    }
     if (mapa->data[*player_y ][*player_x - 1] == 'b') {
       mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_x)--;
      // hoguera
      st_hoguera();
     
    
      break;
    }
          mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_x)--;
        }
        break;
      case 'S':
      case 's':
        if (*player_y < MAP_SIZE_Y - 1 && mapa->data[*player_y + 1][*player_x] != '#') {
          if (mapa->data[*player_y+ 1][*player_x] == 'd') {
      // Cambiar al siguiente mapa
      load_map_from_file("mapa2.csv", mapa);
 
      break;
    }
     if (mapa->data[*player_y + 1][*player_x] == 'e') {
       mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_y)++;
      // combate
      st_combate();
    
    
      break;
    }
     if (mapa->data[*player_y + 1][*player_x] == 'b') {
       mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_y)++;
      // hoguera
      st_hoguera();
    
    
      break;
    }
          mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_y)++;
        }
        break;
      case 'D':
      case 'd':
        if (*player_x < MAP_SIZE_X - 1 && mapa->data[*player_y][*player_x + 1] != '#') {
          if (mapa->data[*player_y][*player_x + 1] == 'd') {
      // Cambiar al siguiente mapa
      load_map_from_file("mapa2.csv", mapa);

      break;
    }
     if (mapa->data[*player_y ][*player_x + 1] == 'e') {
       mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_x)++;
      // combate
      st_combate();
      
    
      break;
    }
    if (mapa->data[*player_y ][*player_x + 1] == 'e') {
       mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_x)++;
      // hoguera
      st_hoguera();
      
    
      break;
    }
          mapa->data[*player_y][*player_x] = '.'; // Restaurar el espacio vacío anterior
          (*player_x)++;
        }
        break;
      default:
        break;
    }
        
  }

  fclose(file);

  // Vaciar el archivo
  file = fopen(file_path, "w");
  if (file == NULL) {
    printf("Error al abrir el archivo.");
    exit(1);
  }
  fclose(file);
}

void PrintArchivo(const char* buffer)
{
    // Abrir el archivo en modo de escritura (borrar contenido existente)
    FILE* archivo = fopen("texto.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Guardar el contenido del buffer en el archivo
    fprintf(archivo, "%s", buffer);

    // Cerrar el archivo
    fclose(archivo);

    // Imprimir el contenido del buffer en la consola
    printf("%s", buffer);
    sleep(1.5);
}

// Cambia el equipo del jugador
void cambioEquipo(Jugador *pj) {
  char buffer[999]; 
  sprintf(buffer,"¿Que objeto desea equipar?\n");
  PrintArchivo(buffer);
  sprintf(buffer,"1. Espada principal\n");
  PrintArchivo(buffer);
  sprintf(buffer,"2. Espada secundaria\n");
  PrintArchivo(buffer);
  sprintf(buffer,"3. Escudo\n");
  PrintArchivo(buffer);
  // printf("4. Armadura\n");
  int opc;
  char nombreObj[30];
  Objeto *espSecEquip;
  scanf("%d", &opc);
  getchar();
  switch (opc) {
  case 1:

    printf("¿Que espada desea equipar?\n");
    scanf("%[^\n]", nombreObj);
    getchar();
    Objeto *new = valueRet(searchMap(pj->items, nombreObj));
    // En caso de no tenerla no la puede equipar
    if (!new) {
      printf("No tienes ese objeto\n");
      getchar();
      break;
    }
    // En caso de tenerla pero no tener ataque no la puede equipar
    else if(new->atk == 0) {
      printf("No puedes equipar eso\n");
      getchar();
      break;
    }
    else if (new->cantidad == 0) {
      printf("Solo tienes el que ya esta equipado\n");
      getchar();
      break;
    }
    // se elimina la espada principal y se equipa la nueva
    Objeto *espEquip = valueRet(searchMap(pj->equipo, "Espada"));
    espEquip->cantidad++;
    eraseMap(pj->equipo, "Espada");
    insertMap(pj->equipo, "Espada", new);
    new->cantidad--;
    printf("Se ha equipado la espada\n");
    getchar();
    break;

  case 2:
    // Comprueba que no tenga equipada una segunda espada
    if (searchMap(pj->equipo, "Espada Secundaria")) {
      printf("Ya tienes equipadas 2 espadas\n");
      printf("Deseas cambiar :\n");
      espSecEquip = valueRet(searchMap(pj->equipo, "Espada Secundaria"));
      printf("%s\nDaño : %d\n", espSecEquip->nombre, espSecEquip->atk);
      printf("1. Si\n");
      printf("2. No\n");
      int opc;
      scanf("%d", &opc);
      getchar();
      if (opc == 2) {
        break;
      }
    }
    // En caso de no tenerla la intenta equipar
    
    printf("¿Que espada desea equipar?\n");
    scanf("%[^\n]", nombreObj);
    getchar();
    Objeto *nuevaSec = valueRet(searchMap(pj->items, nombreObj));

    // Si no tiene la espada en el inventario no la puede equipar
    if (!nuevaSec) {
      printf("No tienes ese objeto\n");
      getchar();
      break;
    }
    // En caso de tenerla pero no tener ataque no la puede equipar
    else if(nuevaSec->atk == 0) {
      printf("No puedes equipar eso\n");
      getchar();
      break;
    }
    else if (nuevaSec->cantidad == 0) {
      printf("Solo tienes el que ya esta equipado\n");
      getchar();
      break;
    }
    // Si la tiene la equipa y desequipa el escudo
    if (searchMap(pj->equipo, "Escudo")) {
      pj->armorClass -= 2;
      eraseMap(pj->equipo, "Escudo");
      Objeto *escudo = valueRet(searchMap(pj->items, "Escudo"));
      escudo->cantidad++;
    }
    espSecEquip = valueRet(searchMap(pj->equipo, "Espada Secundaria"));
    if (espSecEquip) {
      espSecEquip->cantidad++;
    }
    eraseMap(pj->equipo, "Espada Secundaria");
    insertMap(pj->equipo, "Espada Secundaria", nuevaSec);
    nuevaSec->cantidad--;
    
    printf("Se ha equipado la espada\n");
    
    getchar();
    break;

  case 3:
    // Comprueba que no tenga equipado un escudo
    if (searchMap(pj->equipo, "Escudo")) {
      printf("Ya tienes equipado un escudo\n");
      getchar();
      break;
    }
    // En caso de no tenerlo lo intenta equipar
    else {
      Objeto *new = valueRet(searchMap(pj->items, "Escudo"));
      // Si no tiene el escudo en el inventario no lo puede equipar
      if (!new) {
        printf("No tienes ese objeto\n");
        getchar();
        break;
      }
      // Si lo tiene lo equipa y desequipa la espada secundaria
      espSecEquip = valueRet(searchMap(pj->equipo, "Espada Secundaria"));
      if (espSecEquip) {
        espSecEquip->cantidad++;
      }
      eraseMap(pj->equipo, "Espada Secundaria");
      insertMap(pj->equipo, "Escudo", new);
      pj->armorClass += 2;
      
      printf("Se ha equipado el escudo\n");
    }
    getchar();
    break;

  case 4:
    printf("¿Que armadura desea equipar?\n");
    scanf("%[^\n]", nombreObj);
    getchar();
    Objeto *armor = valueRet(searchMap(pj->items, nombreObj));
    if (!armor) {
      printf("No tienes ese objeto\n");
      getchar();
      break;
    }
    if (armor->def == 0) {
      printf("No puedes equipar eso\n");
      getchar();
      break;
    }
    eraseMap(pj->equipo, "Armadura");
    insertMap(pj->equipo, "Armadura", armor);
    pj->armorClass = 10 + armor->def + pj->bonifDestreza;
    printf("Se ha equipado la armadura\n");
    printf("Tu clase de armadura es %d\n", pj->armorClass);
    getchar();

  default:
    printf("Opcion no valida\n");
    getchar();
    break;
  }
}

// Imprime los objetos del jugador
void stats(Jugador *pj) {
  // Imprime los stats del jugador
  printf("Nombre : %s\n", pj->nombre);
  printf("Experiencia para el siguiente nivel : %ld\n", pj->psMax * 10 - pj->exp);
  printf("Puntos de vida: %ld\n", pj->pH);
  printf("Puntos de armadura: %d\n", pj->armorClass);
  printf("Bonificador de competencia: %d\n", pj->comp);
  printf("Fuerza: %d\n", pj->fuerza);
  printf("Bonificador de fuerza: %d\n", pj->bonifFuerza);
  printf("Destreza: %d\n", pj->destreza);
  printf("Bonificador de destreza: %d\n", pj->bonifDestreza);

  // Imprime los objetos del jugador
  printf("Objetos:\n");
  Pair *aux = firstMap(pj->items);
  while (aux) {
    Objeto *obj = valueRet(aux);
    char *copiaName = (char *)malloc(30 * sizeof(char));
    strcpy(copiaName, obj->nombre);
    char *primPala = strtok(copiaName, " ");
    printf("-%s\n", obj->nombre);

    // Si es pocion muestra cuantas tiene
    if (strcmp(primPala, "Pocion") == 0) {
      printf("    Cantidad: %d\n", obj->cantidad);
    }
    // Si es espada muestra el ataque
    else if (strcmp(primPala, "Espada") == 0 || strcmp(primPala, "Palo") == 0) {
      printf("    Ataque: %d\n", obj->atk);
      printf("    Cantidad sin equipar: %d\n", obj->cantidad);
    }
    // Si es armadura muestra el defensa
    else if (strcmp(primPala, "Armadura") == 0) {
      printf("    Defensa: %d\n", obj->def);
    }
    aux = nextMap(pj->items);
  }

  // Imprime el equipo del jugador
  printf("Equipo:\n");
  aux = firstMap(pj->equipo);
  while (aux) {
    Objeto *obj = valueRet(aux);
    char *copiaName = (char *)malloc(30 * sizeof(char));
    strcpy(copiaName, obj->nombre);
    char *primPala = strtok(copiaName, " ");
    printf("-%s\n", obj->nombre);

    // Si es espada muestra el ataque
    if (strcmp(aux->key, "Espada") == 0 || strcmp(aux->key, "Espada Secundaria") == 0) {
      printf("    Ataque: %d\n", obj->atk);
    }
    // Si es armadura muestra el defensa
    else if (strcmp(primPala, "Armadura") == 0) {
      printf("    Defensa: %d\n", obj->def);
    }
    aux = nextMap(pj->equipo);
  }
  getchar();
}

// Imprime las opciones de accion del jugador y devuelve la opcion elegida
int printOp(int objSec) {  
  char buffer[999];
  sprintf(buffer,"¿Que desea hacer?\n");
  PrintArchivo(buffer);
  // Si tiene al menos una espada imprime los mensajes correspondientes
  if (objSec != 4) {
    
    if (objSec == 0) {
      sprintf(buffer,"Accion no disponible.\n");
    PrintArchivo(buffer);
    }
    else if (objSec == 1) {
      sprintf(buffer,"1. Atacar\n2. Ataque extra\n 3. Curarse\n 4. Ver stats");
    PrintArchivo(buffer);

    } else if (objSec == 2) {
          sprintf(buffer,"1. Atacar\n2. Protegerse\n 3. Curarse\n 4. Ver stats");
    PrintArchivo(buffer);
    } else if (objSec == 3) {
     sprintf(buffer,"1. Atacar\n2. Recoger espada\n 3. Curarse\n 4. Ver stats");
    PrintArchivo(buffer);
    }
    int opc;
    scanf("%d", &opc);
    getchar();
    return opc;
  }
  // Si no tiene espadas pierde las opciones de atacar
  else {
    sprintf(buffer,"\n1.Recoger una espada\n 2. Curarse\n 3. Ver stats");
    PrintArchivo(buffer);
    int opc;
    scanf("%d", &opc);
    getchar();
    // Se modifican las opciones para que se correspondan con las opciones del
    // jugador
    if (opc == 1) {
      return 2;
    } else if (opc == 2) {
      return 3;
    } else {
      return 4;
    }
  }
}

// Realiza la accion de ataque del jugador o enemigo
void ataque(Jugador *pj, Jugador *enemigo, char *objeto) {
  char buffer[999];
  int acc = rand() % 20 + 1;
  int acc2 = rand() % 20 + 1;
  sprintf(buffer, "Primer dado : %d\n\n Segundo dado : %d\n\n", acc, acc2);
  PrintArchivo(buffer);
  if (enemigo->desventaja == 1) {
    if (acc < acc2) {
      acc = acc2;
    }
  }
   sprintf(buffer,"Dado definitivo : %d\n", acc);
    PrintArchivo(buffer);
  acc += pj->comp;
   sprintf(buffer,"Numero de entrada : %d\n", acc);
    PrintArchivo(buffer);
  // Ataque exitoso
  if (acc >= enemigo->armorClass) {
    int damage;
    Objeto *espada = valueRet(searchMap(pj->equipo, objeto));
    // Ataque critico
    if ((acc - pj->comp) == 20) {
      if (strcmp(objeto, "Espada") == 0) {
        damage = espada->atk * 2 + pj->bonifFuerza;
      }
      else {
        damage = espada->atk * 2;
      }
    }
    // Ataque normal
    else {
      if (strcmp(objeto, "Espada") == 0) {
        damage = espada->atk + pj->bonifFuerza;
      }
      else {
        damage = espada->atk;
      }
    }
    enemigo->pH -= damage;
    // Imprime el resultado del ataque
    if (!pj->prota) {
      if ((acc - pj->comp) == 20) {
       sprintf(buffer,"El enemigo te ha hecho %d de daño (critico)\n",
               damage);
                PrintArchivo(buffer);
      } 
      else {
        sprintf(buffer,"El enemigo te ha hecho %d de daño\n", damage);
         PrintArchivo(buffer);
      }
    }
    // Imprime el resultado del ataque
    else {
      if ((acc - pj->comp) == 20) {
        sprintf(buffer,"Has hecho %d de daño (critico)\n", damage);
         PrintArchivo(buffer);
      } else {
         sprintf(buffer,"Has hecho %d de daño\n", damage);
          PrintArchivo(buffer);
      }
    }
  }
  // Fallo critico, se le cae la espada
  else if ((acc - pj->comp) == 1) {
    if (!pj->prota) {
      sprintf(buffer,"El enemigo ha fallado\n");
      PrintArchivo(buffer);
      pj->desventaja = 1;
      if (strcmp(objeto, "Espada") == 0) {
        pj->desarmadoPrin = 1;
        sprintf(buffer,"El enemigo ha perdido su espada principal\n");
        PrintArchivo(buffer);
      } else {
        pj->desarmadoSec = 1;
        sprintf(buffer,"El enemigo ha perdido su espada secundaria\n");
        PrintArchivo(buffer);
      }
    } else {
      sprintf(buffer,"Has fallado\n");
       PrintArchivo(buffer);
      pj->desventaja = 1;
      if (strcmp(objeto, "Espada") == 0) {
        pj->desarmadoPrin = 1;
         sprintf(buffer,"Has perdido tu espada principal\n");
          PrintArchivo(buffer);
      } else {
        pj->desarmadoSec = 1;
         sprintf(buffer,"Has perdido tu espada secundaria\n");
          PrintArchivo(buffer);
      }
    }
  }
  // Ataque fallido
  else {
    if (enemigo->cubierto) {
      pj->desventaja = 1;
    }
    if (!pj->prota) {
     sprintf(buffer,"El enemigo ha fallado\n");
     PrintArchivo(buffer);
    } else {
      sprintf(buffer,"Has fallado\n");
      PrintArchivo(buffer);
    }
  }
}

// Curarse con pocion durante el combate
int usarPocion(Jugador *pj) {
  char buffer[999];
  // Comprueba que tenga pociones
  Objeto *pocion = valueRet(searchMap(pj->items, "Pocion"));
  if (!pocion) {
    if (pj->prota) {
      sprintf(buffer,"No tienes pociones\n");
       PrintArchivo(buffer);
    }
    return 0;
  }
  // Se cura
  else {
    int curacion = pj->psMax - pj->pH;
    pj->pH += pocion->curacion;
    if (pj->pH > pj->psMax) {
      pj->pH = pj->psMax;
      if (pj->prota) {
         sprintf(buffer,"Te has curado %d puntos de vida\n", curacion);
          PrintArchivo(buffer);
      }
      else {
       sprintf(buffer,"El enemigo se ha curado\n");
       PrintArchivo(buffer);
      }
    }
    else {
      if (pj->prota) {
        sprintf(buffer,"Te has curado %d puntos de vida\n", pocion->curacion);
         PrintArchivo(buffer);
      }
      else {
         sprintf(buffer,"El enemigo se ha curado\n");
          PrintArchivo(buffer);
      }
    } 

    pocion->cantidad--;
    if (pocion->cantidad == 0) {
      eraseMap(pj->items, "Pocion");
      if (pj->prota) {
         sprintf(buffer,"Se han acabado las pociones\n");
         PrintArchivo(buffer);
      }
    }
  }
  return 1;
}

// Modifica la accion extra si el jugador esta desarmado
int detCaida(Jugador *pj, int accExtra) {
    char buffer[999];
  // Si esta desarmado pero tiene 2 espadas
  if (pj->desarmadoPrin == 1 && accExtra == 1) {
    if (pj->prota)
       sprintf(buffer,"No puedes atacar con la espada principal\n");
        PrintArchivo(buffer);
    accExtra = 3;
  }
  // Si esta desarmado pero tiene 2 espadas
  else if (pj->desarmadoSec == 1 && accExtra == 1) {
    if (pj->prota)
       sprintf(buffer,"No puedes atacar con la espada secundaria\n");
        PrintArchivo(buffer);
    accExtra = 3;
  }
  // Si esta desarmado de ambas manos o tiene solo una espada que se le cayo y
  // un escudo
  else if (pj->desarmadoPrin == 1 && accExtra == 0 ||
           pj->desarmadoPrin == 1 && pj->desarmadoSec == 1 ||
           pj->desarmadoPrin == 1 && accExtra == 2) {
    sprintf(buffer,"No puedes atacar\n");
    PrintArchivo(buffer);
    accExtra = 4;
  }
  return accExtra;
}

// Realiza el turno del jugador o enemigo
void turnoPj(Jugador *pj, Jugador *enemigo) {
  int opc;
    char buffer[999];

  // Define que accion extra tiene el personaje
  int accExtra = 0;
  Pair *secundario = searchMap(pj->equipo, "Espada Secundaria");
  if (!secundario || (secundario && secundario->key == NULL)) {
    secundario = searchMap(pj->equipo, "Escudo");
  }
  if (!secundario || (secundario && secundario->key == NULL)) {
    secundario = (Pair *)malloc(sizeof(Pair));
    secundario->key = (char *)malloc(sizeof(char) * 5);
    secundario->key = "Nada";
  }
  if (strcmp(secundario->key, "Espada Secundaria") == 0) {
    accExtra = 1;
  } else if (strcmp(secundario->key, "Escudo") == 0) {
    accExtra = 2;
  }
  // Variable para que el enemigo solo diga una vez su vida
  int mostVidaEne = 0;
  int accOriginal = accExtra;
  // Bucle para que el jugador elija una accion valida
  while (true) {
    accExtra = detCaida(pj, accExtra);

    // Si es jugador pide la accion, si es enemigo la elige aleatoriamente
    if (pj->prota) {
      sprintf(buffer,"Salud : %ld\n", pj->pH);
      PrintArchivo(buffer);


      opc = printOp(accExtra);
    } 
    // Da indicios de la vida del enemigo
    else {
      if (!mostVidaEne) {
        mostVidaEne = 1;
        float porcVida = pj->pH * 1.0 / pj->psMax;
        if (porcVida == 1) {
           sprintf(buffer,"El enemigo se ve en perfecto estado\n");
            PrintArchivo(buffer);
        }
        else if (porcVida >= 0.75) {
           sprintf(buffer,"El enemigo no parece tener heridas\n");
            PrintArchivo(buffer);
        }
        else if (porcVida >= 0.5) {
           sprintf(buffer,"El enemigo se ve adolorido\n");
            PrintArchivo(buffer);
        }
        else if (porcVida >= 0.25) {
           sprintf(buffer,"El enemigo se ve bastante herido\n");
            PrintArchivo(buffer);
        }
        else {
           sprintf(buffer,"No sabes como se mantiene en pie\n");
            PrintArchivo(buffer);
        }
        getchar();
      }
      opc = rand() % 3 + 1;
      // Si sale opcion extra pero no tiene nada equipado elige ataque
      if (opc == 2 && accExtra == 0) {
        opc = 1;
      }
      else if (opc == 1 && accExtra == 4) {
        opc = 2;
      }
    }

    // Realiza la accion
    switch (opc) {
    case 1:
      if (!pj->desarmadoPrin) {
        ataque(pj, enemigo, "Espada"); 
        }
      else if (pj->desarmadoPrin && !pj->desarmadoSec && accOriginal == 1) {
        ataque(pj, enemigo, "Espada Secundaria");
      }
      else {
         sprintf(buffer,"No puedes atacar\n");
          PrintArchivo(buffer);
        break;
      }
      getchar();
      return;

    case 2:
      // No tiene equipo para realizar acciones extras
      if (accExtra == 0) {
        sprintf(buffer,"No disponible\n");
        PrintArchivo(buffer);
        getchar();
        break;
      }
      // Ataque extra
      else if (accExtra == 1) {
        if (pj->prota == 1) {
          sprintf(buffer,"Primer ataque\n");
          PrintArchivo(buffer);
          ataque(pj, enemigo, "Espada");
           sprintf(buffer,"Segundo ataque\n");
           PrintArchivo(buffer);
          ataque(pj, enemigo, "Espada Secundaria");
        } else {
          ataque(pj, enemigo, "Espada");
          ataque(pj, enemigo, "Espada Secundaria");
        }
      }
      // Protegerse
      else if (accExtra == 2) {
        pj->armorClass += 2;
        pj->cubierto = 1;
        if (pj->prota)  {
           sprintf(buffer,"Te has cubierto\n");  PrintArchivo(buffer);}
        else {
           sprintf(buffer,"El enemigo se ha cubierto\n");  PrintArchivo(buffer);}
      }
      // Recoger una espada
      else {
        if (pj->prota){
          sprintf(buffer,"Recoges el arma del suelo\n");
          PrintArchivo(buffer);}
        else  {
          sprintf(buffer,"El enemigo recogio una espada\n");
          PrintArchivo(buffer);}
        if (pj->desarmadoPrin == 1) {
          pj->desarmadoPrin = 0;
        } else {
          pj->desarmadoSec = 0;
        }
      }
      getchar();
      return;

    case 3:
      // No se puede curar
      if (usarPocion(pj) == 0) {
        break;
      }
      // Se cura
      else {
        getchar();
        return;
      }

    case 4:
      stats(pj);
      break;

    default:
        sprintf(buffer,"Opcion no valida\n");
        PrintArchivo(buffer);
      break;
    }
  }
}

// Realiza el combate entre el jugador y el enemigo mientras ambos tengan vida
void combate(Jugador *pj, Jugador *enemigo) {
  char buffer[999];
  int iniciativaPj = rand() % 20 + 1;
  int iniciativaEnemigo = rand() % 20 + 1;
  if (iniciativaPj > iniciativaEnemigo) {
    pj->turno = 1;
    enemigo->turno = 0;
  } else {
    pj->turno = 0;
    enemigo->turno = 1;
  }
  while (pj->pH > 0 && enemigo->pH > 0) {
    if (pj->turno == 1) {
      sprintf(buffer, "Es tu turno\n");
      PrintArchivo(buffer);
      // Si tiene desventaja la quita
      if (pj->desventaja == 1 && pj->desarmadoPrin == 0 &&
          pj->desarmadoSec == 0) {
        pj->desventaja = 0;
      }
      // Si esta cubierto lo quita
      if (pj->cubierto == 1) {
        pj->cubierto = 0;
        pj->armorClass -= 2;
      }
      turnoPj(pj, enemigo);
      pj->turno = 0;
      enemigo->turno = 1;
    } else {
      sprintf(buffer,"Turno del enemigo\n");
      PrintArchivo(buffer);
      // Si tiene desventaja la quita
      if (enemigo->desventaja == 1 && enemigo->desarmadoPrin == 0 &&
          enemigo->desarmadoSec == 0) {
        enemigo->desventaja = 0;
      }
      // Si esta cubierto lo quita
      if (enemigo->cubierto == 1) {
        enemigo->cubierto = 0;
        enemigo->armorClass -= 2;
      }
      turnoPj(enemigo, pj);
      pj->turno = 1;
      enemigo->turno = 0;
    }
  }
}

// Realiza la subida de nivel del jugador
void subidaNivel(Jugador *pj) {
  printf("Has subido de nivel\n");
  pj->exp -= pj->psMax * 10;
  pj->psMax += 5;
  pj->pH = pj->psMax;
  pj->comp = 2 + (pj->psMax - 15) / 5;
  printf("Tus puntos de vida maximos son %ld\n", pj->psMax);
  printf("Tu bonificador de competencia es %d\n", pj->comp);
  getchar();
  Objeto *armadura;
  if (pj->fuerza < 20 && pj->destreza < 20) {
    if (pj->psMax % 2 == 0) {
      printf("Puedes sumarle dos a una caracteristica\n");
      printf("1. Fuerza: actualmente = %d\n", pj->fuerza);
      printf("2. Destreza: actualmente = %d\n", pj->destreza);
      int opc;
      scanf("%d", &opc);
      getchar();

      // Suma 2 a la fuerza
      if (opc == 1) {
        pj->fuerza += 2;
        if (pj->fuerza >= 20) {
          pj->fuerza = 20;
          printf("Has llegado al maximo de fuerza\n");
        }
        pj->bonifFuerza = (pj->fuerza - 10) / 2;
        printf("Tu bonificador de fuerza es %d\n", pj->bonifFuerza);
      }
      // Suma 2 a la destreza
      else {
        pj->destreza += 2;
        if (pj->destreza >= 20) {
          pj->destreza = 20;
          printf("Has llegado al maximo de destreza\n");
        }
        pj->bonifDestreza = (pj->destreza - 10) / 2;
        armadura = valueRet(searchMap(pj->equipo, "Armadura"));
        if (armadura) {
          pj->armorClass = 10 + armadura->def + pj->bonifDestreza;
        }
        else {
          pj->armorClass = 10 + pj->bonifDestreza;
        }
        printf("Tu bonificador de destreza es %d\n", pj->bonifDestreza);
      }
    }
  }
  else if (pj->fuerza < 20) {
    printf("Tu destreza esta al maximo\n");
    printf("Se suma automaticamente a la fuerza\n");
    pj->fuerza += 2;
    if (pj->fuerza >= 20) {
      pj->fuerza = 20;
      printf("Has llegado al maximo de fuerza\n");
    }
    pj->bonifFuerza = (pj->fuerza - 10) / 2;
    printf("Tu bonificador de fuerza es %d\n", pj->bonifFuerza);
  }
  else if (pj->destreza < 20) {
    printf("Tu fuerza esta al maximo\n");
    printf("Se suma automaticamente a la destreza\n");
    pj->destreza += 2;
    if (pj->destreza >= 20) {
      pj->destreza = 20;
      printf("Has llegado al maximo de destreza\n");
    }
    pj->bonifDestreza = (pj->destreza - 10) / 2;
    armadura = valueRet(searchMap(pj->equipo, "Armadura"));
    if (armadura) {
      pj->armorClass = 10 + armadura->def + pj->bonifDestreza;
    }
    else {
      pj->armorClass = 10 + pj->bonifDestreza;
    }
    printf("Tu bonificador de destreza es %d\n", pj->bonifDestreza);
  }
  else {
    printf("Tus caracteristicas estan al maximo\n");
  }
}

// Da inicio al combate y luego otorga el loot en caso de ganar
void estructuraCombate(Jugador *pj, Jugador *enemigo) {
  char buffer[999]; 
  sprintf(buffer,"Comienza el combate\n");
  PrintArchivo(buffer);

  combate(pj, enemigo);
  if (pj->pH <= 0) {
    sprintf(buffer,"Has muerto\n");
    printf(buffer);
    exit(EXIT_SUCCESS);
  } else {
    
    sprintf(buffer,"Has obtenido %ld de experiencia\n", enemigo->exp);
    PrintArchivo(buffer);
    pj->exp += enemigo->exp;
    while (pj->exp >= (pj->psMax * 10)) {
      subidaNivel(pj);
    }
  }
  if (enemigo->pH <= 0) {
    Pair *aux = firstMap(enemigo->items);
    while (aux) {
      Objeto *obj = valueRet(aux);
      Objeto *itemJug = valueRet(searchMap(pj->items, obj->nombre));
      if (!itemJug) {
        insertMap(pj->items, obj->nombre, obj);
      } else {
        if (strcmp(obj->nombre,"Pocion") && obj->cantidad == 0)
          obj->cantidad++;
        itemJug->cantidad += obj->cantidad;
      }
      sprintf(buffer,"Has obtenido %s\n", obj->nombre);
       PrintArchivo(buffer);
      aux = nextMap(enemigo->items);
    }
  }
  pj->desarmadoPrin = 0;
  pj->desarmadoSec = 0;
  pj->desventaja = 0;
}

// Genera una caracteristica aleatoria
int generadorCaract() {
  int d1 = rand() % 6 + 1;
  int d2 = rand() % 6 + 1;
  int d3 = rand() % 6 + 1;
  int d4 = rand() % 6 + 1;
  printf("Los dados han sido %d, %d, %d, %d\n", d1, d2, d3, d4);
  int min = d1;
  if (d2 < min) {
    min = d2;
  }
  if (d3 < min) {
    min = d3;
  }
  if (d4 < min) {
    min = d4;
  }
  printf("El valor de la caracteristica es %d\n", d1 + d2 + d3 + d4 - min);
  return d1 + d2 + d3 + d4 - min;
}

// Crea un nuevo jugador
Jugador *crearJugador() {
  char buffer[100]; 

  Jugador *pj = (Jugador *)malloc(sizeof(Jugador));
  sprintf(buffer,"¿Cual es tu nombre?\n");
  PrintArchivo(buffer);
  char *nombre = (char *)malloc(30 * sizeof(char));
  scanf("%[^\n]", nombre);
  getchar();

  // Solo esta por un tema de testing
  printf("Es jugador?\n");
  char resp[3];
  scanf("%s", resp);
  getchar();

  pj->nombre = nombre;
  pj->items = createMap(10);
  pj->equipo = createMap(3);
  pj->pH = 10;
  pj->psMax = 10;
  pj->comp = 2;
  pj->exp = 0;
  printf("Se realizaran lanzamientos aleatorios para determinar la fuerza y la destreza del personaje\n");
  printf("Primer lanzamiento\n");
  int caract1 = generadorCaract();
  printf("Segundo lanzamiento\n");
  int caract2 = generadorCaract();

  // Se asignan las caracteristicas
  printf("¿Cual sera tu caracteristica principal?\n");
  printf("1. Fuerza: Bonificador al daño del arma\n");
  printf("2. Destreza: Bonificador a la armadura\n");
  int opc;
  scanf("%d", &opc);
  getchar();
  if (opc == 1) {
    if (caract1 >= caract2) {
      pj->fuerza = caract1 + 2;
      pj->bonifFuerza = (pj->fuerza - 10) / 2;
      pj->destreza = caract2 + 1;
      pj->bonifDestreza = (pj->destreza - 10) / 2;
    } 
    else {
      pj->fuerza = caract2 + 2;
      pj->bonifFuerza = (pj->fuerza - 10) / 2;
      pj->destreza = caract1 + 1;
      pj->bonifDestreza = (pj->destreza - 10) / 2;
    }
  }
  else {
    if (caract1 >= caract2) {
      pj->fuerza = caract2 + 1;
      pj->bonifFuerza = (pj->fuerza - 10) / 2;
      pj->destreza = caract1 + 2;
      pj->bonifDestreza = (pj->destreza - 10) / 2;
    } 
    else {
      pj->fuerza = caract1 + 1;
      pj->bonifFuerza = (pj->fuerza - 10) / 2;
      pj->destreza = caract2 + 2;
      pj->bonifDestreza = (pj->destreza - 10) / 2;
    }
  }
  printf("Bonificador de fuerza : %d\n", pj->bonifFuerza);
  printf("Bonificador de destreza : %d\n", pj->bonifDestreza);

  if (strcmp(resp, "si") == 0)
    pj->prota = 1;
  else {
    pj->prota = 0;
    // Solo test para que los enemigos den exp
    printf("¿Cuanta experiencia dara?\n");
    int xp = 0;
    scanf("%d", &xp);
    getchar();
    pj->exp = xp;
  }
  pj->turno = 0;
  pj->armorClass = 10 + pj->bonifDestreza;
  pj->cubierto = 0;
  pj->desventaja = 0;

  // Inserta los objetos iniciales
  Objeto *espada = (Objeto *)malloc(sizeof(Objeto));
  espada->nombre = "Palo de madera";
  espada->atk = 2;
  espada->def = 0;
  espada->curacion = 0;
  espada->cantidad = 0;
  insertMap(pj->items, espada->nombre, espada);
  insertMap(pj->equipo, "Espada", espada);
  Objeto *pocion = (Objeto *)malloc(sizeof(Objeto));
  pocion->nombre = "Pocion";
  pocion->atk = 0;
  pocion->def = 0;
  pocion->curacion = 5;
  pocion->cantidad = 2;
  insertMap(pj->items, "Pocion", pocion);

  // Test
  printf("Tendra escudo?\n");
  printf("1. Si\n");
  printf("2. No\n");
  scanf("%d", &opc);
  getchar();
  if (opc == 2) {
    return pj;
  }
  Objeto *escudo = (Objeto *)malloc(sizeof(Objeto));
  escudo->nombre = "Escudo";
  escudo->atk = 0;
  escudo->def = 2;
  escudo->curacion = 0;
  escudo->cantidad = 0;
  insertMap(pj->items, "Escudo", escudo);
  insertMap(pj->equipo, "Escudo", escudo);
  pj->armorClass += 2;
  return pj;
}

// Zona de descanso y recupera la vida maxima
void hoguera(Jugador *pj) {
  pj->pH = pj->psMax;
  printf("Has descansado en la hoguera\n");
  getchar();
  while (true) {
    printf("¿Deseas realizar algo más?\n");
    printf("1. Cambiar equipo\n");
    printf("2. Ver stats\n");
    printf("3. Salir\n");
    int opc;
    scanf("%d", &opc);
    getchar();
    switch (opc) {
      case 1:
        cambioEquipo(pj);
        break;
      
      case 2:
        stats(pj);
        break;
      
      default:
        return;
    }
  }
}

// Lectura de enemigos csv
HashMap *lecturaPjs() {
  FILE *archivo = fopen("enemigos.csv", "r");
  if (!archivo) {
    printf("No se pudo abrir el archivo\n");
    return NULL;
  }
  HashMap *enemigos = createMap(10);
  char *linea = (char *)malloc(100 * sizeof(char));
  fgets(linea, 100, archivo);
  return NULL;
}



int main() {
    int desiredIterationsPerSecond = 5;
    int microsecondsPerIteration = 1000000 / desiredIterationsPerSecond;
   const char* fileEstado = "estado.txt";
  Jugador *yo = crearJugador();
  Jugador *enemigo = crearJugador();

    while (1) {  // Bucle infinito
        Mapa mapa;
 int player_x = 1;
int player_y = 1;

   load_map_from_file("mapa.csv", &mapa);

  while (1) {
    display_map(&mapa, player_x, player_y);
    save_map_to_file("mapatemp.csv", &mapa);

    process_actions("accion.txt", &mapa, &player_x, &player_y);



        printf("Ejecutando lógica...\n");
        if(checkFileForEstado(fileEstado,"combate") == true){
          estructuraCombate(yo, enemigo);
        }
        if(checkFileForEstado(fileEstado,"bonfire") == true){
          hoguera(yo);
        }

        usleep(microsecondsPerIteration);  // Pausa el programa durante los microsegundos calculados
    }

    return 0;
}
}