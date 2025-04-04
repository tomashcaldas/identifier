//Tomas Haddad Caldas
//identifier.c -- comissions calculator


#include <stdio.h>

float CalcularComissao(int* vendas) {
    int total_pas = 0;
    int total_regadores = 0;
    int total_vasos = 0;
    
    // Processar cada conjunto de vendas
    for (int i = 0; ; i += 3) {
        // Verificar se é o marcador de fim de mês
        if (vendas[i] == -1) {
            break;
        }
        
        int pas = vendas[i];
        int regadores = vendas[i+1];
        int vasos = vendas[i+2];
        
        // Validar quantidades
        if (pas < 1 || pas > 70) {
            return -1.0f;
        }
        if (regadores < 1 || regadores > 80) {
            return -2.0f;
        }
        if (vasos < 1 || vasos > 90) {
            return -3.0f;
        }
        
        // Acumular totais
        total_pas += pas;
        total_regadores += regadores;
        total_vasos += vasos;
    }
    
    // Verificar se vendeu pelo menos uma unidade de cada produto
    if (total_pas == 0 || total_regadores == 0 || total_vasos == 0) {
        // Pode retornar um código de erro específico ou considerar inválido
        // Como o enunciado diz que precisa vender pelo menos 1 de cada,
        // mas não especifica o código de erro, vou considerar como erro de pás
        return -1.0f;
    }
    
    // Calcular valor total das vendas
    float valor_total = total_pas * 45.0f + total_regadores * 30.0f + total_vasos * 25.0f;
    
    // Calcular comissão por faixas
    float comissao = 0.0f;
    
    if (valor_total <= 1000.0f) {
        comissao = valor_total * 0.10f;
    } else if (valor_total <= 1800.0f) {
        comissao = 1000.0f * 0.10f + (valor_total - 1000.0f) * 0.15f;
    } else {
        comissao = 1000.0f * 0.10f + 800.0f * 0.15f + (valor_total - 1800.0f) * 0.20f;
    }
    
    return comissao;
}

// Função para testar o programa (não faz parte da especificação)
int main() {
    // Exemplo de uso:
    int vendas_mes[] = {
        5, 3, 4,    // 1ª cidade: 5 pás, 3 regadores, 4 vasos
        10, 8, 12,  // 2ª cidade: 10 pás, 8 regadores, 12 vasos
        -1, 0, 0     // Fim do mês
    };
    
    float comissao = CalcularComissao(vendas_mes);
    
    if (comissao >= 0) {
        printf("Comissão do vendedor: R$ %.2f\n", comissao);
    } else {
        printf("Erro no cálculo da comissão: ");
        if (comissao == -1.0f) printf("Quantidade de pás inválida\n");
        else if (comissao == -2.0f) printf("Quantidade de regadores inválida\n");
        else if (comissao == -3.0f) printf("Quantidade de vasos inválida\n");
    }
    
    return 0;
}
