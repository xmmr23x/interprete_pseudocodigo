#borrar;
#lugar(0,0);
Escribir_cadena('Ejemplos codificados para probar el interprete: \n');
Escribir_cadena('\t1. Sucesión de fibonacci.\n');
Escribir_cadena('\t0. Salir\n\n');

repetir
	Escribir_cadena('ipe> ');
	Leer(a);

	si (a = 1) entonces
		Escribir_cadena('\nCalculadora de la sucesion de fibonacci.\n');
		Escribir_cadena('\tSe calcula hasta: ');
		Leer(n);

		Escribir_cadena('\tEl resultado es: ');
		si (n = 0) entonces 
			Escribir(0);
		si_no
		si (n = 1) entonces 
			Escribir(1);
		si_no
			a := 1;
			b := 1;
			c := 0;

			para i desde 2 hasta n+1 paso 1 hacer
				c := b + a;
				a := b;
				b := c;
			fin_para;

			Escribir(a);
		fin_si;

		Escribir_cadena('\t\n\n');
		
		fin_si;
	fin_si;
hasta (a = 0);