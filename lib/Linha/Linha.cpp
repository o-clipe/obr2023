/*Algoritimo para o robo seguir a linha - Codigo*/

#include "Arduino.h"
#include "Linha.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"

#define Padrao 0
#define None 1
#define Inicio 2
#define LinhaaEsquerda 10
#define NoventaEsquerda 11
#define LinhaaDireita 20
#define NoventaDireita 21
#define SemLinha 30
#define SemiParaleloaLinha 40
#define ParaleloaLinha 41


Linha::Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj): _lum(lum_obj), _carro(motor_obj), _giros(giros_obj) // Constructor
{
    status = Inicio;
    _loopBool = true;
    _paralelarBest = 0;
    _paralelarLadoDone = false;
    _paralelarBestAssigned = false;
}


void Linha::setup() // Chamado no Setup()
{

}


void Linha::run() // Comandos de rotina
{
  segueLinha();
}


uint8_t Linha::checkState(uint16_t sensorsPosition[5])
{
    uint16_t ee = _lum.normalizeSensEntry(0, sensorsPosition[0]);
    uint16_t e = _lum.normalizeSensEntry(1, sensorsPosition[1]);
    uint16_t m = _lum.normalizeSensEntry(2, sensorsPosition[2]);
    uint16_t d = _lum.normalizeSensEntry(3, sensorsPosition[3]);
    uint16_t dd = _lum.normalizeSensEntry(4, sensorsPosition[4]);

    Serial.print((String)ee + " " + (String)e + " " + (String)m + " " + (String)d + " " + (String)dd + ": ");

    if (ee < e && e < m && m > d && d > dd) return Padrao;
    if (e >= m && m > d && d >= dd) return LinhaaEsquerda;
    if (ee <= e && e < m && m <= d) return LinhaaDireita;
    if (ee == 0 && e == 0 && m == 0 && d == 0 && dd == 0) return SemLinha;
    if (ee > OUTPUTRANGE/10 && e > OUTPUTRANGE/10 && m > OUTPUTRANGE/10 && d > OUTPUTRANGE/10 && dd > OUTPUTRANGE/10) return ParaleloaLinha;
    if (ee > 0 && e > 0 && m > 0 && d > 0 && dd > 0) return SemiParaleloaLinha;

    return None;
}


void Linha::pararSeOutroStatus(uint8_t f_status)
{
    if (f_status != status)
    {
        _carro.parar();
    }
}


bool Linha::segueLinha()
{
    uint8_t status = checkState(_lum.processedLastMem());
    if (status == Padrao)
    {
        _carro.ligarReto();
    }
    if (status == LinhaaEsquerda)
    {
        pararSeOutroStatus(LinhaaEsquerda);
        _carro.ligarMotor("e", VELOCIDADEDECURVA);
    }
    if (status == LinhaaDireita)
    {
        pararSeOutroStatus(LinhaaDireita);
        _carro.ligarMotor("d", VELOCIDADEDECURVA);
    }
    else
    {
        return false;
    }
    return true;
}


bool Linha::girar90Graus(char l)
{
    char op;
    if (l == 'e'){op='l';}else{op='e';}

    if (_loopBool)
    {
    float* xyzRef = _giros.girosRead();
    _startGirosPos[0] = xyzRef[0];
    _startGirosPos[1] = xyzRef[1];
    _startGirosPos[2] = xyzRef[2];
    _carro.ligarMotor((String)l+"r", VELOCIDADEDECURVA/2);
    _carro.ligarMotor((String)op, VELOCIDADEDECURVA/2);
    _loopBool = false;
    }
    else
    {
        float* xyzRef = _giros.girosRead();
        if (fmod((xyzRef[2]-90), 180) < _giros.variacaoPadrao[2]*1.5) // Possivel BUG, caso o robo gire muito rapido
        {
            _carro.parar();
            _loopBool = true;
            return false;
        }
    }
    return true;
}


bool Linha::paralelar()  // necessario espaco, bastante
{
    uint8_t status = checkState(_lum.processedLastMem());
    if (_loopBool)
    {
        _paralelarLadoDone = false;
        if (status == LinhaaEsquerda)
        {
            _paralelarLado = 'e';
        }
        if (status == LinhaaDireita)
        {
            _paralelarLado = 'd';
        }
        _loopBool = false;
        return true;
    }
    // if (status == ParaleloaLinha)
    // {
    //     _loopBool = true;
    //     return false;
    // }
    if (_paralelarLado == 'e')
    {
        if(!_paralelarLadoDone)
        {
            if(_paralelarLadoE())
            {
                return true;
            }
            _paralelarLadoDone = true;
        }
        if (_paralelarLadoD()){return true;}else{_loopBool = true; return false;}
    }
    if (_paralelarLado == 'd')
    {
        if(!_paralelarLadoDone)
        {
            if(_paralelarLadoD())
            {
                return true;
            }
            _paralelarLadoDone = true;
        }
        if (_paralelarLadoE()){return true;}else{_loopBool = true; return false;} 
    }
}


bool Linha::_paralelarLadoE()
{
    if(_lum.processedlastMemOutput[0] > _paralelarBest)
    {
        _paralelarBest = _lum.processedlastMemOutput[0];
        _carro.ligarMotor("e", VELOCIDADEDECURVA/2);
        return true;
    }
    if(_lum.processedlastMemOutput[0] < _paralelarBest)
    {
        _carro.ligarMotor("er", VELOCIDADEDECURVA/2);
        _paralelarBestAssigned = true;
        return true;
    }
    if(_lum.processedlastMemOutput[0] == _paralelarBest && _paralelarBestAssigned)
    {
        _carro.parar();
        _paralelarBestAssigned = false;
        _paralelarBest = 0;
        return false;
    }
}


bool Linha::_paralelarLadoD()
{
    if(_lum.processedlastMemOutput[4] < _paralelarBest)
    {
        _paralelarBest = _lum.processedlastMemOutput[0];
        _carro.ligarMotor("d", VELOCIDADEDECURVA/2);
        return true;
    }
    if(_lum.processedlastMemOutput[4] > _paralelarBest)
    {
        _carro.ligarMotor("dr", VELOCIDADEDECURVA/2);
        _paralelarBestAssigned = true;
        return true;
    }
    if(_lum.processedlastMemOutput[4] == _paralelarBest && _paralelarBestAssigned)
    {
        _carro.parar();
        _paralelarBestAssigned = false;
        _paralelarBest = 0;
        return false;
    }
}


bool Linha::alignInPlace()
{
    uint8_t status = checkState(_lum.processedLastMem());
    if (status != Padrao)
    {
        if (_loopBool)
        {
            
        }
    }
}


bool Linha::gap()
{
    uint8_t status = checkState(_lum.processedLastMem());
    if (status == SemLinha){
        return true;
    }
}


 