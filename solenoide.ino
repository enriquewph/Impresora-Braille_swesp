int punto()
{
    digitalWrite(SOLENOIDE,1);
    delay(50);
    digitalWrite(SOLENOIDE,0);
    return(1);
}