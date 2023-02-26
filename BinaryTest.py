binaire = 0b11111111

PORTA0 = 0b00
PORTA1 = 0b01

#binaire |= (1 << 0) | (1 << 4)

binaire &= ~((1 << PORTA0) | (1 << PORTA1))
 
print("{0:b}".format(binaire))