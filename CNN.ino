#include "matriz_entrenamiento.h"
float datos_prueba[5]={6.2,2.9,4.3,1.3,2}; //6,2  2,9 4,3 1,3
int respuesta;

void setup() {
 Serial.begin(9600);
}



void loop() {
  cnn(3,5,120);
  delay(5000);
}



void cnn (int etiquetas, int tam_col, int tam_fil){
  int i;
  int j;
  int l;
  int p;
  float centroid=0;
  float promedio=0;
  float distancia_menor=3000;
  float distancia=0;
  int label;
  int f;
  int c;
  int s=0; // Contar los datos en source
  

/*  
 *   centroides -> promedio
 *                 promedio por columna y por etiqueta
 *                 almaceno vectores 
 *                 knn entre vectores y matriz de entrenamiento
 */

 float centroides [etiquetas][tam_col];
 for(i=0;i<etiquetas;i++){
   for(j=0;j<tam_col;j++){
    if(j==tam_col-1)
    centroides [i][j]=i+1;
    else
    centroides[i][j]=0;
    }
  }

   for(l=0;l<etiquetas;l++){
     for(i=0;i<tam_col-1;i++){
       for(j=(40*l);j<40*(l+1);j++){
        centroid=centroid+matriz[j][i];
        }
          centroides[l][i]=centroid/40;
          Serial.print(centroides[l][i],4);
          Serial.print(',');
          centroid=0;
      }
          Serial.println(centroides[l][tam_col-1]);
   } 
    
  // Encontrar la distancia entre los centroides y la matriz de entrenamiento 
  // para comparar si clasifica adecuadamente

           // for -> filas de matriz de entrenamiento 
             // for -> filas de matriz centroide
              //for -> columnas 
              
   for (i=0;i<tam_fil;i++){
    for (j=0;j<etiquetas;j++){
      for (l=0;l<tam_col-1;l++){
        promedio=promedio+pow(centroides[j][l]-matriz[i][l],2);
      }

      distancia=sqrt(promedio);
      if(distancia<distancia_menor){
        distancia_menor=distancia;
        label=centroides[j][tam_col-1];     
        }
        
      promedio=0;
    }
     distancia_menor=3000;
    if (matriz[i][tam_col-1]==label){
      Serial.println(String(i)+":");
      Serial.println("Drenaje");
    }
    else {
      Serial.println(String(i)+":");
      Serial.println("Source");
      s++;
       float matriz_s[s][tam_col];
       for(f=0;f<s;f++){
        for(c=0;c<tam_col;s++){
          Serial.print(matriz_s[f][c]=matriz[i][c]);
          Serial.println(',');
        }
     Serial.println(',');
       }
    }
   }
 
  int dist_mayor=2000;
      // si clasifica correctamente el sistema no realiza ninguna accion
        if(label==matriz_d[fil][4]){
                    }
        // si clasifica de forma erronea, almacena en matriz s
          else{
           for(;col_s<5;col_s++){
              matriz_s[fil_s1][col_s]=matriz[fil][col_d];
               }
                col_s=0;
                fil_s1++;
               }
  }
   // imprime los valores almacenados en matriz s
fil_s=0;
for(;fil_s<fil_s1;fil_s++){
     for(;col_s<5;col_s++){
        Serial.print(matriz_s[fil_s][col_s]);
        Serial.print(',');
      }
      col_s=0;
      Serial.println(' ');
  }
 fil_s1=-1; 
 
fil_s=0;
     dist_mayor=2000;
     // si clasifica correctamente el sistema no realiza ninguna accion
        if(label==matriz_d[fil][4]){
                    }
      // si clasifica de forma erronea, almacena en matriz s
          else{
          for(;col_s<5;col_s++){
          matriz_s[fil_s1][col_s]=matriz[fil][col_d];
           }
           col_s=0;
           fil_s1++;
               }
  }
   // imprime los valores almacenados en matriz s
fil_s=0;
for(;fil_s<fil_s1;fil_s++){
     for(;col_s<5;col_s++){
        Serial.print(matriz_s[fil_s][col_s]);
        Serial.print(',');
      }
      col_s=0;
      Serial.println(' ');
  }
 fil_s1=-1; 
 
    

  }


     
