#include "soc_ekf.h"
#include <math.h>
#include <algorithm>

void SoC_EKF::set_update_matrix()
{
    _State_vector[ttc1] = 0;
    _State_vector[ttc2] = 0;

    _et1 = expf(-_Ts / _battery.battery_equivalent_model[ttc1]);
    _et2 = expf(-_Ts / _battery.battery_equivalent_model[ttc2]);

    _A_matrix[SoC] = 1;
    _A_matrix[ttc1] = _et1;
    _A_matrix[ttc2] = _et2;

    _B_matrix[SoC] = - _Ts/_battery.battery_equivalent_model[Qnom]/60/60
            /_battery.cell_in_parallel;

    _B_matrix[ttc1] = _battery.battery_equivalent_model[Rttc1]*(1 - _et1);
    _B_matrix[ttc2] = _battery.battery_equivalent_model[Rttc2]*(1 - _et2);

    _P_matrix[SoC] = 0.005;
    _P_matrix[ttc1] = 0.1;
    _P_matrix[ttc2] = 0.1;

    _Q_matrix[SoC] = default_Q_value;
    _Q_matrix[ttc1] = _P_matrix[ttc1];
    _Q_matrix[ttc2] = _P_matrix[ttc2];

    _R_coeff = default_R_value;
}

void SoC_EKF::set_filter_covariance(float R, float Q_soc, float Q_v1, float Q_v2)
{
    _R_coeff = R;
    _Q_matrix[SoC] = Q_soc;
    _Q_matrix[Vttc1] = Q_v1;
    _Q_matrix[Vttc2] = Q_v2;
}

void SoC_EKF::update(const float &Current, const float &Voltage)
{

//    if(Current <= -0.3){ // charge
//        set_filter_covariance(default_R_value*charge_R_value_multiplier, default_Q_value);
//    }
//    else {
//        set_filter_covariance(default_R_value, default_Q_value);
//    }
    // Predict
    _State_vector[SoC] =  _State_vector[SoC] * _A_matrix[SoC] + Current * _B_matrix[SoC];
    _State_vector[ttc1] =  _State_vector[ttc1] * _A_matrix[ttc1] + Current * _B_matrix[ttc1];
    _State_vector[ttc2] =  _State_vector[ttc2] * _A_matrix[ttc2] + Current * _B_matrix[ttc2];

    // Covariance matrix
    _P_matrix[SoC] =  _A_matrix[SoC]  * _A_matrix[SoC] *  _P_matrix[SoC]  + _Q_matrix[SoC];
    _P_matrix[ttc1] = _A_matrix[ttc1] * _A_matrix[ttc1] * _P_matrix[ttc1] + _Q_matrix[ttc1];
    _P_matrix[ttc2] = _A_matrix[ttc2] * _A_matrix[ttc2] * _P_matrix[ttc2] + _Q_matrix[ttc2];

    // Predict Opec circiut voltage single call voltage based on SoC
    float Voltage_predict_OCV = horner(_battery.battery_ocv_poli, SOC_OCV_poli_coeff_lenght, &_State_vector[SoC]);

    float Voltage_predict = Voltage_predict_OCV - _State_vector[Vttc1]/_battery.cell_in_parallel
            - _State_vector[Vttc2]/_battery.cell_in_parallel
            - (Current) * _battery.battery_equivalent_model[Rs]
                        *_battery.cell_in_series
                        /_battery.cell_in_parallel; // for multiple cell voltage

    float innovation = (Voltage) - Voltage_predict;

    float H = horner(_battery.battery_d_ocv_poli, SOC_OCV_poli_coeff_lenght - 1, &_State_vector[SoC]);

    float S = H *  _P_matrix[SoC] * H + _R_coeff;

    float Kf = _P_matrix[SoC] * H * (1/S);

    _State_vector[SoC] += Kf*innovation;

    _P_matrix[SoC] = (1 - Kf*H) * _P_matrix[SoC];

    // to ensure that (0.0 <= SoC <= 1.0)
    _State_vector[SoC] = std::clamp(_State_vector[SoC], 0.00f, 1.00f);
}

void SoC_EKF::update_SoC_based_on_voltage(const float &Voltage)
{
    // set low observation noice covariance to calculate faster voltage soc prediction

    set_time_sampling(100.0f);
    set_update_matrix();
    set_filter_covariance(1);

    for(int i=0; i < 10e3; ++i){
        update(0, Voltage);
    }

    set_filter_covariance();
    set_time_sampling(0.05f);
    set_update_matrix();
}

void SoC_EKF::set_single_cell_equivalent_model(const float *battery_model){
    std::copy(battery_model, battery_model+6, _battery.battery_equivalent_model);
};

void SoC_EKF::set_initial_SoC(float aSoC){
    _State_vector[SoC] = aSoC;
}

void SoC_EKF::set_full_battery()
{
    _State_vector[SoC] = 1.00f;
};

void SoC_EKF::set_time_sampling(float Ts){
    _Ts = Ts;
};

void SoC_EKF::set_battery_configuration(unsigned int &&s, unsigned int &&p){
    _battery.cell_in_parallel = p;
    _battery.cell_in_series = s;
};

void SoC_EKF::set_single_cell_ocv_polinomial(const float *battery_ocv, unsigned int number_of_coef){

    std::copy(battery_ocv, battery_ocv + number_of_coef, _battery.battery_ocv_poli);

    for(unsigned int ocv_poly_iter = 0; ocv_poly_iter < number_of_coef - 1; ocv_poly_iter++){
        _battery.battery_d_ocv_poli[ocv_poly_iter] = static_cast<float>(number_of_coef - ocv_poly_iter - 1) * battery_ocv[ocv_poly_iter];
    }
};

void debug_display(){
    //    std::cout<<"Voltage "<< _battery.cell_in_parallel <<std::endl;
    //    std::cout<<"innowation: "<<innovation<<std::endl;
    //    std::cout<<"H: "<<H<<std::endl;
    //    std::cout<<"S: "<<S<<std::endl;
    //    std::cout<<"Kf: "<<Kf <<std::endl;
    //    std::cout<<"SoC: "<<State_vector[0]<<std::endl;
}

[[nodiscard]] float horner(const float *arry, unsigned int n, const float *x)
{
    float s = 0;
    for(unsigned int i = 0; i < n ; i++){
        s = s*(*x) + arry[i];
    }
    return s;
}
