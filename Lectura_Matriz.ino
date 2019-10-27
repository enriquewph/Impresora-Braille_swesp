int matriz[NUMERO_POSICIONES_Y][NUMERO_POSICIONES_X] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}};
int escritura()
{

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int f = 0;
    int g = 0;
    int n = 0;

    for (int i1 = 0; i1 < NUMERO_POSICIONES_Y; i1++)
    {
        d++;
        g++;

        for (int i = 0; i < NUMERO_POSICIONES_X; i++)
        {
            if (matriz[i1][i] == 1)
            {
                n = 1;
            }
            if (matriz[i1][i] == 0)
            {
                b++;
            }
            if (b == 4 && n == 0)
            {
                f = 0;
            }
            else
            {
                f = 1;
            }
        }
        b = 0;

        switch (f)
        {
        case 0:
            Serial.println("         RENGLON SIN NADA");
            Serial.println(n);
            g++;
            c++;
            break;
        case 1:

            if (g % 2 == 0) //SI ES PAR VA PARA LA DERECHA
            {
                Serial.println("direcion:DERECHA");
                //SE SETEA LA DIRECION DE LA IMPRESION

                EJEX_POSICION_ENCODER_SETPOINT = DISTANCIA_MARGEN_DER;
                MOVIMIENTO_EJEX();
                Serial.println("margen");
                Serial.println("SET: " + String(EJEX_POSICION_ENCODER_SETPOINT));
                Serial.println("ACT: " + String(EJEX_POSICION_ENCODER_ACTUAL));
                //DISTANCIA DE MARGEN DE LA HOJA

                for (int i = 0; i < NUMERO_POSICIONES_X; i++)
                {
                    Serial.println("SETfor: " + String(EJEX_POSICION_ENCODER_SETPOINT));
                    Serial.println("ACTfor: " + String(EJEX_POSICION_ENCODER_ACTUAL));
                    if (matriz[c][i] == 1)
                    {
                        Serial.println("punto");
                        punto();
                        //SE ACTIVA EL SOLENOIDE
                        a++;
                        delay(250);
                    }
                    else
                    {
                        Serial.println("espacio");
                        //NO ACTIVAR
                        a++;
                        delay(250);
                    }
                    if (a == 1)
                    {
                        MOVER(DISTANCIA_LETRA);
                        MOVIMIENTO_EJEX();
                        Serial.println("movimiento 2.54");
                        Serial.println("SET: " + String(EJEX_POSICION_ENCODER_SETPOINT));
                        //SE MUEVE 2.54 mm EN EL EJE X
                    }

                    Serial.println("ACT: " + String(EJEX_POSICION_ENCODER_ACTUAL));
                    if (a == 2)
                    {
                        MOVER(DISTANCIA_LyL);
                        MOVIMIENTO_EJEX();
                        Serial.println("movimineto 3.75");
                        Serial.println("SET: " + String(EJEX_POSICION_ENCODER_SETPOINT));
                        //SE MUEVE 3.75 mm EN EL EJE X
                        a = 0;
                    }

                    Serial.println("ACT: " + String(EJEX_POSICION_ENCODER_ACTUAL));
                    if (i == NUMERO_POSICIONES_X - 1)
                    {
                        Serial.println("margen");
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

                EJEX_POSICION_ENCODER_SETPOINT = DISTANCIA_MARGEN_IZQ;
                MOVIMIENTO_EJEX();
                Serial.println("margen");
                Serial.println("SET: " + String(EJEX_POSICION_ENCODER_SETPOINT));
                Serial.println("ACT: " + String(EJEX_POSICION_ENCODER_ACTUAL));
                //DISTANCIA DE MARGEN DE LA HOJA

                for (int i = 0; i < NUMERO_POSICIONES_X; i++)
                {
                    Serial.println("SETfor: " + String(EJEX_POSICION_ENCODER_SETPOINT));
                    Serial.println("ACTfor: " + String(EJEX_POSICION_ENCODER_ACTUAL));
                    if (matriz[c][i] == 1)
                    {
                        Serial.println("punto");
                        punto();
                        //SE ACTIVA EL SOLENOIDE
                        a++;
                        delay(250);
                    }
                    else
                    {
                        Serial.println("espacio");
                        //NO ACTIVAR
                        a++;
                        delay(250);
                    }
                    Serial.println("SETpunto: " + String(EJEX_POSICION_ENCODER_SETPOINT));
                    Serial.println("ACTpunto: " + String(EJEX_POSICION_ENCODER_ACTUAL));
                    if (a == 1)
                    {

                        MOVER(DISTANCIA_LETRA * -1);
                        MOVIMIENTO_EJEX();
                        Serial.println("movimiento 2.54");
                        Serial.println("SET: " + String(EJEX_POSICION_ENCODER_SETPOINT));
                        //SE MUEVE 2.54 mm EN EL EJE X
                    }

                    Serial.println("ACT: " + String(EJEX_POSICION_ENCODER_ACTUAL));
                    if (a == 2)
                    {
                        MOVER(DISTANCIA_LyL * -1);
                        MOVIMIENTO_EJEX();
                        Serial.println("movimineto 3.75");
                        Serial.println("SET: " + String(EJEX_POSICION_ENCODER_SETPOINT));
                        //SE MUEVE 3.75 mm EN EL EJE X
                        a = 0;
                    }

                    Serial.println("ACT: " + String(EJEX_POSICION_ENCODER_ACTUAL));
                    if (i == NUMERO_POSICIONES_X - 1)
                    {
                        Serial.println("margen");
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
       EJEX_POSICION_ENCODER_SETPOINT=10;
    MOVIMIENTO_EJEX();
    Serial.println("IMPRECION FINALIZADA");
    //EN ESTE PUNTO TERMINO LA IMPRESION DE TODA LA HOJA
}