int punto()
{
    digitalWrite(SOLENOIDE,1);
    delay(25);
    digitalWrite(SOLENOIDE,0);
    return(1);
}