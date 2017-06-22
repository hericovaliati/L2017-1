program Multiplica2Numeros;
  a, b, c : integer;
  d, e, f: integer;
  procedure numberMultiplica(reference integer: k, reference integer: x, reference integer: y) :
    i : integer;
    j : integer;
  begin
    repeat
      k := i + j;
      write(k, i, j);
      k := i * j;
      write(k, i, j)
    until NOT true
  end
begin
  numberMultiplica(c, a, b);
  numberMultiplica(c, a, b)
end

