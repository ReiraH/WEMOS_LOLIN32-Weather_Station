/*!
 * @file Adafruit_ZeroPDM.h
 */
#ifndef ADAFRUIT_ZEROPDM_H
#define ADAFRUIT_ZEROPDM_H

#include <Arduino.h>

/// @cond DISABLE
#if defined(I2S)
/// @endcond DISABLE

// Uncomment to enable debug message output.
#define DEBUG //!< Enables or disables debug

#define DEBUG_PRINTER                                                          \
  Serial //!< Define where debug output is printed (the native USB port on the
         //!< Zero).

/*!
 * ZeroPDM driver
 */
class Adafruit_ZeroPDM {
public:
  /*!
   * @brief Create a new instance of an I2S audio transmitter.
   * Can specify the pins to use and the generic clock ID to use for driving the
   * I2S hardware (default is GCLK 3).
   * @param clockpin Clock pin
   * @param datapin Data pin
   * @param gclk Clock generator
   */
  Adafruit_ZeroPDM(int clockpin, int datapin, uint8_t gclk = 3);

  /*!
   * @brief Initialize the I2S audio  receiver.
   * @return Returns whether or not initialization was successful
   */
  bool begin();
  /*!
   * @brief Ends the connection
   */
  void end();

  /*!
   * @brief Configure the transmitter with the sample rate (in hertz)
   * @param sampleRateHz Sample rate (in hertz)
   * @param stereo Whether stereo is enabled
   * @return Returns whether or not configuration was successful
   */
  bool configure(uint32_t sampleRateHz, boolean stereo);

  /*!
   * @brief Read a single sample from the I2S subsystem.  Will wait until the
   * I2S hardware is ready to receive the sample.
   * @return Returns the data read over I2S
   */
  uint32_t read(void);

  /*!
   * @brief Gets the I2S serializer
   * @return Returns the I2S serializer
   */
  uint8_t getSerializer(void) { return _i2sserializer; };

  /*!
   * @brief Reads data from I2S buffer
   * @param buffer Buffer to read from
   * @param bufsiz Size of buffer
   * @return Returns the data read over I2S
   */
  bool read(uint32_t *buffer, int bufsiz);

private:
  uint8_t _gclk;
  int _clk, _data;
  uint32_t _clk_pin, _clk_mux, _data_pin, _data_mux;
  uint8_t _i2sserializer;
  uint8_t _i2sclock;

  I2s *_hw;
};

#ifndef I2S_H_INCLUDED

/**
 * Master Clock (MCK) source selection
 */
enum i2s_master_clock_source {
  /** Master Clock (MCK) is from general clock */
  I2S_MASTER_CLOCK_SOURCE_GCLK,
  /** Master Clock (MCK) is from MCK input pin */
  I2S_MASTER_CLOCK_SOURCE_MCKPIN
};

/**
 * Serial Clock (SCK) source selection
 */
enum i2s_serial_clock_source {
  /** Serial Clock (SCK) is divided from Master Clock */
  I2S_SERIAL_CLOCK_SOURCE_MCKDIV,
  /** Serial Clock (SCK) is input from SCK input pin */
  I2S_SERIAL_CLOCK_SOURCE_SCKPIN
};

/**
 * Data delay from Frame Sync (FS)
 */
enum i2s_data_delay {
  /** Left Justified (no delay) */
  I2S_DATA_DELAY_0,
  /** I2S data delay (1-bit delay) */
  I2S_DATA_DELAY_1,
  /** Left Justified (no delay) */
  I2S_DATA_DELAY_LEFT_JUSTIFIED = I2S_DATA_DELAY_0,
  /** I2S data delay (1-bit delay) */
  I2S_DATA_DELAY_I2S = I2S_DATA_DELAY_1
};

/**
 * Frame Sync (FS) source
 */
enum i2s_frame_sync_source {
  /** Frame Sync (FS) is divided from I2S Serial Clock */
  I2S_FRAME_SYNC_SOURCE_SCKDIV,
  /** Frame Sync (FS) is input from FS input pin */
  I2S_FRAME_SYNC_SOURCE_FSPIN
};

/**
 * Frame Sync (FS) output pulse width
 */
enum i2s_frame_sync_width {
  /** Frame Sync (FS) Pulse is 1 Slot width */
  I2S_FRAME_SYNC_WIDTH_SLOT,
  /** Frame Sync (FS) Pulse is half a Frame width */
  I2S_FRAME_SYNC_WIDTH_HALF_FRAME,
  /** Frame Sync (FS) Pulse is 1 Bit width */
  I2S_FRAME_SYNC_WIDTH_BIT,
  /** 1-bit wide Frame Sync (FS) per Data sample, only used when Data transfer
   *  is requested */
  I2S_FRAME_SYNC_WIDTH_BURST
};

/**
 * Time Slot Size in number of I2S serial clocks (bits)
 */
enum i2s_slot_size {
  /** 8-bit slot */
  I2S_SLOT_SIZE_8_BIT,
  /** 16-bit slot */
  I2S_SLOT_SIZE_16_BIT,
  /** 24-bit slot */
  I2S_SLOT_SIZE_24_BIT,
  /** 32-bit slot */
  I2S_SLOT_SIZE_32_BIT
};

/**
 * DMA channels usage for I2S
 */
enum i2s_dma_usage {
  /** Single DMA channel for all I2S channels */
  I2S_DMA_USE_SINGLE_CHANNEL_FOR_ALL,
  /** One DMA channel per data channel */
  I2S_DMA_USE_ONE_CHANNEL_PER_DATA_CHANNEL
};

/**
 * I2S data format, to extend mono data to 2 channels
 */
enum i2s_data_format {
  /** Normal mode, keep data to its right channel */
  I2S_DATA_FORMAT_STEREO,
  /** Assume input is mono data for left channel, the data is duplicated to
   *  right channel */
  I2S_DATA_FORMAT_MONO
};

/**
 * I2S data bit order
 */
enum i2s_bit_order {
  /** Transfer Data Most Significant Bit first (Default for I2S protocol) */
  I2S_BIT_ORDER_MSB_FIRST,
  /** Transfer Data Least Significant Bit first */
  I2S_BIT_ORDER_LSB_FIRST
};

/**
 * I2S data bit padding
 */
enum i2s_bit_padding {
  /** Padding with 0 */
  I2S_BIT_PADDING_0,
  /** Padding with 1 */
  I2S_BIT_PADDING_1,
  /** Padding with MSBit */
  I2S_BIT_PADDING_MSB,
  /** Padding with LSBit */
  I2S_BIT_PADDING_LSB,
};

/**
 * I2S data word adjust
 */
enum i2s_data_adjust {
  /** Data is right adjusted in word */
  I2S_DATA_ADJUST_RIGHT,
  /** Data is left adjusted in word */
  I2S_DATA_ADJUST_LEFT
};

/**
 * I2S data word size
 */
enum i2s_data_size {
  /** 32-bit */
  I2S_DATA_SIZE_32BIT,
  /** 24-bit */
  I2S_DATA_SIZE_24BIT,
  /** 20-bit */
  I2S_DATA_SIZE_20BIT,
  /** 18-bit */
  I2S_DATA_SIZE_18BIT,
  /** 16-bit */
  I2S_DATA_SIZE_16BIT,
  /** 16-bit compact stereo */
  I2S_DATA_SIZE_16BIT_COMPACT,
  /** 8-bit */
  I2S_DATA_SIZE_8BIT,
  /** 8-bit compact stereo */
  I2S_DATA_SIZE_8BIT_COMPACT
};

/**
 * I2S data slot adjust
 */
enum i2s_slot_adjust {
  /** Data is right adjusted in slot */
  I2S_SLOT_ADJUST_RIGHT,
  /** Data is left adjusted in slot */
  I2S_SLOT_ADJUST_LEFT
};

/**
 * I2S data padding
 */
enum i2s_data_padding {
  /** Padding 0 in case of under-run */
  I2S_DATA_PADDING_0,
  /** Padding last data in case of under-run */
  I2S_DATA_PADDING_SAME_AS_LAST,
  /** Padding last data in case of under-run
   *  (abbr. \c I2S_DATA_PADDING_SAME_AS_LAST) */
  I2S_DATA_PADDING_LAST = I2S_DATA_PADDING_SAME_AS_LAST,
  /** Padding last data in case of under-run
   *  (abbr. \c I2S_DATA_PADDING_SAME_AS_LAST) */
  I2S_DATA_PADDING_SAME = I2S_DATA_PADDING_SAME_AS_LAST
};

/**
 * I2S line default value when slot disabled
 */
enum i2s_line_default_state {
  /** Output default value is 0 */
  I2S_LINE_DEFAULT_0,
  /** Output default value is 1 */
  I2S_LINE_DEFAULT_1,
  /** Output default value is high impedance */
  I2S_LINE_DEFAULT_HIGH_IMPEDANCE = 3,
  /** Output default value is high impedance
   *  (abbr. \c I2S_LINE_DEFAULT_HIGH_IMPEDANCE) */
  I2S_LINE_DEFAULT_HIZ = I2S_LINE_DEFAULT_HIGH_IMPEDANCE
};

/**
 * I2S Serializer mode
 */
enum i2s_serializer_mode {
  /** Serializer is used to receive data */
  I2S_SERIALIZER_RECEIVE,
  /** Serializer is used to transmit data */
  I2S_SERIALIZER_TRANSMIT,
  /** Serializer is used to receive PDM data on each clock edge */
  I2S_SERIALIZER_PDM2
};

/**
 * I2S clock unit selection
 */
enum i2s_clock_unit {
  /** Clock Unit channel 0 */
  I2S_CLOCK_UNIT_0,
  /** Clock Unit channel 1 */
  I2S_CLOCK_UNIT_1,
  /** Number of Clock Unit channels */
  I2S_CLOCK_UNIT_N
};

/**
 * I2S Serializer selection
 */
enum i2s_serializer {
  /** Serializer channel 0 */
  I2S_SERIALIZER_0,
  /** Serializer channel 1 */
  I2S_SERIALIZER_1,
  /** Number of Serializer channels */
  I2S_SERIALIZER_N
};

#endif // I2S header include

/// @cond DISABLE
#endif // I2S defined
/// @endcond DISABLE

#endif // ADAFRUIT_ZEROPDM_H
