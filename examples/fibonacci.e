Escribir_cadena('Calculadora de la sucesion de fibonacci.\n');
Escribir_cadena('Se calcula hasta: ');
Leer(n);

a := 1;
b := 1;
c := 0;

si n = 0
	entonces Escribir(0);
	si_no
		si n = 1
			entonces Escribir(1);
		si_no


			para i desde 2 hasta n paso 1 hacer
				c := b + a;
				a := b;
				b := c;
			fin_para;

			Escribir_cadena('El resultado es: ');
			Escribir(a);
			Escribir_cadena('\n');
		fin_si;
	fin_si;
fin_si;