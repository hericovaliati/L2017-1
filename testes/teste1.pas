program Teste1;
	oi : real;
	weight, group, charge, distance : integer
begin
	distance := 2300;
	oi := 2.2;
	read(weight);
	if distance > 60 then group := 5
		else group := (weight + 14) / 15;
	charge := 40 + 3 * (distance / 1000);
	write(charge)
end
