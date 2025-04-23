#include "unity.h"
#include "comissao.h"

void setUp(void) {}
void tearDown(void) {}

// =============================================
// EQUIVALENCE CLASSES & BOUNDARY VALUE ANALYSIS
// =============================================
/*
 * classes de equivalencia:
 * 
 * 1. Valid inputs:
 *    - Pás: >0 or <=70
 *    - Regadores: >0 or <=80 
 *    - Vasos: >0 or <=90
 *    - Must have at least one of each
 *    - Must end with -1 marker
 *
 * 2. Invalid inputs:
 *    - Pás: <=0 or >70 → return -1
 *    - Regadores: <=0 or >80 → return -2  
 *    - Vasos: <=0 or >90 → return -3
 *    - Missing -1 marker → buffer overflow
 *    - NULL pointer → return -1
 */

// =============================================
// BOUNDARY VALUE TESTS (Valid boundaries)
// =============================================

void test_min_valid_values(void) {
    int vendas[] = {1, 1, 1, -1, 0, 0}; // Lower bounds
    TEST_ASSERT_TRUE(CalcularComissao(vendas) > 0);
}

void test_max_valid_values(void) {
    int vendas[] = {70, 80, 90, -1, 0, 0}; // Upper bounds
    TEST_ASSERT_TRUE(CalcularComissao(vendas) > 0);
}

// =============================================
// CLASSES DE EQUIVALENCIA TESTS (Invalid inputs)
// =============================================

// EC1: Invalid pás
void test_pas_zero(void) {
    int vendas[] = {0, 1, 1, -1, 0, 0}; // Lower invalid
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, CalcularComissao(vendas));
}

void test_pas_exceed_max(void) {
    int vendas[] = {71, 1, 1, -1, 0, 0}; // Upper invalid
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, CalcularComissao(vendas));
}

// EC2: Invalid regadores  
void test_regadores_zero(void) {
    int vendas[] = {1, 0, 1, -1, 0, 0};
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, CalcularComissao(vendas));
}

void test_regadores_exceed_max(void) {
    int vendas[] = {1, 81, 1, -1, 0, 0};
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, CalcularComissao(vendas));
}

// EC3: Invalid vasos
void test_vasos_zero(void) {
    int vendas[] = {1, 1, 0, -1, 0, 0};
    TEST_ASSERT_EQUAL_FLOAT(-3.0f, CalcularComissao(vendas));
}

void test_vasos_exceed_max(void) {
    int vendas[] = {1, 1, 91, -1, 0, 0};
    TEST_ASSERT_EQUAL_FLOAT(-3.0f, CalcularComissao(vendas));
}

// EC4: Missing product type
void test_missing_pas(void) {
    int vendas[] = {0, 1, 1, -1, 0, 0}; // Also covers EC1
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, CalcularComissao(vendas));
}

void test_missing_regadores(void) {
    int vendas[] = {1, 0, 1, -1, 0, 0}; // Also covers EC2
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, CalcularComissao(vendas));
}

void test_missing_vasos(void) {
    int vendas[] = {1, 1, 0, -1, 0, 0}; // Also covers EC3
    TEST_ASSERT_EQUAL_FLOAT(-3.0f, CalcularComissao(vendas));
}

// =============================================
// CALCULO DE COMISSAO CALSSES DE EQUIVALENCIA
// =============================================
/*
 * Commission tiers:
 * EC5: <= 1000 → 10%
 * EC6: 1001-1800 → 10% first 1000 + 15% remainder
 * EC7: >1800 → 10% first 1000 + 15% next 800 + 20% remainder
 */

// EC5: Low commission tier
void test_commission_tier1(void) {
    int vendas[] = {10, 10, 10, -1, 0, 0}; // Exatamente 1000 (10*45 + 10*30 + 10*25)
    TEST_ASSERT_EQUAL_FLOAT(100.0f, CalcularComissao(vendas));
}

// EC6: Middle commission tier 
void test_commission_tier2(void) {
    int vendas[] = {15, 15, 15, -1, 0, 0}; // 1500 total (100 + 500*0.15)
    TEST_ASSERT_EQUAL_FLOAT(185.0f, CalcularComissao(vendas));
}

// EC7: High commission tier
void test_commission_tier3(void) {
    int vendas[] = {20, 20, 20, -1, 0, 0}; // 2000 total (100 + 120 + 40)
    TEST_ASSERT_EQUAL_FLOAT(260.0f, CalcularComissao(vendas));
}

// =============================================
// SPECIAL CASES
// =============================================

void test_null_input(void) {
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, CalcularComissao(NULL));
}

void test_empty_sales(void) {
    int vendas[] = {-1, 0, 0};
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, CalcularComissao(vendas));
}

void test_multiple_cities(void) {
    int vendas[] = {5,5,5, 10,10,10, -1,0,0}; // Mixed values
    float expected = 175.0f;
    TEST_ASSERT_EQUAL_FLOAT(expected, CalcularComissao(vendas));
}

// =============================================
// TEST RUNNER
// =============================================

int main(void) {
    UNITY_BEGIN();
    
    // Boundary values
    RUN_TEST(test_min_valid_values);
    RUN_TEST(test_max_valid_values);
    
    // Invalid input classes
    RUN_TEST(test_pas_zero);
    RUN_TEST(test_pas_exceed_max);
    RUN_TEST(test_regadores_zero);
    RUN_TEST(test_regadores_exceed_max); 
    RUN_TEST(test_vasos_zero);
    RUN_TEST(test_vasos_exceed_max);
    RUN_TEST(test_missing_pas);
    RUN_TEST(test_missing_regadores);
    RUN_TEST(test_missing_vasos);
    
    // Commission tiers
    RUN_TEST(test_commission_tier1); //até 1000
    RUN_TEST(test_commission_tier2); //1001 até 1800
    RUN_TEST(test_commission_tier3); //acima de 1800
    
    // Special cases
    RUN_TEST(test_null_input);
    RUN_TEST(test_empty_sales);
    RUN_TEST(test_multiple_cities);
    
    return UNITY_END();
}