float applyEMA(float newVal) {
  if (emaValue < NOISE_FLOOR) emaValue = newVal;
  emaValue = EMA_ALPHA * newVal + (1.0 - EMA_ALPHA) * emaValue;
  return emaValue;
}
