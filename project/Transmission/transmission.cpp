#iclude "transmission.hpp"


LightManager lm(&DDRA, &PORTA, PORTA0, PORTA1); 

void RoutineTransmission::flashGreen()
{
    while(true)
    {
        lm.setLight(COLOR::GREEN);
        _delay_ms(250); // doit etre 10 Hz
        lm.setLight(COLOR::OFF);
        _delay_ms(250); 
    }
}

void RoutineTransmission::ExecuteRoutine()
{
    TransmissionSteps transmissionSteps; 
    
}