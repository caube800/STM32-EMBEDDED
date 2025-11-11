#ifndef INC_TM1637_H_
#define INC_TM1637_H_

void TM1637_WriteData (uint8_t Addr, uint8_t *data, int size);
void TM1637_WriteNum (uint8_t Addr, int num, int colon);
void TM1637_WriteTime (uint8_t *Time, int colon);

#endif /* INC_TM1637_H_ */
