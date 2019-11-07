| declare two constants
  num1: dc.b #$15
  num2: dc.b #$26
| declare one byte of storage in main memory for the result
  result: ds.b 1
|
  move.b num1, D0
  move.b num2, D1
  add.b D0, D1
  move.b D1, result