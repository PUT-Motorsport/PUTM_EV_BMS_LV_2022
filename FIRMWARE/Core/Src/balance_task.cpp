/*
 * balance_task.cpp
 *
 *  Created on: May 6, 2022
 *      Author: Maks
 */
#include <balance_task.hpp>

/*
 * Brief:	Finding the highest and the lowest cell voltage and index of the highest one
 * Param:	None
 * Retval:	min_cell_voltage, max_cell_voltage, max_cell_voltage_index
 */
void min_max_cell_voltage(uint16_t *min, uint16_t *max, uint8_t *index){
	for(unsigned int i = 1; i < NUMBER_OF_CELLS; i++)
	{
		if(min > data.voltages.cells[i])
		{
			min = data.voltages.cells[i];
		}
		if(max < data.voltages.cells[i])
		{
			max = data.voltages.cells[i];
			index = i;
		}
	}
}


/*
 * Brief:	If the index indicates the last cell because
			the last cell is next to cell already being discharged,
			the next cell to discharge has to be the first one.
			So generally it sets the array tail at the beginning.
 * Param:	index
 * Retval:	index
 */
int discharge_cells_tail(int *i){
	if(5 == i)
		return i = -1;
}

/**
 * Brief:	It sets cell to be discharged
 * Param:	Index
 * Retval:	None
 */
void set_discharge_cell(uint8_t *discharge_at_once, int *i){
	if(discharge_at_once < MAX_CELLS_DISCHARGE_AT_ONCE)
	{
		data.charging.cell_discharge[i] = true;
		discharge_at_once++;
		i++;	//impossible to discharge 2 cells next to each other
	}
	data.charging.discharge_activation = true;
	data.charging.discharge_tick_end = HAL_GetTick() + BALANCE_TIME;

	i=discharge_cells_tail(i);
}

/**
 * Brief:	It sets cell having the highest voltage to be discharged
 * Param:	Index
 * Retval:	None
 */
void set_discharge_cell_max(uint8_t *discharge_at_once, int *i, uint8_t *max_cell_voltage_index, bool *max_voltage_discharge_activation){
	max_voltage_discharge_activation = false;
	if(discharge_at_once < MAX_CELLS_DISCHARGE_AT_ONCE)
	{
		data.charging.cell_discharge[max_cell_voltage_index] = true;
		discharge_at_once++;
		i = max_cell_voltage_index + 1; //impossible to discharge 2 cells next to each other
	}

	data.charging.discharge_activation = true;
	data.charging.discharge_tick_end = HAL_GetTick() + BALANCE_TIME;

	i=discharge_cells_tail(i);
}

/**
 * Brief:	Control of cell discharges
 * Param:	None
 * Retval:	None
 */
void balance_control()
{
	uint8_t charged_cells = 0, nearly_charged_cells = 0, cell_overcharged = 0, max_cell_voltage_index = 0, discharge_at_once = 0;
	uint16_t min_cell_voltage = data.voltages.cells[0], max_cell_voltage = data.voltages.cells[0];
	bool max_voltage_discharge_activation= 0, max_voltage_discharge_activation_out_of_charge = 0;
	data.charging.charger_state = HAL_GPIO_ReadPin(INTERLOCK_GPIO_Port, INTERLOCK_Pin);

	min_max_cell_voltage(min_cell_voltage, max_cell_voltage, max_cell_voltage_index);


	for(unsigned int i = 0; i < NUMBER_OF_CELLS; i++)
	{
		if(max_cell_voltage > VOL_UP_OK || (max_cell_voltage - min_cell_voltage) > BALANCE_VALUE)
		{
			max_voltage_discharge_activation= true;
		}
		if(max_cell_voltage > VOL_UP_OK)
		{
			max_voltage_discharge_activation_out_of_charge = true;
		}
		if(data.voltages.cells[i] > VOL_UP_OK)
		{
			charged_cells++;
		}
		if(data.voltages.cells[i] > VOL_UP_NEARLY_OK)
		{
			nearly_charged_cells++;
		}
		if(data.voltages.cells[i] > VOL_UP_OVERCHARGE)
		{
			cell_overcharged++;
		}
	}

	//EFUSE switch off - battery full
	if(charged_cells >= 4 && fabsf(outputCurrent) < CHARGING_CUTOFF_CURRENT && nearly_charged_cells == 6)
	{
		HAL_GPIO_WritePin(EFUSE_GPIO_Port, EFUSE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_SET);
		soc.set_full_battery();

	}
	//EFUSE switch off - cell overcharged
	else if(cell_overcharged > 1)
	{
		HAL_GPIO_WritePin(EFUSE_GPIO_Port, EFUSE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_SET);
	}
	//EFUSE switch on
	else if(HAL_GPIO_ReadPin(EFUSE_GPIO_Port, EFUSE_Pin) == 0 && nearly_charged_cells < 6 && data.charging.discharge_activation == 0 && cell_overcharged == 0 && acuState == 0)
	{
		HAL_GPIO_WritePin(EFUSE_GPIO_Port, EFUSE_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_RESET);
	}


	//cell choice algorithm when charger is connected
	if(true == data.charging.charger_state) //charger is connected
	{
		HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_RESET);

		if(false == data.charging.discharge_activation)
		{
			for(int i = 0; i < NUMBER_OF_CELLS; i++)
			{
				//discharge activation for the cell with the highest voltage
				if(true == max_voltage_discharge_activation)
				{
					set_discharge_cell_max(discharge_at_once, i, max_cell_voltage_index, max_voltage_discharge_activation);
				}
				//discharge activation for the cells with maximum voltage level - 4.201V
				else if(data.voltages.cells[i] > VOL_UP_OK)
				{
					set_discharge_cell(discharge_at_once, i);
				}
				//discharge activation for rest cells if needed
				else if((data.voltages.cells[i] - min_cell_voltage) > BALANCE_VALUE)
				{
					set_discharge_cell(discharge_at_once, i);
				}
				else
					data.charging.cell_discharge[i] = 0;
			}
		}
	}
	else //charger is disconnected
	{
		HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_SET);

		//balance if the cell voltages are overcharged
		if(false == data.charging.discharge_activation)
		{
			for(int i = 0; i < NUMBER_OF_CELLS; i++)
			{
				//discharge activation for the cell with the highest voltage
				if(true == max_voltage_discharge_activation_out_of_charge)
				{
					set_discharge_cell_max(discharge_at_once, i, max_cell_voltage_index, max_voltage_discharge_activation_out_of_charge);
				}
				//discharge activation for the cells with maximum voltage level - 4.201V
				else if(data.voltages.cells[i] > VOL_UP_OK)
				{
					set_discharge_cell(discharge_at_once, i);
				}
				else
					data.charging.cell_discharge[i] = 0;
			}
		}
	}
}

/**
 * Brief:	Activation and deactivation of balance
 * Param:	None
 * Retval:	None
 */
void balance_activation_deactivation()
{
	if(true == data.charging.discharge_activation)
	{
		for(int i = 0; i < NUMBER_OF_CELLS ; i++)
		{
			if(true == data.charging.cell_discharge[i])
			{
				LTC_turn_on_discharge(i, data.charging.cell_discharge);
			}
		}

	}
	else if(data.charging.discharge_tick_end <= HAL_GetTick())
	{
		data.charging.discharge_activation = 0;
		LTC_turn_off_discharge();
		osDelay(1000);
	}
}

void start_balance_function(void *argument){
	for(;;){
		balance_control();
		balance_activation_deactivation();
	}
}



