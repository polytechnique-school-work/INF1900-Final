#include "Writer.hpp"
unsigned char Writer::receiveUSART() {
    /* Wait for data to be received */
    while (!(UCSRnA & (1 << RXCn)))
        ;
    /* Get and return received data from buffer */
    return UDRn;

    /*
     *  Est-ce qu'on doit supprimer le bit de fin? Est-ce qu'on a un bit de fin?
     */

    // unsigned char status, resh, resl;
    // /* Wait for data to be received */
    // while ( !(UCSRnA & (1<<RXCn)) )
    // ;
    // /* Get status and 9th bit, then data */
    // /* from buffer */
    // status = UCSRnA;
    // resh = UCSRnB;
    // resl = UDRn;
    // /* If error, return -1 */
    // if ( status & (1<<FEn)|(1<<DORn)|(1<<UPEn) )
    // return -1;
    // /* Filter the 9th bit, then return */
    // resh = (resh >> 1) & 0x01;
    // return ((resh << 8) | resl);
}