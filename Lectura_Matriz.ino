int matriz[NUMERO_POSICIONES_Y][NUMERO_POSICIONES_X] =
{
{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
};
void escritura()
{

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int f = 0;
    int g = 0;
    int h = 0;
    int n = 0;
    int r = 0;
    int s = 0;

    s = analogRead(SENSOR_HOJA);
    if (s >= 2000)
    {
        MOVIMIENTO_EJEY(SACAR_HOJA);
        Serial.println("HOJA MAL PUESTA");
    }
    else
    {
        r = MOVIMIENTO_EJEY(ENTRAR_HOJA);
        if (r == 0)
        {
            MOVIMIENTO_EJEY(MARGEN_TOP_DOWN);
            for (int i1 = 0; i1 < NUMERO_POSICIONES_Y; i1++)
            {
                d++;
                g++;


                for (int i = 0; i < NUMERO_POSICIONES_X; i++)
                {

                    if (matriz[i1][i] == 0)
                    {
                        b++;
                    }
                    else
                    {
                        n = 1;
                    }
                }
                if (b == NUMERO_POSICIONES_X)
                {
                    f = 0;
                }
                else
                {
                    f = 1;
                }
                b = 0;
                switch (f)
                {
                case 0:
                    Serial.println("         RENGLON SIN NADA");
                    g++;
                    c++;
                    d++;
                    break;
                case 1:

                    if (g % 2 == 0) //SI ES PAR VA PARA LA DERECHA
                    {
                        //SE SETEA LA DIRECION DE LA IMPRESION
                        Serial.println("direcion:IZQUIERDA");
                        //DISTANCIA DE MARGEN DE LA HOJA
                        EJEX_POSICION_ENCODER_SETPOINT = DISTANCIA_MARGEN_IZQ;
                        MOVER(DISTANCIA_MARGEN* -1);
                        MOVIMIENTO_EJEX();
                        Serial.println("margen");

                        for (int i = NUMERO_POSICIONES_X; i > 0; i--)
                        {
                            if (matriz[c][i] == 1)
                            {
                                //SE ACTIVA EL SOLENOIDE
                                Serial.println("punto");
                                punto();
                                a++;
                                delay(250);
                            }
                            else
                            {
                                //NO ACTIVAR
                                Serial.println("espacio");
                                a++;
                            }
                            if (a == 1)
                            {
                                MOVER(DISTANCIA_LETRA * -1);
                                MOVIMIENTO_EJEX();
                                Serial.println("movimiento 2.5");
                                //SE MUEVE 2.54 mm EN EL EJE X
                            }
                            if (a == 2)
                            {
                                MOVER(DISTANCIA_LyL * -1);
                                MOVIMIENTO_EJEX();
                                Serial.println("movimineto 3.5");
                                //SE MUEVE 3.75 mm EN EL EJE X
                                a = 0;
                            }
                            if (i == 1)
                            {
                                
                                MOVIMIENTO_EJEY(ESPA_LINEA);
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
                        //SE SETEA LA DIRECION DE LA IMPRESION
                        Serial.println("direcion:DERECHA");
                        //DISTANCIA DE MARGEN DE LA HOJA
                        EJEX_POSICION_ENCODER_SETPOINT = DISTANCIA_MARGEN_DER;
                        MOVER(DISTANCIA_MARGEN);
                        MOVIMIENTO_EJEX();
                        Serial.println("margen");

                        for (int i = 0; i < NUMERO_POSICIONES_X; i++)
                        {
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
                            }
                            if (a == 1)
                            {
                                MOVER(DISTANCIA_LETRA);
                                MOVIMIENTO_EJEX();
                                Serial.println("movimiento 2.5");
                                //SE MUEVE 2.54 mm EN EL EJE X
                            }
                            if (a == 2)
                            {
                                MOVER(DISTANCIA_LyL);
                                MOVIMIENTO_EJEX();
                                Serial.println("movimineto 3.5");
                                //SE MUEVE 3.75 mm EN EL EJE X
                                a = 0;
                            }
                            if (i == NUMERO_POSICIONES_X - 1)
                            {
                                
                                MOVIMIENTO_EJEY(ESPA_LINEA);
                                Serial.println("margen");
                                Serial.println("linea terminada");
                                //DISTANCIA DE MARGEN DE LA HOJA
                                //EN ESTE PUNTO SE TERMINO DE IMPRIMIR LA LINEA
                            }
                        }
                        c++;
                    }
                        
                    
                    if (d >= 3)
                    {
                        MOVIMIENTO_EJEY(ESPA_RENGLON);
                        Serial.println("RENGLON FINALIZADO");
                        //ACÁ IRIA EL MOVIMIETO DEL MOTOR PASO A PASO CON EL ESPACIADO QUE HAY ENTRE RENGLONES
                        d = 0;
                    }
                    break;
                }
            }
            EJEX_POSICION_ENCODER_SETPOINT = 10;
            MOVIMIENTO_EJEY(MARGEN_TOP_DOWN);
            MOVIMIENTO_EJEY(SACAR_HOJA);
            MOVIMIENTO_EJEX();
            Serial.println("IMPRECION FINALIZADA");
            //EN ESTE PUNTO TERMINO LA IMPRESION DE TODA LA HOJA
        }
    }
}