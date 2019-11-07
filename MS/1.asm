| declare two constants
  a: dc.b #$15
  ten: dc.b #$A
  hun: dc.b #$64
| declare one byte of storage in main memory for the result
  b: ds.b 1
|
  move a, D0
  sub #$14, D0
  bmi minus
  move hun, D0
  jsr end
minus: move.b ten, D0
end: move.b D0, b
  