/*Algoritimo para o robo seguir a linha - Codigo*/

#include "Arduino.h"
#include "Linha.h"
#include "Lum.h"
#include "Motor.h"
#include "Giros.h"

#define None 1
#define Inicio 2
#define Padrao 10
#define PerfeitamenteNaLinha 11
#define LinhaaEsquerda 20
#define NoventaEsquerda 21
#define LinhaaDireita 30
#define NoventaDireita 31
#define SemLinha 40
#define SemiParaleloaLinha 50
#define ParaleloaLinha 51


Linha::Linha(Lum& lum_obj, Motor& motor_obj, Giros& giros_obj): _lum(lum_obj), _carro(motor_obj), _giros(giros_obj) // Constructor
{
    status = Inicio;
    _boolLoop = true;
    _paralelarBest = 0;
    _paralelarLadoDone = false;
    _paralelarBestAssigned = false;
    _paralelarLoop = true;
    _trialAndErrorTime = 0;
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

    if (ee==_perfeitamenteNaLinha[0] && e==_perfeitamenteNaLinha[1] && m==_perfeitamenteNaLinha[2] && d==_perfeitamenteNaLinha[3] && d==_perfeitamenteNaLinha[4]) return PerfeitamenteNaLinha;
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

}


bool Linha::_simples()
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

    if (_boolLoop)
    {
    float* xyzRef = _giros.girosRead();
    _startGirosPos[0] = xyzRef[0];
    _startGirosPos[1] = xyzRef[1];
    _startGirosPos[2] = xyzRef[2];
    _carro.ligarMotor((String)l+"r", VELOCIDADEDECURVA/2);
    _carro.ligarMotor((String)op, VELOCIDADEDECURVA/2);
    _boolLoop = false;
    }
    else
    {
        float* xyzRef = _giros.girosRead();
        if (fmod((xyzRef[2]-90), 180) < _giros.variacaoPadrao[2]*1.5) // Possivel BUG, caso o robo gire muito rapido
        {
            _carro.parar();
            _boolLoop = true;
            return false;
        }
    }
    return true;
}


bool Linha::paralelar()  // necessario espaco, bastante
{
    uint8_t status = checkState(_lum.processedLastMem());
    if (_paralelarLoop)
    {
        _paralelarLadoDone = false;
        if (status/10*10 == LinhaaEsquerda)
        {
            _paralelarLado = 'e';
        }
        if (status/10*10 == LinhaaDireita)
        {
            _paralelarLado = 'd';
        }
        _paralelarLoop = false;
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
        if (_paralelarLadoD()){return true;}else{if(girar90Graus('e')){return true;}else{_paralelarLoop=true;return false;};}
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
        if (_paralelarLadoE()){return true;}else{if(girar90Graus('d')){return true;}else{_paralelarLoop=true;return false;};} 
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
        _carro.ligarMotor("d", VELOCIDADEDECURVA);
        return true;
    }
    if(_lum.processedlastMemOutput[4] > _paralelarBest)
    {
        _carro.ligarMotor("dr", VELOCIDADEDECURVA);
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


bool Linha::micro()
{
    uint8_t status = checkState(_lum.processedLastMem());
    if (status == PerfeitamenteNaLinha)
    {
        _carro.parar();
        return false;
    }
    _paralelarLadoDone = false;
    if (status/10*10 == LinhaaEsquerda)
    {
    _carro.ligarMotor("er", VELOCIDADEDECURVA);
    _carro.ligarMotor("d", VELOCIDADEDECURVA);
    }
    if (status/10*10 == LinhaaDireita)
    {
    _carro.ligarMotor("dr", VELOCIDADEDECURVA);
    _carro.ligarMotor("e", VELOCIDADEDECURVA);
    }
    return true;
}


bool Linha::smoothCurve()
{
    uint8_t status = checkState(_lum.processedLastMem());
    if (status != Padrao)
    {
        if (_boolLoop)
        {
            
        }
    }
}


bool Linha::trialAndErrorCurve()
{
    unsigned long time = millis();
    uint8_t status = checkState(_lum.processedLastMem());

    if (time/MILLISTEP == _trialAndErrorTime/MILLISTEP)
    {
        return true;  //Evitar isso pelo amor de Deus.
    }
    if (status/10*10 == Padrao)
    {
        _boolLoop=true;
        return false;
    }
    _trialAndErrorTime = time;
    if (_boolLoop)
    {
        _boolLoop = false;
        return _simples();
    }
    else
    {
        _boolLoop = true;
        _carro.ligarRe(VELOCIDADEDECURVA);
        return true;
    }

}


bool Linha::gap()
{
    uint8_t status = checkState(_lum.processedLastMem());
    if (status == SemLinha){
        return true;
    }
}

void Linha::definePerfeitamenteNaLinha()
{
    uint16_t* r = _lum.processedReadAll();
    _perfeitamenteNaLinha[0] = r[0];
    _perfeitamenteNaLinha[1] = r[1];
    _perfeitamenteNaLinha[2] = r[2];
    _perfeitamenteNaLinha[3] = r[3];
    _perfeitamenteNaLinha[4] = r[4];
}


 