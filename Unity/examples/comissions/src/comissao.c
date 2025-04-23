#include <stdio.h>                    //1
#include "comissao.h"

float CalcularComissao(int* vendas) { 
    if (vendas == NULL) {             //2  
        return -1.0f;                 //3
    }
    int total_pas = 0;                //4
    int total_regadores = 0;
    int total_vasos = 0;
    
    // Add safety limit (100 cities max)
    for (int i = 0; i < 300; i += 3) {  //4(até o int=0)   //5(i<300)   //15(loop)
        if (vendas[i] == -1) {          //6
            break;                      //7
        }
        int pas = vendas[i];            //8
        int regadores = vendas[i+1];
        int vasos = vendas[i+2];
        
        // Validate quantities
        if (pas < 1 || pas > 70) {      //9
            return -1.0f; }             //10
        if (regadores < 1 || regadores > 80) {  //11
            return -2.0f; }                 //12
        if (vasos < 1 || vasos > 90) {      //13
            return -3.0f; }                 //14
        
        total_pas += pas;                  //15
        total_regadores += regadores;
        total_vasos += vasos;
    }
    
    // Verify at least one of each was sold
    if (total_pas == 0 || total_regadores == 0 || total_vasos == 0) {   //16
        return -1.0f;                                                   //17
    }
    
    float valor_total = total_pas * 45.0f + total_regadores * 30.0f + total_vasos * 25.0f;      //18
    
    // progressive commission calculation:
    float comissao = 0.0f;
    float remaining = valor_total;
    
    // First 1000 at 10%
    if (remaining > 1000.0f) {          //19
        comissao += 1000.0f * 0.10f;    //20
        remaining -= 1000.0f;
    } else {                            //21
        comissao += remaining * 0.10f;  
        remaining = 0;
    }
    
    // Next 800 at 15%
    if (remaining > 800.0f) {           //22
        comissao += 800.0f * 0.15f;     //23
        remaining -= 800.0f;
    } else if (remaining > 0) {         //24
        comissao += remaining * 0.15f;  //25
        remaining = 0;
    }
    
    // Anything above 1800 at 20%
    if (remaining > 0) {                //26
        comissao += remaining * 0.20f;  //27
    }
    
    return comissao;        //28
}