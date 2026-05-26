# ⚡ Motor Current Monitoring System With MAX485 & EMA Filter

A real-time AC current monitoring system specifically engineered to track the load metrics of an automatic industrial grinding motor. The system measures current induction through a *Current Transformer* (CT) sensor utilizing **EmonLib**, filters read fluctuations with an **EMA (Exponential Moving Average)** digital algorithm, and transmits the rounded current telemetry long-distance via the **RS485** serial protocol.

---

## ✨ Key Features & Technical Implementation

* **Accurate AC Current Extraction (EmonLib):** Employs high-speed analog sampling at 4,800 samples per cycle to compute a highly precise RMS (*Root Mean Square*) current value.
* **Hardware Signal Conditioning (Physical Filter & Bias):** Integrates an external physical circuit to establish a 2.5V DC offset bias using a 10K voltage divider (R1 & R2). This protects the microcontroller analog pin by shifting the negative alternative current waveform into a readable positive DC scale. A 100uF/16V electrolytic capacitor (C1) acts as a ripple bypass filter to ensure reference voltage stability.
* **Digital Signal Filtration (EMA Filter):** Features an Exponential Moving Average filter to smooth out heavy current spikes and fluctuations when the grinding motor encounters dense material, balancing stability and responsiveness.
* **Smart Noise Floor Suppression:** Implements a dynamic noise floor cutoff. If the motor is completely powered down but the sensor picks up minor induced electrical noise below `0.10 A`, the system forces the readout to `0.0 A` for data integrity.
* **Robust RS485 Transmission:** Outputs the processed current measurements over an industrial RS485 transceiver network (via *SoftwareSerial*) configured with precise hardware *Driver Enable* (DE) and *Receiver Enable* (RE) pin toggling.

---

## 🔧 Hardware Pin & Circuit Configuration

### A. Current Sensor Signal Conditioning Circuit
Before connecting to the Arduino analog pin, the CT sensor outputs must be routed through the following hardware filter network:
* **R1 (10K Ohm):** Pulls up from VCC 5V to the sensor's mid-bias point (Sensor GND).
* **R2 (10K Ohm):** Ties the mid-bias point (Sensor GND) down to the Main Microcontroller GND.
* **C1 (100uF/16V):** Connected in parallel with R2 (Positive lead to mid-bias point, negative lead to Main GND) to decouple power rails and stabilize the reference.
* **Output Line:** Routed directly to Analog Pin **A1** on the Arduino.

### B. Microcontroller Pin Mapping Table
| Component / Function | Arduino Pin | Description |
| :--- | :--- | :--- |
| **Current Sensor Input** | Analog Pin A1 | Intermittent signal source coming from the physical conditioning filter circuit |
| **RS485 Module RO (RX)** | Digital Pin 10 | Serial Receiver Line for RS485 communication |
| **RS485 Module DI (TX)** | Digital Pin 11 | Serial Transmitter Line for RS485 communication |
| **RS485 Module DE & RE** | Digital Pin 3  | Hardware Transceiver Mode Control (High=TX, Low=RX) |

---

## ⚙️ Calibration Constants & Parameters

You can adjust physical sensitivity factors and filter response characteristics directly within the configuration header of `SensorArus.ino`:

```cpp
float       CALIB_FACTOR = 600.6;  // Scaling multiplier (calibrated against a physical clamp meter)
const float EMA_ALPHA   = 0.35;    // Filter smoothing factor (Higher = faster response, Lower = cleaner dampening)
const float NOISE_FLOOR = 0.10;    // Absolute zero current baseline suppression threshold (Amps)
const int   ADC_SAMPLES = 4800;    // Number of analog samples used to compute the Irms value
