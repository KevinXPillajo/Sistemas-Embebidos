/*
 *          UNIVERSIDAD TÉCNICA DEL NORTE
 *         FICA/CIERCOM/SISTEMAS EMBEBIDOS
 *            EXAMEN FINAL (pERCEPTRÓN)
 *            
 *  PILLAJO RUALES KEVIN XAVIER        
 */

#include "datos.h"

////////////////////////////////////////////////////////////////////////
//** SE DEFINEN LAS VARIABLES INICIALES DEL SISTEMA**

int N = 300; // N -> DEFINE EL NUMERO DE MUESTRAS DE LA BDD

int M = 5; // M -> DEFINE EL NUMERO DE COLUMNDAS DE LA BDD (INCLUYE ETIQUETA)

int P = 20 ; // DEFINE EL NUMERO DE MUESTRAS DE LA BDD DE PRUEBA

float W[5]={random(0,1000)/1000,random(0,1000)/1000,random(0,1000)/1000,random(0,1000)/1000,random(0,1000)/1000}; // DEFINE EL VECTOR DE PESOS DEL PERCEPTRON ALEATORIAMENTE CON 3 DECIMALES
//float W[5]={0,0,0,0,0};

boolean e = true; // e -> SIRVE PARA INDICAR SI HUBO O NO ERRORES EN UNA ITERACION

int MAX = 100; // MAX -> DEFINE EL NUMERO MÀXIMO DE ITERACIONES, PARA EL CALCULO DE LOS PESOS ADECUADOS, DEL PERCEPTRON

int CONT = 0; // CONT -> SIRVE PARA CONTABILIZAR EL NUMERO DE ERRORES EN UNA ITERACION, CON CIERTOS VALORES DE PESOS

int STOP=0; // VARIABLE PARA FINALIZAR LA EJECUCION DEL SISTEMA

////////////////////////////////////////////////////////////////////////

void setup() {
  
  Serial.begin(9600); // DEFINIMOS EL CLOCK RATE PARA LA COMUNICACION SERIAL
}

void loop() {
  // EN CASO DE QUE ENTRE AL BLOQUE IF SE IMPRIME UN MENSAJE EN LA VENTANA SERIAL, 
  // INDICANDO QUE EL SISTEMA ESTA CALCULANDO LOS PESOS ADECUADOS PARA EL PERCEPTRON
  
  if( e && CONT<MAX){  // SI ENTRO EN ESTE BLOQUE QUIERE DECIR, QUE AUN EXISTEN ERRORES CON LOS PESOS ESTABLECIDOS EN ESE MOMENTO
 
    Serial.println("ENTRENANDO EL SISTEMA");
    
    float A = 0.5;   // A-> FACTOR DE APRENDIZAJE DEL SISTEMA (EL VALOR DE LOS PESOS CAMBIARAN DE ACUERDO A ESTE VALOR)
    
    int ne = training(A); // TRAINING ES LA FUNCION QUE PERMITE ENTRENAR AL SISTEMA, SIMPLEMENTE PASANDOLE COMO PARAMETRO EL FACTOR DE APRENDIZAJE
                          // Y DEVUELVE COMO RESULTADO EL NUMERO DE ERRORES OBTENIDOS PARA ESE ENTRENAMIENTO(PARA EL VALOR DE LOS PESOS EN ESE MOMENTO)

    Serial.println("Nro de errores:"+String(ne)); // IMPRIME EL NUMERO DE ERRORES EN ESE MOMENTO 
    
    CONT++; //AUMENTA EL VALOR DE CONTADOR DE ITERACIONES
    
  }else{
    if(STOP==0){
     
      int c = 0;   // c-> contador de aciertos
      
      Serial.println("ITERACION NRO::::: "+String(CONT));   // IMPRIME EL NUMERO DE ITERACIONES REALIZADAS PARA OBTENER LOS PESOS 
      
      for (int i = 0;  i<P; i++){     // SE EMPIEZA A RECORRER LA BDD DE PRUEBA PARA CALCULAR LA EFICIENCIA DEL SISTEMA CON LOS PESOS OBTENIDOS
        
        int label = test[i][M-1];       // SE LEE EL VALOR DE ETIQUETA PARA EL REGISTRO i DE LA BDD DE PRUEBA

 /////////////////////////////////////////////////////////////////////////////  
        int real_y;   // SE INICIA LA VARIABLE REAL_Y LA CUAL TENDRA UN VALOR DE 1 SI LA ETIQUETA ES IGUAL A 1 Y 0 SI LA ETIQUETA ES IGUAL A 2
        
        if(label == 1){
          real_y = 1;
        }else{
          real_y = 0;  
        }
        
 ///////////////////////////////////////////////////////////////////////////////

        float SUM = 0;  // SUM ALMACENA LA SUMATORIA DE LOS VALORES DE ENTRADA MULTIPLICADOS CADA UNO, POR SU RESPECTIVO PESO
       
        for (int j = 0; j<M; j++){  // EL FOR RECORRE CADA UNA DE LAS VARIABLES DE ENTRADA DEL REGISTRO i LEIDO EN ESE MOMENTO
  
          if (j<M-1){
            SUM=SUM+test[i][j]*W[j];
          }
          else {
            SUM=SUM+W[j];
          }
          
        }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
        int output_y ;            // output_y ALMACENARA UN VALOR IGUAL A CERO SI LA SUMATORIA EN SUM, ES MENOR QUE CERO Y UN UNO EN CASO CONTRARIO, 
                                  // ESTO ESTA ASOCIADO A LA SALIDA CALCULADA, SI output_y ES IGUAL A 1, EL SISTEMA PREDICE QUE LA ENTRADA (O MUESTRA) 
                                 // CORRESPONDE A UNA ETIQUETA DE VALOR 1, CASO CONTRARIO CORRESPONDE A UNA ETIQUETA DE VALOR 2
         
        if(SUM>=0){
          output_y = 1;
        }else{
          output_y = 0;
        }
        
        if(real_y==output_y){
          Serial.println(" OK !");
          c++;
        }else{
          Serial.println(" ERROR !");
        }
////////////////////////////////////////////////////////////////////////////////////////////////////////
      }
      
      STOP = 1;     // SE ASIGNA STOP IGUAL A 1, PARA QUE EL SISTEMA PARE
  
      Serial.println("*PESOS**");  // SE IMPRIME LOS PESOS OBTENIDOS
      String str_w = "";
      for (int k = 0; k < M; k++){
        str_w+=String(W[k])+";";
      } 
      Serial.println(str_w);
 ////////////////////////////////////////////////////////////////////////////////////////////////////////
      // r-> rendimiento
      Serial.println("ACIERTOS :"+String(c));
      float r  =  ((float)c/P)*100;
      Serial.print("Rendimiento del sistema : ");
      Serial.print(r);
      Serial.println("%");
      
    }
  }
}

/**
 * ESTA FUNCION SIRVE PARA ENYTRENAR AL SISTEMA, EN DONDE, DE ACUERDO AL ALGORITMO DE PERCEPTRON SIMPLE
 * VARIA LOS PESOS DEFINIDOS, CUANDO EL SISTEMA AUN TIENE ERRORES CON ESTOS
 */
int training (float A){
  
  e = false;
  // CONTADOR DE ERRORES 
  int errors = 0;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  for (int i = 0;  i<N; i++){    // SE RECORRE LA BDD
 
    int label = bdd[i][M-1];  // SE LEE LA ETIQUETA DEL REGISTRO i DE LA BDD

    int real_y;    // SE ASOCIA LA ETIQUETA A UN 0 O 1 ; 1-> SI LA ETIQUETA ES 1; UN 0-> SI LA ETIQUETA ES 2
    if (label==1){
      real_y=1;
      }
    else {
      real_y=0;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////
    
    float SUM = 0; // SUM ALMACENA LA SUMATORIA DE LOS VALORES DE ENTRADA MULTIPLICADOS CADA UNO, POR SU RESPECTIVO PESO
    
    for (int j = 0; j<M; j++){
      if(j<M-1){
        SUM = SUM+bdd[i][j]*W[j];
      }else{
        SUM = SUM+W[j];   
      }
    }
////////////////////////////////////////////////////////////////////////////////////////////////////
    int output_y ;            // output_y ALMACENARA UN VALOR IGUAL A CERO SI LA SUMATORIA EN SUM, ES MENOR QUE CERO Y UN UNO EN CASO CONTRARIO, 
                              // ESTO ESTA ASOCIADO A LA SALIDA CALCULADA, SI output_y ES IGUAL A 1, EL SISTEMA PREDICE QUE LA ENTRADA (O MUESTRA) 
                              // CORRESPONDE A UNA ETIQUETA DE VALOR 1, CASO CONTRARIO CORRESPONDE A UNA ETIQUETA DE VALOR 2
    
    if(SUM>=0){
      output_y = 1;
    }else{
      output_y = 0;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////

    int error = real_y - output_y;   // importante error siempre será 1 o -1 cuando haya error, si no hay error es igual a cero
    
    //Serial.print(String(i)+") ");
    
    //Serial.print(real_y);
    //Serial.print("::::");
    //Serial.println(output_y);
    
    if(error!=0){ // en caso de fallar (error diferente de cero) aumenta el contador de errores
      
      errors++;
      
    }
////////////////////////////////////////////////////////////////////////////////////////////////////
    // VARIACION DE LOS PESOS
    for(int k = 0; k<M; k++){
      
      if(k<M-1){
        W[k]=W[k]+A*error*bdd[i][k];// PESOS PARA VARIABLES DE ENTRADA(SENSORES)
      }else{
        W[k]=W[k]+A*error;// PESO PARA LA ETIQUETA
      }
      // IMPRIMIENDO EL REGISTRO EN DONDE NO ACERTO EL ALGORITMO
      if(error!=0){
        Serial.print(bdd[i][k]);
        Serial.print(";");
      }
    }
    // IMPRIMIENDO SALTO DE LINEA
    if(error!=0)
      Serial.println();
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  // SI HUBO ERRORES CAMBIO EL VALOR DE e A TRUE, INDICANDO QUE CON LOS PESOS ACTUALES AUN EXISTEN ERRORES
  if(errors>0)
    e=true;
    // SE DEVULVE EL NUMERO DE ERRORES OBTENIDOS CON LOS PESOS ACTUALES
    
  return errors;
}
