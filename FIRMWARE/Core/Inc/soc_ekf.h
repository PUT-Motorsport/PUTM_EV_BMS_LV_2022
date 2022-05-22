#ifndef SOC_EKF_H
#define SOC_EKF_H

//#include <array>
#include <math.h>
const unsigned int SOC_OCV_poli_coeff_lenght = 9;

const float default_R_value = 500000; // observation noice covariance
const float charge_R_value_multiplier = 1e5;
const float default_Q_value = 0.0002; // proces noice covariance

enum batt{
    Rs,    // in Ohms
    ttc1,  // in second
    ttc2,  // in second
    Rttc1, // in Ohms
    Rttc2, // in Ohms
    Qnom   // nominal charge in Ah single cell
};


enum state_vector{
    SoC,
    Vttc1,
    Vttc2
};

float horner(const float *arry,unsigned int n, const float *x);

struct Battery_characteristic{
    unsigned int cell_in_parallel = 1;
    unsigned int cell_in_series = 1;
    float battery_equivalent_model[6];
    float battery_ocv_poli[SOC_OCV_poli_coeff_lenght];
    float battery_d_ocv_poli[SOC_OCV_poli_coeff_lenght];
};



class SoC_EKF
{
private:
    Battery_characteristic _battery;
    float _et1,_et2;
    float _Ts;

    float _A_matrix[3];
    float _B_matrix[3];
    float _P_matrix[3];
    float _R_coeff;
    float _Q_matrix[3];
    float _State_vector[3];
    

public:
    SoC_EKF() = default;

    /* Battery model represented in Two Time Constatant model */
    /*  { Rs[Ohms], ttc1[s], ttc2, Rttc1[Ohms], Rttc2, Qnominal[Ah]} */
    void set_single_cell_equivalent_model(const float *battery_model);
    
    /* Battery OCV curve represented by polynomial [0] -> highest order coeff */
    /* and calc derative of ocv polinomial  */
    void set_single_cell_ocv_polinomial(const float *battery_ocv, unsigned int number_of_coef);

    /* Define battery configuration in eg. 1s2p -> s = 1, p = 2 */
    void set_battery_configuration(unsigned int &&s, unsigned int &&p);

    /* For constant time sampling */
    void set_time_sampling(float Ts);

    void set_initial_SoC(float aSoC);

    void set_full_battery();
    
    void set_update_matrix();

    void set_filter_covariance(float R = default_R_value,
                               float Q_soc = default_Q_value,
                               float Q_v1 = 0.1,
                               float Q_v2 = 0.1);

    // positive current -> discharge
    // negative current -> charge
    void update(const float &Current, const float &Voltage);

    void update_SoC_based_on_voltage(const float &Voltage);
    
    [[nodiscard]] float get_SoC(){return _State_vector[SoC];};
};




#endif // SOC_EKF_H
