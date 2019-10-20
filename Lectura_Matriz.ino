int matriz[NUMERO_POSICIONES_Y][NUMERO_POSICIONES_X] = {{1, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}};

int escritura()
{

  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;
  int f = 0;
  int g = 0; 

  for (int i1 = 0; i1 < NUMERO_POSICIONES_Y; i1++)
  {
    d++;
    g++;

    for (int i = 0; i < NUMERO_POSICIONES_X; i++)
    {
      if (matriz[i1][i] == 0)
      {
        b++;
        if (b == 4)
        {
          f = 0;
        }
        else
        {
          f = 1;
        }
      }
    }
    b = 0;

    switch (f)
    {
      case 0:
        Serial.println("         RENGLON SIN NADA");
        g++;
        c++;
        break;
      case 1:

        if (g % 2 == 0) //SI ES PAR VA PARA LA DERECHA
        {
          Serial.println("direcion:DERECHA");
          //SE SETEA LA DIRECION DE LA IMPRESION
          Serial.println("margen");
          MOVER_X(DISTANCIA_MARGEN_IZQ);
          //DISTANCIA DE MARGEN DE LA HOJA

          for (int i = 0; i < NUMERO_POSICIONES_X; i++)
          {
            if (matriz[c][i] == 1)
            {
              Serial.println("punto");
              punto();
              //SE ACTIVA EL SOLENOIDE
              a++;
            }
            else
            {
              Serial.println("espacio");
              //NO ACTIVAR
              a++;
            }
            if (a == 1)
            {
              Serial.println("movimiento 2.54");
              MOVER_X(DISTANCIA_LETRA);
              //SE MUEVE 2.54 mm EN EL EJE X
            }
            if (a == 2)
            {
              Serial.println("movimineto 3.75");
              MOVER_X(DISTANCIA_LyL);
              //SE MUEVE 3.75 mm EN EL EJE X
              a = 0;
            }
            if (i == NUMERO_POSICIONES_X - 1)
            {
              Serial.println("margen");
              MOVER_X(DISTANCIA_MARGEN_DER);
              Serial.println("linea terminada");
              //DISTANCIA DE MARGEN DE LA HOJA
              //EN ESTE PUNTO SE TERMINO DE IMPRIMIR LA LINEA
            }
          }
          c++;
        }
        else //SI ES IMPAR VA PARA LA IZQUIERDA
        {
          Serial.println("direcion:IZQUIERDA");
          //SE SETEA LA DIRECION DE LA IMPRESION
          Serial.println("margen");
          MOVER_X(DISTANCIA_MARGEN_IZQ);
          //DISTANCIA DE MARGEN DE LA HOJA
          for (int i = 0; i < NUMERO_POSICIONES_X; i++)
          {
            if (matriz[c][i] == 1)
            {
              Serial.println("punto");
              punto();
              //SE ACTIVA EL SOLENOIDE
              a++;
            }
            else
            {
              Serial.println("espacio");
              //NO ACTIVAR
              a++;
            }
            if (a == 1)
            {
              Serial.println("movimiento 2.54");
              MOVER_X(DISTANCIA_LETRA);
              //SE MUEVE 2.54 mm EN EL EJE X
            }
            if (a == 2)
            {
              Serial.println("movimineto 3.75");
              MOVER_X(DISTANCIA_LyL);
              //SE MUEVE 3.75 mm EN EL EJE X
              a = 0;
            }
            if (i == NUMERO_POSICIONES_X - 1)
            {
              Serial.println("margen");
              MOVER_X(DISTANCIA_MARGEN_DER);
              Serial.println("linea terminada");
              //DISTANCIA DE MARGEN DE LA HOJA
              //EN ESTE PUNTO SE TERMINO DE IMPRIMIR LA LINEA
            }

          }
          c++;
        }

        if (d == 3)
        {
          Serial.println("RENGLON FINALIZADO");
          //ACÁ IRIA EL MOVIMIETO DEL MOTOR PASO A PASO CON EL ESPACIADO QUE HAY ENTRE RENGLONES
          d = 0;
        }
        break;
    }

  }

  Serial.println("IMPRECION FINALIZADA");
  //EN ESTE PUNTO TERMINO LA IMPRESION DE TODA LA HOJA

}