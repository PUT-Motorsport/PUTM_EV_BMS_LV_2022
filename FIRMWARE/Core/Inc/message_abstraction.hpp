#ifndef MESSAGE_ABSTRACTION_H
#define MESSAGE_ABSTRACTION_H

#ifdef UNIT_TESTS
#include "../hal_can.hpp"
#else
#include "main.h"
#endif

#include <cstdint>
#include <cstring>

namespace PUTM_CAN {

static const std::size_t max_dlc_size = 8;

struct Can_rx_message {
  Can_rx_message(CAN_HandleTypeDef &hcan, uint32_t RxFifo) : header{}, data{0} {
    this->status =
        HAL_CAN_GetRxMessage(&hcan, RxFifo, &this->header, this->data);
  }

  CAN_RxHeaderTypeDef header;
  uint8_t data[max_dlc_size];
  HAL_StatusTypeDef status;
};

template <typename T> class Can_tx_message {
public:
  CAN_TxHeaderTypeDef header;
  uint8_t buff[max_dlc_size];

  constexpr Can_tx_message(const T &data,
                           const CAN_TxHeaderTypeDef &message_header)
      : header{message_header} {
    static_assert(std::is_trivially_constructible<T>(),
                  "Object must by C like struct");
    static_assert(std::is_class<T>(), "Object must by C like struct");
    static_assert(std::is_standard_layout<T>(), "Object must by C like struct");
    static_assert(std::is_trivially_copyable<T>(),
                  "Object must by C like struct");
    static_assert(sizeof(T) <= max_dlc_size,
                  "Object size must be less than 8bytes");
    std::memcpy(this->buff, &data, sizeof(T));
  }

  HAL_StatusTypeDef send(CAN_HandleTypeDef &hcan) {
    static uint32_t TxMailbox(0);
    return HAL_CAN_AddTxMessage(&hcan, &this->header, this->buff, &TxMailbox);
  }
};

class __attribute__((packed)) Device_base {
  const uint32_t IDE : 12; // using 11 bits identifier
  const uint8_t DLC : 4;   // max size for data is 8 `bytes`

protected:
  bool new_data : 1;

public:
  constexpr Device_base(uint32_t ide, uint8_t dlc)
      : IDE{ide}, DLC{dlc}, new_data{false} {}
  [[nodiscard]] constexpr uint32_t get_ID() { return IDE; }
  [[nodiscard]] constexpr uint8_t get_DLC() { return DLC; }
  virtual void set_data(const Can_rx_message &m) = 0;

  [[nodiscard]] constexpr bool get_new_data() {
    bool temporary = new_data;
    new_data = false;
    return temporary;
  }
};

template <typename Device_data_type>
class __attribute__((packed)) Device : public Device_base {
public:
  explicit constexpr Device(uint32_t ide)
      : Device_base(ide, sizeof(Device_data_type)){};

  Device_data_type data{};

  void set_data(const Can_rx_message &m) override {
    new_data = true;
    std::memcpy(&data, m.data, sizeof(Device_data_type));
  }
};

} // namespace PUTM_CAN

#endif
