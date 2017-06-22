program t5_MEPA;
	a, b, c : integer;
	procedure p(value integer: x, value integer: y, reference integer: z):
		j : integer;
		begin
			z := x + y + z;
			write(x,z)
		end
begin
	a := 5;
	b:= 8;
	c:= 3;
	p(a,b,c);
	p(7, a+b+c, a)
end
