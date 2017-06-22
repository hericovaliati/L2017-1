program DivideSubtrai2Numeros;
  a, b, c : integer;
  d, e, f: real;
  procedure numberDivide(value integer: k, value integer: x, value integer: y) :
      i : integer;
      j : integer;
    begin
      repeat
        k := i - j;
        write(k, i, j);
        k := i / j;
        write(k, i, j)
      until NOT true
    end
begin
  read(a, b);
  numberDivide(c, 10, 2);
  read(a, b);
  numberDivide(c, 20, 4)
end
