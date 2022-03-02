template <class T>
int EEPROM_writeAnything(int ee, const T &value)
{
    Serial.printf("Writing: %f\n", value);
    const byte *p = (const byte *)(const void *)&value;
    unsigned int i;
    EEPROM.begin(sizeof(value));
    for (i = 0; i < sizeof(value); i++)
    {
        Serial.printf("Writing: %d\n", *p);
        EEPROM.write(ee++, *p++);
    }
    EEPROM.commit();
    EEPROM.end();
    return i;
}

template <class T>
int EEPROM_readAnything(int ee, T &value)
{
    byte *p = (byte *)(void *)&value;
    unsigned int i;
    EEPROM.begin(sizeof(value));
    for (i = 0; i < sizeof(value); i++)
    {
        *p = EEPROM.read(ee++);
        Serial.printf("Read: %d\n", *p);
        p++;
    }
    Serial.printf("Read: %f\n", value);
    EEPROM.end();
    return i;
}